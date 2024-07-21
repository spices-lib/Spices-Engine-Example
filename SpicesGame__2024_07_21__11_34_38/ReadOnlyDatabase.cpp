//--------------------------------------------------------------------------------------
// File: ReadOnlyDatabase.cpp
//
// Distributed as part of NVIDIA Nsight serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------------------

#include "ReadOnlyDatabase.h"
#include "DataScope.h"

#include <algorithm>
#include <cassert>
#include <string>

#if NV_ANDROID_EXTERNAL()
#include "Helpers.h"
#include <android/asset_manager.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#endif

namespace Serialization {
//------------------------------------------------------------------------------
// Definition for DATABASE_HANDLE_INVALID
//------------------------------------------------------------------------------
const DATABASE_HANDLE DATABASE_HANDLE_INVALID;

//------------------------------------------------------------------------------
// CloseFile
//------------------------------------------------------------------------------
static void CloseFile(NVFILE* pFile)
{
#if NV_ANDROID_EXTERNAL()
    AAsset_close(pFile);
#else
    fclose(pFile);
#endif
}

//------------------------------------------------------------------------------
// OpenFile
//------------------------------------------------------------------------------
static NVFILE* OpenFile(const char* pFileName)
{
#if NV_ANDROID_EXTERNAL()
    return AAssetManager_open(pAndroidApp->activity->assetManager, pFileName, AASSET_MODE_STREAMING);
#else
    return fopen(pFileName, "rb");
#endif
}

//------------------------------------------------------------------------------
// SeekInFile
//------------------------------------------------------------------------------
static bool SeekInFile(NVFILE* pFile, uint64_t offset, int whence)
{
#if NV_ANDROID_EXTERNAL()
    return AAsset_seek(pFile, offset, whence) != -1;
#elif defined(__ANDROID__) || defined(__QNX__) || defined(__INTEGRITY)
    // Android/QNX does not have LFS
    return !fseek(pFile, offset, whence);
#elif defined(_WIN32)
    return !_fseeki64(pFile, offset, whence);
#else
    return !fseeko64(pFile, offset, whence);
#endif
}

//------------------------------------------------------------------------------
// GetFileLength
//------------------------------------------------------------------------------
static size_t GetFileLength(NVFILE* pFile)
{
    size_t totalSize = 0;
    NV_DATABASE_WARN(pFile, "Invalid file");

#if NV_ANDROID_EXTERNAL()
    totalSize = (size_t)AAsset_getLength(pFile);
#elif defined(__ANDROID__) || defined(__QNX__) || defined(__INTEGRITY)
    // Android/QNX does not have LFS
    fseek(pFile, 0, SEEK_END);
    totalSize = (size_t)ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
#elif defined(_WIN32)
    _fseeki64(pFile, 0, SEEK_END);
    totalSize = (size_t)_ftelli64(pFile);
    _fseeki64(pFile, 0, SEEK_SET);
#else
    fseeko64(pFile, 0, SEEK_END);
    totalSize = (size_t)ftello64(pFile);
    fseeko64(pFile, 0, SEEK_SET);
#endif
    return totalSize;
}

//------------------------------------------------------------------------------
// ReadFromFile
//------------------------------------------------------------------------------
static size_t ReadFromFile(NVFILE* pFile, size_t elemSize, size_t numElements, void* buf)
{
    NV_DATABASE_WARN(pFile, "Invalid file");

    size_t numBytesRead;

#if NV_ANDROID_EXTERNAL()
    const int bytesRead = AAsset_read(pFile, buf, elemSize * numElements);
    numBytesRead = (std::max)(size_t(bytesRead), size_t(0));
#else
    const size_t elemsRead = fread(buf, elemSize, numElements, pFile);
    numBytesRead = elemSize * elemsRead;
#endif

#if defined(__COVERITY__)
    __coverity_mark_pointee_as_sanitized__(buf, GENERIC);
#endif
    return numBytesRead;
}

//------------------------------------------------------------------------------
// Constructors.
//------------------------------------------------------------------------------
ReadOnlyDatabase::ReadOnlyDatabase()
    : m_pFile(NULL)
    , m_PageAccessCounter(0)
    , m_PageSizeThreshold(1 << 20) // Default: 1 MB per page
    , m_MaxResidentPages(256) // Default: 256 pages
    , m_ForceEvict(false)
    , m_lastInitResult(InitResult::NeverInitialized)
{
}

ReadOnlyDatabase::ReadOnlyDatabase(const char* pFileName, uint64_t PageSizeThreshold, size_t MaxResidentPages)
    : m_pFile(NULL)
    , m_PageAccessCounter(0)
    , m_PageSizeThreshold(PageSizeThreshold)
    , m_MaxResidentPages(MaxResidentPages)
    , m_ForceEvict(false)
    , m_lastInitResult(InitResult::NeverInitialized)
{
    m_lastInitResult = InitReadOnly(pFileName);
}

//------------------------------------------------------------------------------
// Destructor.
//------------------------------------------------------------------------------
ReadOnlyDatabase::~ReadOnlyDatabase()
{
    CleanupPageRecords();
    if (m_pFile)
    {
        CloseFile(m_pFile);
    }
}

//------------------------------------------------------------------------------
// InitResultToString
//------------------------------------------------------------------------------
const char* ReadOnlyDatabase::InitResultToString(InitResult result)
{
    switch (result)
    {
    case InitResult::Ok:
        return "Successful initialization";
    case InitResult::NeverInitialized:
        return "Database never initialized";
    case InitResult::BadArgument:
        return "Bad initialization argument";
    case InitResult::FailedToOpenDatabase:
        return "Failed to find or open database";
    case InitResult::FailedToOpenDatabaseRecords:
        return "Failed to open database records";
    case InitResult::AllocationFailure:
        return "Allocation failure";
    case InitResult::UnspecifiedFailure:
        return "Unspecified failure";
    default:
        return "Unknown result";
    }
}

//------------------------------------------------------------------------------
// Init- assign a filename.
//------------------------------------------------------------------------------
ReadOnlyDatabase::InitResult ReadOnlyDatabase::Init(const char* pFileName)
{
    m_lastInitResult = InitReadOnly(pFileName);
    return m_lastInitResult;
}

//------------------------------------------------------------------------------
// GetLastInitResult
//------------------------------------------------------------------------------
ReadOnlyDatabase::InitResult ReadOnlyDatabase::GetLastInitResult() const
{
    return m_lastInitResult;
}

//------------------------------------------------------------------------------
// FreeCachedMemory
//------------------------------------------------------------------------------
void ReadOnlyDatabase::FreeCachedMemory()
{
    // Quick return if we have nothing resident
    if (m_ResidentBlobPages.empty())
    {
        return;
    }

    // Clear resident pages and dealloc memory if needed.
    std::vector<BlobPage*>::iterator iter = m_ResidentBlobPages.begin();
    std::vector<BlobPage*>::iterator end = m_ResidentBlobPages.end();
    for (; iter != end; ++iter)
    {
        BlobPage* pPage = *iter;
        if (pPage->pMemory)
        {
            delete[] pPage->pMemory;
            pPage->pMemory = NULL;
        }
    }

    m_ResidentBlobPages.clear();
}

//------------------------------------------------------------------------------
// Build up our internally stored pages.
//------------------------------------------------------------------------------
void ReadOnlyDatabase::BuildPageRecords()
{
    // Make sure we are clean to begin with.
    CleanupPageRecords();

    // Our raw blob records should already be initialized.  Loop through and construct
    // pages.  We want the pages to be less than or equal to m_PageSizeThreshold.
    // If a single blob exceeds m_PageSizeThreshold, then it gets its own page.

    uint64_t currentPageOffset = 0;
    uint64_t currentPageSize = 0;
    std::vector<BlobRecord>::iterator iter = m_BlobRecords.begin();
    std::vector<BlobRecord>::iterator end = m_BlobRecords.end();
    for (; iter != end; ++iter)
    {
        const BlobRecord& record = *iter;

        // Determine if there are gaps in the generated resource file records
        // and adjust the current page size to account for them
        uint64_t recordGap = record.Offset - (currentPageOffset + currentPageSize);
        if (recordGap)
        {
            currentPageSize += recordGap;
        }

        if (currentPageSize && currentPageSize + record.Size > m_PageSizeThreshold)
        {
            // This page is big enough already.
            m_BlobPages.push_back(BlobPage(currentPageOffset, currentPageSize));

            currentPageOffset = record.Offset;
            currentPageSize = 0;
        }

        currentPageSize += record.Size;
    }

    // Final element.
    if (currentPageSize)
    {
        m_BlobPages.push_back(BlobPage(currentPageOffset, currentPageSize));
    }
}

//------------------------------------------------------------------------------
// Clean up our internally stored pages.
//------------------------------------------------------------------------------
void ReadOnlyDatabase::CleanupPageRecords()
{
    // Clear resident pages
    FreeCachedMemory();

    // Clear non-resident page info
    m_BlobPages.clear();
}

//------------------------------------------------------------------------------
// InitReadOnly- assign a filename (readonly specific).
//------------------------------------------------------------------------------
ReadOnlyDatabase::InitResult ReadOnlyDatabase::InitReadOnly(const char* pFileName)
{
    // Assume success
    InitResult retval = InitResult::Ok;
    NVFILE* pRecordsFile = NULL;

    CleanupPageRecords();
    m_BlobRecords.clear();
    m_BlobPages.clear();

    if (m_pFile)
    {
        CloseFile(m_pFile);
        m_pFile = NULL;
    }

    if (!pFileName)
    {
        NV_DATABASE_WARN(false, "pFileName must be non-null");
        return InitResult::BadArgument;
    }

    // Handle both when the database is in the current directory as well as
    // the parent folder (or parent's parent folder). Also ensure the first
    // search path is empty to handle the possibility that the path is
    // absolute. nullptr must be the last entry.

#if defined(_WIN32)
    const auto appDirectory = []() {
        char szFileName[MAX_PATH];
        GetModuleFileNameA(NULL, szFileName, MAX_PATH);
        std::string dir = szFileName;
        auto pos = dir.find_last_of('\\');
        dir.erase(pos);
        return dir;
    }();

    std::string directoriesToTry[] = { "", ".\\", "..\\", "..\\..\\", "..\\..\\..\\", appDirectory, appDirectory + "..\\", appDirectory + "..\\..\\" };
#else
    std::string directoriesToTry[] = { "", "../", "../../", "../../../" };
#endif
    std::string pathToFile;
    for (const auto& directoryToTry : directoriesToTry)
    {
        pathToFile = directoryToTry + std::string(pFileName);
        m_pFile = OpenFile(pathToFile.c_str());
        if (m_pFile)
        {
            // Update pFileName given the path
            pFileName = pathToFile.c_str();
            break;
        }
    }

    if (!m_pFile)
    {
        auto fileOpenWarning = "Could not open file" + pathToFile;
        NV_DATABASE_WARN(false, fileOpenWarning.c_str());
        return InitResult::FailedToOpenDatabase;
    }

    std::string RecordsFileName = std::string(pFileName) + ".rec";

    try
    {
        // Now read the table that will tell us how the blobs are layed out
        pRecordsFile = OpenFile(RecordsFileName.c_str());
        if (!pRecordsFile)
        {
            auto recordOpenWarning = "Can't open records" + RecordsFileName;
            NV_DATABASE_WARN(false, recordOpenWarning.c_str());
            throw InitResult::FailedToOpenDatabaseRecords;
        }

        BuildBlobRecords(pRecordsFile);

        BuildPageRecords();
    }
    catch (InitResult r)
    {
        retval = r;
    }
    catch (std::bad_alloc&)
    {
        retval = InitResult::AllocationFailure;
    }
    catch (...)
    {
        retval = InitResult::UnspecifiedFailure;
    }

    // Cleanup.
    if (pRecordsFile)
    {
        CloseFile(pRecordsFile);
    }

    return retval;
}

//------------------------------------------------------------------------------
// BuildBlobRecords - Build up the blob records from an open file
//------------------------------------------------------------------------------
void ReadOnlyDatabase::BuildBlobRecords(NVFILE* pFile)
{
    // Read the count, by getting the total file size
    const size_t totalSize = GetFileLength(pFile);

    size_t recordsCount = totalSize / sizeof(BlobRecord);
    m_BlobRecords.resize(recordsCount);

    // Read the records
    if ((recordsCount > 0) && (0 == ReadFromFile(pFile, sizeof(m_BlobRecords[0]), recordsCount, &m_BlobRecords[0])))
    {
        NV_DATABASE_WARN(false, "Can't read records");
        throw 0;
    }
}

//------------------------------------------------------------------------------
// Clean up our internally stored blob table
//------------------------------------------------------------------------------
void ReadOnlyDatabase::CleanupBlobRecords()
{
    // Clear blob records.
    m_BlobRecords.clear();
}

//------------------------------------------------------------------------------
// GetSize - Get the size of a blob if it exists, or zero
//------------------------------------------------------------------------------
uint64_t ReadOnlyDatabase::GetSize(const DATABASE_HANDLE& Handle)
{
    if (Handle.value < 0 || Handle.value >= (int)m_BlobRecords.size())
    {
        return 0;
    }

    return m_BlobRecords[Handle.value].Size;
}

//------------------------------------------------------------------------------
// DoRead - Read paged blob from the database.  Returns NULL upon error.
//------------------------------------------------------------------------------
void* ReadOnlyDatabase::DoRead(const DATABASE_HANDLE& handle)
{
    auto& scopeTracker = DataScopeTracker::Instance();
    return DoRead(handle, scopeTracker);
}

//------------------------------------------------------------------------------
// DoRead - Read paged blob from the database.  Returns NULL upon error.
//------------------------------------------------------------------------------
void* ReadOnlyDatabase::DoRead(const DATABASE_HANDLE& handle, DataScopeTracker& scopeTracker)
{
    if (DATABASE_HANDLE_INVALID == handle)
    {
        return NULL;
    }

    else if (handle.value < 0 || handle.value >= (int)m_BlobRecords.size())
    {
        NV_DATABASE_WARN(false, "Invalid handle");
        return NULL;
    }

    const BlobRecord& neededBlob = m_BlobRecords[handle.value];
    BlobPage* pPage = NULL;

    try
    {
        // First to see if the needed page is resident.
        BlobPage pageKey(neededBlob.Offset, neededBlob.Size);
        std::vector<BlobPage>::iterator foundIter;
        foundIter = std::lower_bound(m_BlobPages.begin(), m_BlobPages.end(), pageKey, PageOffsetComparator<BlobPage>());

        if (m_BlobPages.end() == foundIter || neededBlob.Offset < foundIter->PageOffset || neededBlob.Offset >= foundIter->PageOffset + foundIter->PageSize)
        {
            NV_DATABASE_WARN(false, "Could not find page matching requested blob");
            return NULL;
        }

        pPage = &(*foundIter);

        // Track the usage of this page in this scope.  If the page is resident this should prevent it from being evicted before the next block.
        scopeTracker.SetUsesPage(pPage->PageOffset, *this);

        // Cache miss.
        if (!pPage->pMemory)
        {
            std::lock_guard<std::mutex> lockGuard(m_mutex);

            // Double locking to prevent multiple threads loading the same page
            if (!pPage->pMemory)
            {
                // We should only need to lock as many pages as the number of blob params consumed by a single function call.
                // Ten should be more than conservative.
                const static size_t MAX_EXPECTED_LOCKED_PAGES = 32;
                (void)MAX_EXPECTED_LOCKED_PAGES;

                uint8_t* pRecycledMemory = NULL;
                uint64_t RecycledMemorySize = 0;

                auto PagesNeedEvicting = [this]() -> bool {
                    // If we are in a "Force Evict" situation, we want to clear out all of the resident pages
                    return m_ResidentBlobPages.size() && (m_ForceEvict || m_ResidentBlobPages.size() >= m_MaxResidentPages);
                };

                // If necessary, search for unlocked pages to evict.  The oldest pages should be at the beginning of the vector
                if (PagesNeedEvicting())
                {
                    // Sort resident pages by last access
                    std::sort(m_ResidentBlobPages.begin(), m_ResidentBlobPages.end(), PageLastAccessComparator());

                    std::vector<BlobPage*>::iterator pageIter = m_ResidentBlobPages.begin();
                    while (PagesNeedEvicting() && pageIter != m_ResidentBlobPages.end())
                    {
                        BlobPage* pEvictPage = *pageIter;
                        if (pEvictPage->LockCount <= 0)
                        {
                            NV_DATABASE_WARN(pEvictPage->LockCount == 0, "Attempting to evict locked page");

                            // If we are not in the "m_ForceEvict" path, recycle the allocation if possible
                            if (!m_ForceEvict && NULL == pRecycledMemory && pEvictPage->MemoryCapacity <= m_PageSizeThreshold && pEvictPage->MemoryCapacity >= pPage->PageSize)
                            {
                                pRecycledMemory = pEvictPage->pMemory;
                                RecycledMemorySize = pEvictPage->MemoryCapacity;
                            }
                            else
                            {
                                delete[] pEvictPage->pMemory;
                            }

                            pEvictPage->pMemory = NULL;
                            pageIter = m_ResidentBlobPages.erase(pageIter);
                        }
                        else
                        {
                            ++pageIter;
                        }
                    }
                }

                NV_DATABASE_WARN(m_ResidentBlobPages.size() < (size_t)std::max(m_MaxResidentPages, MAX_EXPECTED_LOCKED_PAGES), "Too many resident pages.");

                auto pMemory = pRecycledMemory ? pRecycledMemory : new uint8_t[(size_t)pPage->PageSize];
                auto MemoryCapacity = pRecycledMemory ? RecycledMemorySize : pPage->PageSize;

                // Read the page data from disk.
                SeekInFile(m_pFile, pPage->PageOffset, SEEK_SET);
                const uint64_t bytesRead = ReadFromFile(m_pFile, size_t(pPage->PageSize), 1, pMemory);

                // Read completed (successfully or not), claim the memory
                pPage->pMemory = pMemory;
                pPage->MemoryCapacity = MemoryCapacity;

                // Insert in resident list
                m_ResidentBlobPages.insert(m_ResidentBlobPages.end(), pPage);

                if (pPage->PageSize != bytesRead)
                {
                    NV_DATABASE_WARN(false, "Could not read page from file");
                    return NULL;
                }
            }
        }
    }
    catch (std::bad_alloc&)
    {
        NV_DATABASE_WARN(false, "Out of memory!");
        return NULL;
    }
    catch (...)
    {
        NV_DATABASE_WARN(false, "Unknown error");
        return NULL;
    }

    if (!pPage || !pPage->pMemory)
    {
        NV_DATABASE_WARN(false, "Missing data");
        return NULL;
    }

    uint64_t localOffset = neededBlob.Offset - pPage->PageOffset;
    pPage->LastAccessCounter = m_PageAccessCounter++;

    // Return an offset into the paged data.
    return pPage->pMemory + localOffset;
}

//------------------------------------------------------------------------------
// Lock - increment the refcount on this blob
//------------------------------------------------------------------------------
DataScope::LockedPageHandle ReadOnlyDatabase::Lock(uint64_t pageOffset)
{
    BlobPage pageKey(pageOffset, 0);
    std::vector<BlobPage>::iterator foundIter;
    foundIter = std::lower_bound(m_BlobPages.begin(), m_BlobPages.end(), pageKey, PageOffsetComparator<BlobPage>());

    if (m_BlobPages.end() == foundIter || pageOffset < foundIter->PageOffset)
    {
        NV_DATABASE_WARN(false, "Could not find page matching requested blob");
        return nullptr;
    }

    foundIter->LockCount++;
    auto retVal = &(*foundIter);
    return retVal;
}

//------------------------------------------------------------------------------
// Lock - decrement the refcount on this blob
//------------------------------------------------------------------------------
void ReadOnlyDatabase::Unlock(DataScope::LockedPageHandle pPageHandle)
{
    static_cast<BlobPage*>(pPageHandle)->LockCount--;
}

//------------------------------------------------------------------------------
// Less-than operator for BlobPage.  If this returns false for both (a,b) and
// (b,a) this means that one memory span contains the other.
//------------------------------------------------------------------------------
int ReadOnlyDatabase::PageLastAccessComparator::operator()(const BlobPage* item1, const BlobPage* item2)
{
    return (item1->LastAccessCounter < item2->LastAccessCounter);
}

} // namespace Serialization
