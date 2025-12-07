/**
 * @file FCGeometryCreateSphere.cpp
 * @brief 创建球体
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateSphere.h"
#include <QDebug>
#include <BRepPrimAPI_MakeSphere.hxx>
#include "FCGeometryData.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaSphere.h"
#include "FCUniqueIDGenerater.h"

namespace FC 
{

FCGeometryCreateSphere::FCGeometryCreateSphere(QObject *parent)
    : FCGeometryModelBase(parent)
{
    
}

bool FCGeometryCreateSphere::execute()
{
    gp_Pnt pt(mLocation[0], mLocation[1], mLocation[2]);
    TopoDS_Shape aTopoBox = BRepPrimAPI_MakeSphere(pt, mRadius).Shape();
    TopoDS_Shape *shape = new TopoDS_Shape;
    *shape = aTopoBox;
    IdType id = 0;
    
    if (shape->IsNull())
    {
        delete shape;
        return false;
    }
    FCGeometrySet *set = new FCGeometrySet(STEP);
    set->setName(mName);
    set->setShape(shape);
    //_geoData->appendGeometrySet(set);
    mResult = set;
    
    if (mIsEdit)
    {
        id = mEditSetID;
        mGeoData->replaceSet(id, set);
        emit updateDisplayGeometryActor(id);    
    }
    else
    {
        id  = FCUniqueIDGenerater::id_uint64();
        mGeoData->appendGeometrySet(id, set);
    }
    
    FCGeometryParaSphere *para = new FCGeometryParaSphere;
    para->setName(mName);
    para->setLocation(mLocation);
    para->setRadius(mRadius);
    mResult->setParameter(para);
    
    emit showSet(id);
    emit updateGeoTree(id, mName);
    
    
    qDebug() << "Create Sphere ,name:" << mName
             << ", radius:" <<  mRadius
             << ", location:" << mLocation[0] << mLocation[1] << mLocation[2];    
    
    return true;
}

void FCGeometryCreateSphere::undo()
{
    
}

void FCGeometryCreateSphere::redo()
{
    
}

void FCGeometryCreateSphere::releaseResult()
{
    if (mResult != nullptr)
        delete mResult;
    mResult = nullptr;
}

void FCGeometryCreateSphere::setName(QString name)
{
    mName = name;
}

void FCGeometryCreateSphere::setLocation(double *loc)
{
    mLocation[0] = loc[0];
    mLocation[1] = loc[1];
    mLocation[2] = loc[2];
}

void FCGeometryCreateSphere::setRadius(double r)
{
    mRadius = r;
}

} // namespace FC
