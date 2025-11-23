/**
 * @file FCGeometrySet.cpp
 * @brief 几何形状表示类
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometrySet.h"

#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDomAttr>
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QString>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shape.hxx>
#include <vtkDataSet.h>
#include <vtkDataSetWriter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>

namespace FC 
{
int FCGeometrySet::s_idOffset = 0;
TopoDS_Shape* FCGeometrySet::s_tempShape = new TopoDS_Shape;

FCGeometrySet::FCGeometrySet(GeometryType type)
    : mType(type)
{
    
}

FCGeometrySet::~FCGeometrySet()
{
    if (mShape != nullptr) {
        delete mShape;
    }
    if (mParameter != nullptr) {
        delete mParameter;
    }
}

void FCGeometrySet::setID(int id)
{
    FCDataBase::setID(id);
  
}

TopoDS_Shape *FCGeometrySet::getShape(int type, int index)
{
    *s_tempShape = TopoDS_Shape();
    TopAbs_ShapeEnum shapeType;
    switch(type) {
    case 1:
        shapeType = TopAbs_VERTEX;
        break;
    case 2:
        shapeType = TopAbs_EDGE;
        break;
    case 3:
        shapeType = TopAbs_FACE;
        break;
    case 4:
        shapeType = TopAbs_SOLID;
        break;
    default:
        return s_tempShape;
    }
    TopExp_Explorer ptExp(*mShape, shapeType);
    for(int i = 0; ptExp.More(); ptExp.Next(), ++i) {
        if(i == index) {
            *s_tempShape = ptExp.Current();
            break;
        }
    }
    return s_tempShape;
}

const TopoDS_Shape &FCGeometrySet::getRealShape(int type, int index)
{
    *s_tempShape = TopoDS_Shape();
    TopAbs_ShapeEnum shapeType;
    switch(type) {
    case 1:
        shapeType = TopAbs_VERTEX;
        break;
    case 2:
        shapeType = TopAbs_EDGE;
        break;
    case 3:
        shapeType = TopAbs_FACE;
        break;
    case 4:
        shapeType = TopAbs_SOLID;
        break;
    default:
        return *s_tempShape;
    }
    TopExp_Explorer ptExp(*mShape, shapeType);
    for(int i = 0; ptExp.More(); ptExp.Next(), ++i) {
        if(i == index)
            *s_tempShape = ptExp.Current();
    }
    return *s_tempShape;
}

void FCGeometrySet::setVisible(bool v)
{
    mVisible = v;
    
}

void FCGeometrySet::setType(GeometryType type)
{
    mType = type;
}

void FCGeometrySet::setShape(TopoDS_Shape *shape)
{
    mShape = shape;
    int i = 0;
    for(TopExp_Explorer faceExp(*shape, TopAbs_FACE);
         faceExp.More(); faceExp.Next()) {
        ++i;        
    }
    qDebug() << "surface number: " << i;
}

TopoDS_Shape *FCGeometrySet::getShape()
{
    return mShape;
}

void FCGeometrySet::setPoly(vtkPolyData *poly)
{
    mPolyData = poly;
}

vtkPolyData *FCGeometrySet::getPoly()
{
    return mPolyData;
}

void FCGeometrySet::setParameter(FCGeometryModelParaBase *p)
{
    mParameter = p;
}

void FCGeometrySet::dataToStream(QDataStream *s)
{
    // todo
}

bool FCGeometrySet::writeBrep(QString name)
{
    QByteArray		arr = name.toLatin1();
    char*			ch	= arr.data();
    
    TopoDS_Compound aRes;
    BRep_Builder	aBuilder;
    aBuilder.MakeCompound(aRes);
    
    if(mShape == nullptr)
        return false;
    aBuilder.Add(aRes, *mShape);
    
    return BRepTools::Write(aRes, ch);
}

bool FCGeometrySet::writePoly(QString name)
{
    QByteArray		  arr = name.toLatin1();
    char*			  ch  = arr.data();
    
    vtkDataSetWriter* w	  = vtkDataSetWriter::New();
    w->SetInputData(mPolyData);
    w->SetFileName(ch);
    w->SetFileTypeToBinary();
    w->Update();
    w->Delete();
    
    return true;
}

bool FCGeometrySet::readBrep(QString name)
{
    QByteArray	  arr	 = name.toLatin1();
    char*		  ch	 = arr.data();
    TopoDS_Shape* ashape = new TopoDS_Shape;
    BRep_Builder  builder;
    BRepTools::Read(*ashape, (const Standard_CString)ch, builder);
    if(ashape->IsNull()) {
        delete ashape;
        return false;
    }
    mShape = ashape;
    return true;
}

bool FCGeometrySet::readPoly(QString name)
{
    QByteArray arr = name.toLatin1();
    char*	   ch  = arr.data();
    mPolyData	   = vtkPolyData::New();
    auto reader	   = vtkPolyDataReader::New();
    reader->SetFileName(ch);
    reader->Update();
    auto poly = reader->GetOutput();
    int	 n	  = poly->GetNumberOfCells();
    mPolyData->DeepCopy(reader->GetOutput());
    reader->Delete();
    return true;
}



} // namespace FC
