/**
 * @file FCGeometryModelBase.cpp
 * @brief 模型创建基类
 * @date 2025-11-22
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryModelBase.h"


namespace FC 
{

FCGeometryModelBase::FCGeometryModelBase(QObject *parent)
    : QObject(parent)
{
    mGeoData = FCGeometryData::getInstance();
}


void FCGeometryModelBase::undo()
{
    
}

void FCGeometryModelBase::redo()
{
    
}

void FCGeometryModelBase::releaseResult()
{
    
}

TopoDS_Shape *FCGeometryModelBase::getResultShape()
{
    return mResShape;
}

GeometryModelType FCGeometryModelBase::getGeometryModelType() const
{
    return mType;
}

/**
 * @brief 设置last set
 * @param set
 */
void FCGeometryModelBase::setEditData(const IdType setID)
{
    if (setID != 0) {
        mEditSetID = setID;
    }
    mIsEdit = true;
}

} // namespace FC

