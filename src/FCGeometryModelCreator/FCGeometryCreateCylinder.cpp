/**
 * @file FCGeometryCreateBoxCylinder.cpp
 * @brief 创建圆柱体
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateCylinder.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaCylinder.h"
#include "FCUniqueIDGenerater.h"
#include <QDebug>
// occ
#include <gp_Ax2.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>

namespace FC 
{
FCGeometryCreateCylinder::FCGeometryCreateCylinder(QObject *parent)
    : FCGeometryModelBase(parent)
{
    
}

bool FCGeometryCreateCylinder::execute()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(mLocation[0], mLocation[1], mLocation[2]));
    anAxis.SetDirection(gp_Dir(mAxis[0], mAxis[1], mAxis[2]));
    TopoDS_Shape aTopoCylinder = BRepPrimAPI_MakeCylinder(anAxis, mRadius, mLength).Shape();
    TopoDS_Shape *shape = new TopoDS_Shape;
    IdType id = 0;
    *shape = aTopoCylinder;
    if (shape->IsNull())
    {
        delete shape;
        return false;
    }
    
    FCGeometrySet *set = new FCGeometrySet(STEP);
    
    set->setName(mName);
    set->setShape(shape);
    mResult = set;
    
    if (mIsEdit) {
        id = mEditSetID;
        mGeoData->replaceSet(id, set);
        emit updateDisplayGeometryActor(id);        
    } else {
        id  = FCUniqueIDGenerater::id_uint64();
        mGeoData->appendGeometrySet(id, set);
    }

    FCGeometryParaCylinder *para = new FCGeometryParaCylinder;
    para->setName(mName);
    para->setLocation(mLocation);
    para->setRadius(&mRadius);
    para->setLength(&mLength);
    para->setDirection(mAxis);
    mResult->setParameter(para);
    
    emit showSet(id);
    emit updateGeoTree(id, mName);
    
    qInfo() << "Create Cylinder,name:" << mName
             << ", r:" <<  mRadius << ", l" <<mLength
             << ", location:" << mLocation[0] << mLocation[1] << mLocation[2];    
    
    return true;
}

void FCGeometryCreateCylinder::undo()
{

}

void FCGeometryCreateCylinder::redo()
{

}

void FCGeometryCreateCylinder::releaseResult()
{
    if (mResult != nullptr)
        delete mResult;
    mResult = nullptr;
}

void FCGeometryCreateCylinder::setName(QString name)
{
    mName = name;
    
}

void FCGeometryCreateCylinder::setLocation(double *loc)
{
    mLocation[0] = loc[0];
    mLocation[1] = loc[1];
    mLocation[2] = loc[2];
}

void FCGeometryCreateCylinder::setAxis(double *axis)
{
    mAxis[0] = axis[0];
    mAxis[1] = axis[1];
    mAxis[2] = axis[2];
}

void FCGeometryCreateCylinder::setRadius(double r)
{
    mRadius = r;
    
}

void FCGeometryCreateCylinder::setLength(double l)
{
    mLength = l;
    
}

} // namespace FC
