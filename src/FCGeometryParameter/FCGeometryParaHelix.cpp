/**
 * @file FCGeometryParaHelix.cpp
 * @brief 螺旋参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaHelix.h"

namespace FC {
FCGeometryParaHelix::FCGeometryParaHelix()
{
    mType = GeometryParaCreateHelix;
}

void FCGeometryParaHelix::setName(QString name)
{
    mName = name;
}

QString FCGeometryParaHelix::getName()
{
    return mName;
}

void FCGeometryParaHelix::setLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaHelix::getLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

int FCGeometryParaHelix::numberOfturns() const
{
    return mNumberOfturns;
}

void FCGeometryParaHelix::setNumberOfturns(int newNumberOfturns)
{
    mNumberOfturns = newNumberOfturns;
}

double FCGeometryParaHelix::majorRadius() const
{
    return mMajorRadius;
}

void FCGeometryParaHelix::setMajorRadius(double newMajorRadius)
{
    mMajorRadius = newMajorRadius;
}

double FCGeometryParaHelix::minorRadius() const
{
    return mMinorRadius;
}

void FCGeometryParaHelix::setMinorRadius(double newMinorRadius)
{
    mMinorRadius = newMinorRadius;
}

double FCGeometryParaHelix::radialPitch() const
{
    return mRadialPitch;
}

void FCGeometryParaHelix::setRadialPitch(double newRadialPitch)
{
    mRadialPitch = newRadialPitch;
}

double FCGeometryParaHelix::axialPitch() const
{
    return mAxialPitch;
}

void FCGeometryParaHelix::setAxialPitch(double newAxialPitch)
{
    mAxialPitch = newAxialPitch;
}

FCGeometryParaHelix::Chirality FCGeometryParaHelix::chirality() const
{
    return mChirality;
}

void FCGeometryParaHelix::setChirality(Chirality newChirality)
{
    mChirality = newChirality;
}

}
