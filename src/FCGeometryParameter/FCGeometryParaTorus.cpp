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

double FCGeometryParaTorus::majorRadius() const
{
    return mMajorRadius;
}

void FCGeometryParaTorus::setMajorRadius(double newMajorRadius)
{
    mMajorRadius = newMajorRadius;
}

double FCGeometryParaTorus::minorRadius() const
{
    return mMinorRadius;
}

void FCGeometryParaTorus::setMinorRadius(double newMinorRadius)
{
    mMinorRadius = newMinorRadius;
}

} // namespace FC
