/**
 * @file FCGeometryCreateBoxCylinder.cpp
 * @brief 创建圆柱体
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateBoxCylinder.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaCylinder.h"
#include <QDebug>
// occ
#include <gp_Ax2.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>

namespace FC 
{
FCGeometryCreateBoxCylinder::FCGeometryCreateBoxCylinder(QObject *parent)
    : FCGeometryModelBase(parent)
{
    
}

bool FCGeometryCreateBoxCylinder::execute()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(mLocation[0], mLocation[1], mLocation[2]));
    anAxis.SetDirection(gp_Dir(mAxis[0], mAxis[1], mAxis[2]));
    
    TopoDS_Shape aTopoCylinder = BRepPrimAPI_MakeCylinder(anAxis, mRadius, mLength).Shape();
    
    TopoDS_Shape *shape = new TopoDS_Shape;
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

    FCGeometryParaCylinder *para = new FCGeometryParaCylinder;
    para->setName(mName);
    para->setLocation(mLocation);
    para->setRadius(&mRadius);
    para->setLength(&mLength);
    para->setDirection(mAxis);
    mResult->setParameter(para);
    
    emit showSet(set);
    
    return true;
}

void FCGeometryCreateBoxCylinder::undo()
{

}

void FCGeometryCreateBoxCylinder::redo()
{

}

void FCGeometryCreateBoxCylinder::releaseResult()
{
    if (mResult != nullptr)
        delete mResult;
    mResult = nullptr;
}

void FCGeometryCreateBoxCylinder::setName(QString name)
{
    mName = name;
    
}

void FCGeometryCreateBoxCylinder::setLocation(double *loc)
{
    mLocation[0] = loc[0];
    mLocation[1] = loc[1];
    mLocation[2] = loc[2];
}

void FCGeometryCreateBoxCylinder::setAxis(double *axis)
{
    mAxis[0] = axis[0];
    mAxis[1] = axis[1];
    mAxis[2] = axis[2];
}

void FCGeometryCreateBoxCylinder::setRadius(double r)
{
    mRadius = r;
    
}

void FCGeometryCreateBoxCylinder::setLength(double l)
{
    mLength = l;
    
}

} // namespace FC
