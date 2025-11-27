/**
 * @file FCGeometryParaCylinder.cpp
 * @brief 圆柱体参数
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaCylinder.h"
#include <QDomElement>
#include <QDomDocument>
#include <QDomAttr>
#include <QDebug>

namespace FC 
{

FCGeometryParaCylinder::FCGeometryParaCylinder()
{
    mType = GeometryParaCreateCylinder;
}

void FCGeometryParaCylinder::setName(QString name)
{
    mName = name;
}

QString FCGeometryParaCylinder::getName()
{
    return mName;
    
}

void FCGeometryParaCylinder::setLocation(double* loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaCylinder::getLocation(double* loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

void FCGeometryParaCylinder::setRadius(double* r)
{
    mRadius = *r;
}

void FCGeometryParaCylinder::getRadius(double* r)
{
    *r = mRadius;
}

void FCGeometryParaCylinder::setLength(double* l)
{
    mLength = *l;
}

void FCGeometryParaCylinder::getLength(double* l)
{
    *l = mLength;
}

void FCGeometryParaCylinder::setDirection(double* dir)
{
    for (int i = 0; i < 3;++i)
    {
        mDirection[i] = dir[i];
    }
}

void FCGeometryParaCylinder::getDirection(double* dir)
{
    for (int i = 0; i < 3;++i)
    {
        dir[i] = mDirection[i];
    }
    
}

} // namespace FC
