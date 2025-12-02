/**
 * @file FCAppDataManager.cpp
 * @brief FC的工程数据管理
 * @date 2025-11-18
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCAppDataManager.h"
#include "FCGeometryData.h"

namespace FC 
{
//===================================================
// FCAppDataManager
//===================================================

FCAppDataManager::FCAppDataManager(FCCoreInterface* c, QObject* p)
    : FCDataManagerInterface(c, p)
{
    mGeoData = FCGeometryData::getInstance();
}

FCAppDataManager::~FCAppDataManager()
{
}

FCGeometryData *FCAppDataManager::getGeometryData()
{
    return FCGeometryData::getInstance();
}

} // namespace FC

