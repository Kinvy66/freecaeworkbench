/**
 * @file FCGeometryData.cpp
 * @brief 几何数据管理基类头文件
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */

#include "FCGeometryData.h"
#include <gp_Ax3.hxx>
#include <assert.h>
#include <QCryptographicHash>

namespace FC 
{

FCGeometryData *FCGeometryData::mInstance = nullptr;

FCGeometryData *FCGeometryData::getInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new FCGeometryData;
    }
    return mInstance;
}

FCGeometryData::~FCGeometryData()
{
    
}

} // namespace FC
