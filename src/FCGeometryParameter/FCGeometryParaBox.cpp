/**
 * @file FCGeometryParaBox.cpp
 * @brief 立方体参数
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaBox.h"

namespace FC 
{

FCGeometryParaBox::FCGeometryParaBox()
{
    mType = GeometryParaCreateBox;
}

void FCGeometryParaBox::setName(QString name)
{
    mName = name;
}

QString FCGeometryParaBox::getName()
{
    return mName;
}

void FCGeometryParaBox::setLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaBox::getLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

void FCGeometryParaBox::setGeoPara(double *para)
{
    for (int i = 0; i < 3; ++i)
        mGeoPara[i] = para[i];
}

void FCGeometryParaBox::getGeoPara(double *para)
{
    for (int i = 0; i < 3; ++i)
        para[i] = mGeoPara[i];
}

} // namespace FC
