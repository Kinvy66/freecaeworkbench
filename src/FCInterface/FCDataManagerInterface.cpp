/**
 * @file FCDataManagerInterface.cpp
 * @brief 数据管理接口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCDataManagerInterface.h"

namespace FC {
class FCDataManagerInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCDataManagerInterface)
public:
    PrivateData(FCDataManagerInterface* p);
    // FCDataManager* mDataMgr;
};


//==============================================================
// FCDataManagerInterfacePrivate
//==============================================================
FCDataManagerInterface::PrivateData::PrivateData(FCDataManagerInterface* p)
    : q_ptr(p)
{
    // mDataMgr = new DADataManager(p);
}

//==============================================================
// DADataManagerInterface
//==============================================================
FCDataManagerInterface::FCDataManagerInterface(FCCoreInterface* c, QObject* par)
    : FCBaseInterface(c, par), FC_PIMPL_CONSTRUCT
{
    // connect(d_ptr->mDataMgr, &DADataManager::dataAdded, this, &DADataManagerInterface::dataAdded);
    // connect(d_ptr->mDataMgr, &DADataManager::dataBeginRemove, this, &DADataManagerInterface::dataBeginRemove);
    // connect(d_ptr->mDataMgr, &DADataManager::dataRemoved, this, &DADataManagerInterface::dataRemoved);
    // connect(d_ptr->mDataMgr, &DADataManager::dataChanged, this, &DADataManagerInterface::dataChanged);
}

FCDataManagerInterface::~FCDataManagerInterface()
{
    
}

} // namespace FC
