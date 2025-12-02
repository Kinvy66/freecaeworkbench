/**
 * @file FCGeometryModelParaBase.cpp
 * @brief 几何模型操作参数基类
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryModelParaBase.h"
#include "FCGeometryData.h"
#include "FCGeometryParaBox.h"
#include "FCGeometryParaCylinder.h"


namespace FC 
{

FCGeometryModelParaBase::FCGeometryModelParaBase()
{
    mGeoData = FCGeometryData::getInstance();

}

GeometryParaType FCGeometryModelParaBase::getParaType()
{
    return mType;
}

FCGeometryModelParaBase *FCGeometryModelParaBase::createParaByString(QString s)
{
    
    FCGeometryModelParaBase* p = nullptr;
    
    if (s == "CreateBox") p = new FCGeometryParaBox;
    else if (s == "CreateCylinder") p = new FCGeometryParaCylinder;
    // else if (s == "CreateCone") p = new GeometryParaCone;
    // else if (s == "CreateFillet") p = new GeometryParaFillet;
    // else if (s == "CreateSphere") p = new GeometryParaSphere;
    // else if (s == "CreatePoint") p = new GeometryParaPoint;
    // else if (s == "CreateLine") p = new GeometryParaLine;
    // else if (s == "CreateFace") p = new GeometryParaFace;
    // else if (s == "MakeChamfer") p = new GeometryParaChamfer;
    // else if (s == "MakeVariableFillet") p = new GeometryParaVariableFillet;
    // else if (s == "MakeBoolOperation") p = new GeometryParaBoolOperation;
    // else if (s == "MakeMirrorFeature") p = new GeometryParaMirrorFeature;
    // else if (s == "MakeRotateFeature") p = new GeometryParaRotateFeature;
    // else if (s == "MakeMoveFeature") p = new GeometryParaMakeMove;
    // else if (s == "MakeMatrix") p = new GeometryParaMatrix;
    // else if (s == "MakeExtrusion") p = new GeometryParaExtrusion;
    // else if (s == "MakeLoft") p = new GeometryParaLoft;
    // else if (s == "MakeSweep") p = new GeometryParaSweep; 
    // else if (s == "MakeRevol") p = new GeometryParaRevol;
    // else if (s == "GeoSplitter") p = new GeometryParaGeoSplitter;
    // else if (s == "FillHole") p = new GeometryParaMakeFillHole;
    // else if (s == "RemoveSurface") p = new GeometryParaMakeRemoveSurface;
    // else if (s == "FillGap") p = new GeometryParaMakeFillGap;
    return p;
    
    
}

QString FCGeometryModelParaBase::typeToString()
{
    QString stype;
    switch (mType)
    {
    case GeometryParaNone: stype = "None"; break;
    case GeometryParaCreateBox: stype = "CreateBox"; break;
    case GeometryParaCreateCylinder:stype = "CreateCylinder"; break;
    case GeometryParaCreateCone:stype = "CreateCone"; break;
    case GeometryParaCreateFillet: stype = "CreateFillet"; break;
    case GeometryParaCreateSphere: stype = "CreateSphere"; break;
    case GeometryParaCreatePoint: stype = "CreatePoint"; break;
    case GeometryParaCreateLine: stype = "CreateLine"; break;
    case GeometryParaCreateFace: stype = "CreateFace"; break;
    case GeometryParaMakeChamfer: stype = "MakeChamfer"; break;
    case GeometryParaMakeVariableFillet: stype = "MakeVariableFillet"; break;
    case GeometryParaMakeBoolOperation: stype = "MakeBoolOperation"; break;
    case GeometryParaMakeMirrorFeature:stype = "MakeMirrorFeature"; break;
    case GeometryParaMakeRotateFeature: stype = "MakeRotateFeature"; break;
    case GeometryParaMakeMoveFeature: stype = "MakeMoveFeature"; break;
    case GeometryParaMakeMatrix:stype = "MakeMatrix"; break;
    case GeometryParaMakeExtrusion:stype = "MakeExtrusion"; break;
    case GeometryParaMakeLoft:stype = "MakeLoft"; break;
    case GeometryParaMakeSweep:stype = "MakeSweep"; break;
    case GeometryParaMakeRevol:stype = "MakeRevol"; break;
    case GeometryParaSplitter:stype = "GeoSplitter"; break;
    case GeometryParaFillHole:stype = "FillHole"; break;
    case GeometryParaRemoveSurface:stype = "RemoveSurface"; break;
    case GeometryParaFillGap:stype = "FillGap"; break;
    default: 
        break;
        
    }
    
    return stype;
}

} // namespace FC
