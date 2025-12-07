/**
 * @file FCGeometryParaSphere.cpp
 * @brief 球体参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaSphere.h"
namespace FC 
{
FCGeometryParaSphere::FCGeometryParaSphere()
{
    mType = GeometryParaCreateSphere;
}

void FCGeometryParaSphere::setName(QString name)
{
    mName = name; 
}

QString FCGeometryParaSphere::getName()
{
    return mName;    
}

void FCGeometryParaSphere::setLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaSphere::getLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

bool FCGeometryParaSphere::getRadius(double *r)
{
    *r = mRadius;
    return true;
}

void FCGeometryParaSphere::setRadius(double newRadius)
{
    mRadius = newRadius;
}

} // namespace FC

