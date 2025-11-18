/******************************************************************************
 * File     : FCAppDataManager.h
 * Brief    : FC的工程数据管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-18
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppDataManager.h"

namespace FC 
{
//===================================================
// FCAppDataManager
//===================================================

FCAppDataManager::FCAppDataManager(FCCoreInterface* c, QObject* p)
    : FCDataManagerInterface(c, p)
{
}

FCAppDataManager::~FCAppDataManager()
{
}

} // namespace FC

