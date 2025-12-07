/**
 * @file FCGeometryParaCone.cpp
 * @brief 圆锥参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaCone.h"

namespace FC 
{

FCGeometryParaCone::FCGeometryParaCone()
{
     mType = GeometryParaCreateCone;
}

void FCGeometryParaCone::setName(QString name)
{
    mName = name;
}

QString FCGeometryParaCone::getName()
{
    return mName;
}

void FCGeometryParaCone::setLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaCone::getLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

void FCGeometryParaCone::setHeigth(double para)
{
    mHeigth = para;
}

bool FCGeometryParaCone::getHeigth(double *para)
{
    *para = mHeigth;
    return true;
}

void FCGeometryParaCone::setBottomRadius(double para)
{
    mBottomRadius = para;
}

bool FCGeometryParaCone::getBottomRadius(double *para)
{
    *para = mBottomRadius;
    return true;
    
}

void FCGeometryParaCone::setTopRadius(double para)
{
    mTopRadius = para;
}

bool FCGeometryParaCone::getTopRadius(double *para)
{
    *para = mTopRadius;
    return true;    
}

void FCGeometryParaCone::setAxis(double *dir)
{
    for (int i = 0; i < 3;++i)
    {
        mAxis[i] = dir[i];
    }
}

void FCGeometryParaCone::getAxis(double *dir)
{
    for (int i = 0; i < 3;++i)
    {
        dir[i] = mAxis[i];
    }
}

QDomElement &FCGeometryParaCone::writeToProjectFile(QDomDocument *doc, QDomElement *parent)
{
    QDomElement element = doc->createElement("Parameter"); //创建子节点
    return element;
    
}

void FCGeometryParaCone::readDataFromProjectFile(QDomElement *e)
{

}

} // namespace FC
