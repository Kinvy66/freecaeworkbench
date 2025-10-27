/******************************************************************************
 * File     : FCDataManagerInterface.cpp
 * Brief    : 数据管理接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
