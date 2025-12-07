/**
 * @file FCGeometryParaTorus.cpp
 * @brief 环面参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaTorus.h"

namespace FC 
{

FCGeometryParaTorus::FCGeometryParaTorus()
{
    mType = GeometryParaCreateTorus;
}

void FCGeometryParaTorus::setName(QString name)
{
     mName = name;
}

QString FCGeometryParaTorus::getName()
{
    return mName;
}

void FCGeometryParaTorus::setLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaTorus::getLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

bool FCGeometryParaTorus::getMajorRadius(double* r)
{
    *r = mMajorRadius;
    return true;
}

void FCGeometryParaTorus::setMajorRadius(double newMajorRadius)
{
    mMajorRadius = newMajorRadius;
}

bool FCGeometryParaTorus::getMinorRadius(double* r)
{
    *r = mMinorRadius;
    return true;
}

void FCGeometryParaTorus::setMinorRadius(double newMinorRadius)
{
    mMinorRadius = newMinorRadius;
}

bool FCGeometryParaTorus::getAngle(double* angle)
{
    *angle = mAngle;
    return true;
}

void FCGeometryParaTorus::setAngle(double newAngle)
{
    mAngle = newAngle;
}

} // namespace FC
