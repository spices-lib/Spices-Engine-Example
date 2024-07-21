//--------------------------------------------------------------------------------------
// File: DataScope.cpp
//
// Distributed as part of NVIDIA Nsight serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------------------

#include "DataScope.h"
#include "ReadOnlyDatabase.h"

namespace Serialization {

DataScope::DataScope(DataScopeTracker& tracker)
    : m_Tracker(tracker)
    , m_pParent()
    , m_staticStorage{}
    , m_dynamicStorage()
    , m_pUsedPages(m_staticStorage)
    , m_usedPageCount()
    , m_pDatabase()
{
    m_pParent = m_Tracker.m_pCurrentDataScope;
    m_Tracker.m_pCurrentDataScope = this;
}

DataScope::~DataScope()
{
    if (m_pDatabase)
    {
        for (int i = 0; i < m_usedPageCount; ++i)
        {
            m_pDatabase->Unlock(m_pUsedPages[i]);
        }
    }

    m_Tracker.m_pCurrentDataScope = m_pParent;
}

void DataScope::SetUsesPage(PageId pageOffset, IReadOnlyDatabase& database)
{
    auto pPageHandle = database.Lock(pageOffset);
    if (!pPageHandle)
    {
        NV_DATABASE_WARN(!pPageHandle, "No page handle for the given page id.");
        return;
    }

    if (m_usedPageCount < NUM_STATIC_IDS)
    {
        m_pUsedPages[m_usedPageCount] = pPageHandle;
    }
    else
    {
        if (m_usedPageCount == NUM_STATIC_IDS)
        {
            m_dynamicStorage.assign(m_staticStorage, m_staticStorage + NUM_STATIC_IDS);
        }

        m_dynamicStorage.push_back(pPageHandle);
        m_pUsedPages = m_dynamicStorage.data();
    }

    ++m_usedPageCount;

    NV_DATABASE_WARN(!m_pDatabase || m_pDatabase == &database, "There should be a single database.");
    m_pDatabase = &database;
}

#if defined(__arm__)
void DataScope::AddBlobProxy(std::shared_ptr<BlobProxyBase>& pBlobProxy)
{
    m_blobProxyVec.push_back(pBlobProxy);
}
#endif

DataScopeTracker& DataScopeTracker::Instance()
{
    static TLS_STORAGE DataScopeTracker* pTracker = nullptr;
    DataScopeTracker* pLocal = pTracker;
    if (!pLocal)
    {
        pTracker = new DataScopeTracker();
        return *pTracker;
    }
    return *pLocal;
}

void DataScopeTracker::SetUsesPage(uint64_t pageOffset, IReadOnlyDatabase& database)
{
    if (!m_pCurrentDataScope)
    {
        return;
    }
    m_pCurrentDataScope->SetUsesPage(pageOffset, database);
}

#if defined(__arm__)
void DataScopeTracker::AddBlobProxyToCurrentDataScope(std::shared_ptr<BlobProxyBase>& pBlobProxy)
{
    NV_DATABASE_WARN(m_pCurrentDataScope != nullptr, "No current data scope");
    if (m_pCurrentDataScope != nullptr)
    {
        m_pCurrentDataScope->AddBlobProxy(pBlobProxy);
    }
}
#endif

DataScopeTracker::DataScopeTracker()
    : m_pCurrentDataScope()
{
}

} // namespace Serialization
