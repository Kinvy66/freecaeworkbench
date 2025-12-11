/**
 * @file FCGeometryCreateTorus.cpp
 * @brief 创建环面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateTorus.h"
#include "FCGeometrySet.h"
#include <QDebug>
#include "FCUniqueIDGenerater.h"
#include "FCGeometryParaTorus.h"
#include <BRepPrimAPI_MakeTorus.hxx>

#ifndef PI
#define PI 3.14159265358979323846
#endif

namespace FC 
{

FCGeometryCreateTorus::FCGeometryCreateTorus(QObject *parent)
    : FCGeometryModelBase(parent)
{
    
}

bool FCGeometryCreateTorus::execute()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(mLocation[0], mLocation[1], mLocation[2]));
    anAxis.SetDirection(gp_Dir(0, 0, 1));  
    
    TopoDS_Shape aTopoTorus;
    double degree = mAngle * PI / 180.0;  // occ的api参数是弧度
    if (mAngle > 0) {
        aTopoTorus = BRepPrimAPI_MakeTorus(anAxis, mMajorRadius, mMinorRadius, degree).Shape();
    } else {
        aTopoTorus = BRepPrimAPI_MakeTorus(anAxis, mMajorRadius, mMinorRadius).Shape();
    }
    
    // aTopoTorus = BRepPrimAPI_MakeTorus(anAxis, mMajorRadius, mMinorRadius).Shape();
        
    TopoDS_Shape *shape = new TopoDS_Shape;
    *shape = aTopoTorus;
    
    if (shape->IsNull()) {
        delete shape;
        return false;
    }
    
    FCGeometrySet *set = new FCGeometrySet(STEP);
    set->setName(mName);
    set->setShape(shape);
    mResult = set;
    
    IdType id = 0;
    if (mIsEdit) {
        id = mEditSetID;
        mGeoData->replaceSet(id, set);
        emit updateDisplayGeometryActor(id);
    } else {
        id = FCUniqueIDGenerater::id_uint64();
        mGeoData->appendGeometrySet(id, set);
    }
    
    FCGeometryParaTorus *para = new FCGeometryParaTorus;
    para->setName(mName);
    para->setLocation(mLocation);
    para->setMajorRadius(mMajorRadius);
    para->setMinorRadius(mMinorRadius);
    para->setAngle(mAngle);
    mResult->setParameter(para);
    
    emit showSet(id);
    emit updateGeoTree(id, mName);
    
    qInfo() << "Create Torus: name:" << mName
             << ", R_major:" << mMajorRadius
             << ", R_minor:" << mMinorRadius
             << ", angle:" << mAngle
             << ", location:" << mLocation[0] << mLocation[1] << mLocation[2];
    
    return true;
}

void FCGeometryCreateTorus::undo()
{
    
}

void FCGeometryCreateTorus::redo()
{
    
}

void FCGeometryCreateTorus::releaseResult()
{
    if (mResult != nullptr)
        delete mResult;
    mResult = nullptr;
}

void FCGeometryCreateTorus::setVisible(bool r)
{
    
}

void FCGeometryCreateTorus::setName(QString name)
{
    mName = name;
    
}

void FCGeometryCreateTorus::setLocation(double *loca)
{
    mLocation[0] = loca[0];
    mLocation[1] = loca[1];
    mLocation[2] = loca[2];
}

void FCGeometryCreateTorus::setMajorRadius(double r)
{
    mMajorRadius = r;
}

void FCGeometryCreateTorus::setMinorRadius(double r)
{
    mMinorRadius = r;
}

void FCGeometryCreateTorus::setAngle(double angle)
{
    mAngle = angle;
}

} // namespace FC
