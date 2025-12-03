/**
 * @file FCGeometrySet.cpp
 * @brief 几何形状表示类
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometrySet.h"
#include "FCGeometryModelParaBase.h"

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

FCGeometrySet::FCGeometrySet(GeometryType type,  bool needID)
    : mType(type)
{
    if (needID) {
        s_idOffset++;
        setID(s_idOffset);        
    }
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
/**
 * @brief 设置id
 * @param id
 */ 
void FCGeometrySet::setID(IdType id)
{
    FCDataBase::setID(id);
    if(id > s_idOffset)
        s_idOffset = id;
}

/**
 * @brief 重置最大id
 * @note 不用轻易调用
 */
void FCGeometrySet::resetMaxID()
{
    s_idOffset = 0;
}

/**
 * @brief 获取最大id
 * @return 
 */
int FCGeometrySet::getMaxID()
{
    return s_idOffset;
}

/**
 * @brief 获取topo数据
 * @param type
 * @param index
 * @return 
 */
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

/**
 * @brief 获取形状
 * @param type
 * @param index
 * @return 
 */
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

/**
 * @brief 设置可见
 * @param v
 */
void FCGeometrySet::setVisible(bool v)
{
    mVisible = v;
    
}

/**
 * @brief 是否可见
 * @return 
 */
bool FCGeometrySet::isVisible()
{
    return true;
}

/**
 * @brief 设置类型
 * @param type
 */
void FCGeometrySet::setType(GeometryType type)
{
    mType = type;
}

GeometryType FCGeometrySet::getType()
{
    return mType;
}

/**
 * @brief 设置形状的拓扑
 * @param shape
 */
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

/**
 * @brief 获取形状的拓扑
 * @return 
 */
TopoDS_Shape *FCGeometrySet::getShape()
{
    return mShape;
}

/**
 * @brief 设置poly data
 * @param poly
 */
void FCGeometrySet::setPoly(vtkPolyData *poly)
{
    mPolyData = poly;
}

/**
 * @brief 获取poly data
 * @return 
 */
vtkPolyData *FCGeometrySet::getPoly()
{
    return mPolyData;
}


/**
 * @brief 根据ID获取子形状
 * @param id 要获取ID的子形状
 * @return GeometrySet* 返回的子形状
 */
FCGeometrySet *FCGeometrySet::getSetByID(IdType id)
{
    FCGeometrySet* s = nullptr;
    if(id == mId) {
        s = this;        
    }
    // else {
    //     const int n = _subSetList.size();
    //     for(int i = 0; i < n; ++i) {
    //         GeometrySet* temp = _subSetList.at(i);
    //         if(id == temp->getID()) {
    //             s = temp;
    //             break;
    //         }
    //     }
    // }
    return s;
}

/**
 * @brief 设置操作参数
 * @param p
 */
void FCGeometrySet::setParameter(FCGeometryModelParaBase *p)
{
    mParameter = p;
}

FCGeometryModelParaBase *FCGeometrySet::getParameter()
{
    return mParameter;
}

/**
 * @brief 转成流数据
 * @param s
 */
void FCGeometrySet::dataToStream(QDataStream *s)
{
    // todo
}

/**
 * @brief 写出brep文件
 * @param name 要写出的brep文件
 * @return bool 返回写出结果
 */
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

/**
 * @brief 写出vtk文件
 * @param name
 * @return 
 */
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

/**
 * @brief 读入brep文件
 * @param name 要读取的brep文件
 * @attention 路径不能出现中文
 * @return bool 返回读取结果
 */
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

/**
 * @brief 读入vtk文件
 * @param name
 * @return 
 */
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

/**
 * @brief 写出几何到工程文件
 * @param doc
 * @param ele
 * @param isDisp
 * @return 
 */
QDomElement &FCGeometrySet::writeToProjectFile(QDomDocument *doc, QDomElement *ele, bool isDiso)
{
    QDomElement element = doc->createElement("GeometrySet"); // 创建子节点
    QDomAttr	idattr	= doc->createAttribute("ID");
    idattr.setValue(QString::number(mId));
    element.setAttributeNode(idattr);
    QDomAttr visible = doc->createAttribute("Visible");
    visible.setValue("True");
    if(!mVisible)
        visible.setValue("False");
    element.setAttributeNode(visible);
    
    QDomAttr isSTL = doc->createAttribute("ISSTL");
    isSTL.setValue("True");
    if(mType != STL)
        isSTL.setValue("False");
    element.setAttributeNode(isSTL);
    
    QDomAttr fileAttr = doc->createAttribute("File");
    fileAttr.setValue(QString("geometry/%1_%2").arg(mName).arg(mId));
    element.setAttributeNode(fileAttr);
    
    QDomElement nameele	 = doc->createElement("Name");
    QDomText	nameText = doc->createTextNode(mName);
    nameele.appendChild(nameText);
    element.appendChild(nameele);
    // QDomElement pathele = doc->createElement("Path");
    // QDomText pathtext = doc->createTextNode(_filePath);
    // pathele.appendChild(pathtext);
    // element.appendChild(pathele);
    
    ele->appendChild(element); // 子节点挂载
    // todo
    if(mParameter != nullptr)
        mParameter->writeToProjectFile(doc, &element);
    
    // if(isDiso) {
    //     QString		  exelPath = QCoreApplication::applicationDirPath();
    //     const QString tempPath = exelPath + "/../tempIO/" + QString("%1.brep").arg(_id);
    //     if(mType != STL)
    //         this->writeBrep(tempPath);
    //     else
    //         this->writePoly(tempPath);
    // }
    return element;
}

/**
 * @brief 从工程文件几何读入
 * @param e
 * @param isDiso
 */
void FCGeometrySet::readDataFromProjectFile(QDomElement *e, bool isDiso)
{
    
}



} // namespace FC
