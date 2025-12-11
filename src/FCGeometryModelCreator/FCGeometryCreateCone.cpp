/**
 * @file FCGeometryCreateCone.cpp
 * @brief 创建圆锥
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateCone.h"
#include <QDebug>
#include <gp_Ax2.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include "FCGeometryData.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaCone.h"
#include "FCUniqueIDGenerater.h"

namespace FC 
{

FCGeometryCreateCone::FCGeometryCreateCone(QObject *parent)
    : FCGeometryModelBase(parent),
    mLocation{0,0,0},
    mAxis{0,0,1},        // 默认方向必须有效！
    mHeigth(1),
    mBottomRadius(1),
    mTopRadius(0)
{
    
}

bool FCGeometryCreateCone::execute()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(mLocation[0], mLocation[1], mLocation[2]));
    anAxis.SetDirection(gp_Dir(mAxis[0], mAxis[1], mAxis[2]));
    
    TopoDS_Shape aTopoCylinder = BRepPrimAPI_MakeCone(anAxis,
                                                      mBottomRadius,
                                                      mTopRadius,
                                                      mHeigth).Shape();
    
    TopoDS_Shape *shape = new TopoDS_Shape;
    *shape = aTopoCylinder;
    IdType id = 0;
    
    if (shape->IsNull())
    {
        delete shape;
        return false;
    }
    
    FCGeometrySet *set = new FCGeometrySet(STEP);
    set->setName(mName);
    set->setShape(shape);
    
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
    
    FCGeometryParaCone *para = new FCGeometryParaCone;
    para->setName(mName);
    para->setLocation(mLocation);
    para->setBottomRadius(mBottomRadius);
    para->setTopRadius(mTopRadius);
    para->setHeigth(mHeigth);
    para->setAxis(mAxis);
    mResult->setParameter(para);
    
    emit showSet(id);
    emit updateGeoTree(id, mName);
    
    
    qInfo() << "Create Cone,name:" << mName
             << ", top r:" <<  mTopRadius << ", bottom r" <<mBottomRadius << ", h:" << mHeigth
             << ", location:" << mLocation[0] << mLocation[1] << mLocation[2];    
    
    return true;
}

void FCGeometryCreateCone::undo()
{
    
}

void FCGeometryCreateCone::redo()
{
    
}

void FCGeometryCreateCone::releaseResult()
{
    if (mResult != nullptr)
        delete mResult;
    mResult = nullptr;
}

void FCGeometryCreateCone::setVisible(bool r)
{
    
}

void FCGeometryCreateCone::setName(QString name)
{
    mName = name;
}

void FCGeometryCreateCone::setLocation(double *loc)
{
    mLocation[0] = loc[0];
    mLocation[1] = loc[1];
    mLocation[2] = loc[2];
}

void FCGeometryCreateCone::setAxis(double *axis)
{
    mAxis[0] = axis[0];
    mAxis[1] = axis[1];
    mAxis[2] = axis[2];
}

void FCGeometryCreateCone::setBottomRadius(double r)
{
    mBottomRadius = r;
}

void FCGeometryCreateCone::setTopRadius(double r)
{
    mTopRadius = r;
}

void FCGeometryCreateCone::setHeigth(double h)
{
    mHeigth = h;
}

} // namespace FC
