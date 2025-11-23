/******************************************************************************
 * File     : FCGeometryModelBase.cpp
 * Brief    : 几何模型基类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-22
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCGeometryModelBase.h"


namespace FC 
{

FCGeometryModelBase::FCGeometryModelBase(QObject *parent)
{
    
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

} // namespace FC

