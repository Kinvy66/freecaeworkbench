/**
 * @file FCGeometryDatum.cpp
 * @brief 基准（参考）形状类
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryDatum.h"
#include <QDomDocument>
#include <QDomElement>
#include <QCoreApplication>

namespace FC 
{

FCGeometryDatum::FCGeometryDatum()
    : FCGeometrySet(DATUM)
{
    
}

FCGeometryDatum::~FCGeometryDatum()
{
}

void FCGeometryDatum::setDatumType(DatumType t)
{
    mType = t;    
}

DatumType FCGeometryDatum::getDatumType()
{
    return mType;
}

// QDomElement &FCGeometryDatum::writeToProjectFile(QDomDocument *doc, QDomElement *ele, bool isDisp)
// {
    
// }

// void FCGeometryDatum::readDataFromProjectFile(QDomElement *e, bool isDiso)
// {
    
// }

QString FCGeometryDatum::datumTypeToString(DatumType t)
{
    QString stype = "None";
    switch (t)
    {
    case DatumNone: break;
    case DatumPoint:
        stype = "DatumPoint"; break;
    case DatumAxis:
        stype = "DatumAxis"; break;
    case DatumPlane:
        stype = "DatumPlane"; break;
    default: break;
    }
    return stype;
}

DatumType FCGeometryDatum::datumTypeFromString(QString s)
{
    DatumType t= DatumNone;
    s = s.toLower();
    if (s == "datumpoint")
        t = DatumPoint;
    else if (s == "datumaxis")
        t = DatumAxis;
    else if (s == "datumplane")
        t = DatumPlane;
    return t;
}

} // namespace FC

