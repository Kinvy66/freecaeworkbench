/**
 * @file FCMeshBody.cpp
 * @brief 单个模型的网格，包含数据和属性
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshBody.h"
#include <vtkPoints.h>
#include <vtkCell.h>
#include <QDataStream>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomText>
#include "FCElementType.h"
#include <vtkIdList.h>
#include <vtkUnstructuredGrid.h>
#include <QDebug>

namespace FC 
{
int FCMeshBody::idOffset = 0;
int FCMeshBody::pointIDOffset = 1;
int FCMeshBody::cellIDOffset = 1;

FCMeshBody::FCMeshBody()
{
    idOffset++;
    setID(idOffset);
    _pointIDOffset = pointIDOffset;
    _cellIDOffset = cellIDOffset;
    //		_mesh = vtkSmartPointer<vtkUnstructuredGrid>::New();
    _specificColor.first = false;
    // appendProperty(QObject::tr("Visible"), _visible);
}

void FCMeshBody::setMeshData(vtkDataSet* dataset)
{
    _mesh = dataset;
    _pointIDOffset = pointIDOffset;
    _cellIDOffset = cellIDOffset;
    pointIDOffset += dataset->GetNumberOfPoints();
    cellIDOffset += dataset->GetNumberOfCells();
    // appendProperty(QObject::tr("Points"), (int)dataset->GetNumberOfPoints());
    // appendProperty(QObject::tr("Cells"), (int)dataset->GetNumberOfCells());
}

vtkDataSet* FCMeshBody::getMeshData()
{
    return _mesh;
}

double* FCMeshBody::getPointAt(const int index)
{
    return _mesh->GetPoint(index);
}

vtkCell* FCMeshBody::getCellAt(const int index)
{
    return _mesh->GetCell(index);
}

bool FCMeshBody::isVisible()
{
    return _visible;
}

void FCMeshBody::setVisible(bool v)
{
    _visible = v;
    // appendProperty(QObject::tr("Visible"), _visible);
}

void FCMeshBody::dataToStream(QDataStream* s)
{
    *s << mId << mName << _mesh->GetNumberOfPoints() << _mesh->GetNumberOfCells();
}

void FCMeshBody::setID(IdType id)
{
    FCDataBase::setID(id);
    if (id > idOffset)
        idOffset = id;
}

void FCMeshBody::setPath(const QString& path)
{
    _path = path;
}

QString FCMeshBody::getPath()
{
    return _path;
}

void FCMeshBody::setPointIDOFfset(int offset)
{
    _pointIDOffset = offset;
    if (pointIDOffset < offset)
        pointIDOffset = offset;
}

void FCMeshBody::setCellIDOFfset(int offset)
{
    _cellIDOffset = offset;
    if (_cellIDOffset < offset)
        cellIDOffset = offset;
}

QDomElement& FCMeshBody::writeToProjectFile(QDomDocument* doc, QDomElement* parent)
{
    QDomElement kernelele = doc->createElement("MeshKernel");
    QDomAttr idAttr = doc->createAttribute("ID");
    idAttr.setValue(QString::number(mId));
    kernelele.setAttributeNode(idAttr);
    QDomAttr visible = doc->createAttribute("Visible");
    visible.setValue("True");
    if (!_visible) visible.setValue("False");
    kernelele.setAttributeNode(visible);
    QDomElement nameele = doc->createElement("Name");
    QDomText nameText = doc->createTextNode(mName);
    nameele.appendChild(nameText);
    kernelele.appendChild(nameele);
    
    if (!_path.isEmpty())
    {
        QDomElement pathele = doc->createElement("Path");
        QDomText pathtext = doc->createTextNode(_path);
        pathele.appendChild(pathtext);
        kernelele.appendChild(pathele);
    }
    
    QDomElement idoffset = doc->createElement("IDOffset");
    QDomAttr nodeid = doc->createAttribute("Node");
    nodeid.setValue(QString::number(_pointIDOffset));
    QDomAttr cellid = doc->createAttribute("Cell");
    cellid.setValue(QString::number(_cellIDOffset));
    idoffset.setAttributeNode(nodeid);
    idoffset.setAttributeNode(cellid);
    kernelele.appendChild(idoffset);
    //节点
    QDomElement nodeListEle = doc->createElement("NodeList");
    const int nNode = _mesh->GetNumberOfPoints();
    for (int i = 0; i < nNode; ++i)
    {
        double* coor = _mesh->GetPoint(i);
        QDomElement node = doc->createElement("Node");
        QString s = QString("%1,%2,%3,%4").arg(i).arg(coor[0]).arg(coor[1]).arg(coor[2]);
        QDomText nodetext = doc->createTextNode(s);
        node.appendChild(nodetext);
        nodeListEle.appendChild(node);
    }
    kernelele.appendChild(nodeListEle);
    //单元
    QDomElement elementListEle = doc->createElement("ElementList");
    const int nele = _mesh->GetNumberOfCells();
    for (int i = 0; i < nele; ++i)
    {
        vtkCell* cell = _mesh->GetCell(i);
        QString stype = vtkCellTYpeToString((VTKCellType)cell->GetCellType());
        QString text = QString("%1,%2").arg(i).arg(stype);
        vtkIdList* ids = cell->GetPointIds();
        const int n = ids->GetNumberOfIds();
        QDomElement element = doc->createElement("Element");
        for (int i = 0; i < n; ++i)
        {
            int id = ids->GetId(i);
            text.append(",");
            text.append(QString("%1").arg(id));
        }
        QDomText eletext = doc->createTextNode(text);
        element.appendChild(eletext);
        elementListEle.appendChild(element);
    }
    
    kernelele.appendChild(elementListEle);
    
    parent->appendChild(kernelele);
    return kernelele;
}

void FCMeshBody::readDataFromProjectFile(QDomElement* kernelele)
{
    QString sid = kernelele->attribute("ID");
    this->setID(sid.toInt());
    QString svis = kernelele->attribute("Visible");
    bool visible = true;
    if (svis.toLower() == "false") visible = false;
    this->setVisible(visible);
    
    QDomNodeList nameNodeList = kernelele->elementsByTagName("Name");
    if (nameNodeList.size() != 1) return;
    QString name = nameNodeList.at(0).toElement().text();
    this->setName(name);
    QDomNodeList pathList = kernelele->elementsByTagName("Path");
    if (pathList.size() > 0)
    {
        QString path = pathList.at(0).toElement().text();
        this->setPath(path);
    }
    QDomNodeList idofflist = kernelele->elementsByTagName("IDOffset");
    if (idofflist.size() != 1) return;
    QDomElement idele = idofflist.at(0).toElement();
    QString spointoff = idele.attribute("Node");
    QString scelloff = idele.attribute("Cell");
    const int po = spointoff.toInt();
    const int co = scelloff.toInt();
    this->setPointIDOFfset(po);
    this->setCellIDOFfset(co);
    
    //读取网格
    vtkSmartPointer<vtkUnstructuredGrid> ung = vtkSmartPointer<vtkUnstructuredGrid>::New();
    //节点
    QDomNodeList nodelist = kernelele->elementsByTagName("Node");
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    const int nNode = nodelist.size();
    for (int i = 0; i < nNode; ++i)
    {
        QDomElement nodeele = nodelist.at(i).toElement();
        QString text = nodeele.text();
        QStringList scoor = text.split(",");
        points->InsertNextPoint(scoor[1].toDouble(), scoor[2].toDouble(), scoor[3].toDouble());
    }
    ung->SetPoints(points);
    QDomNodeList elementList = kernelele->elementsByTagName("Element");
    const int nele = elementList.size();
    for (int i = 0; i < nele; ++i)
    {
        QDomElement eleele = elementList.at(i).toElement();
        QString text = eleele.text();
        QStringList info = text.split(",");
        VTKCellType celltype = TypeStringToVTKCellType(info.at(1));
        vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
        for (int i = 2; i < info.size(); ++i)
        {
            int id = info.at(i).toInt();
            idlist->InsertNextId(id);
        }
        ung->InsertNextCell(celltype, idlist);
    }
    
    this->setMeshData(ung);
}

int FCMeshBody::getPointCount()
{
    if (_mesh != nullptr)
        
    return _mesh->GetNumberOfPoints();
    return -1;
}

int FCMeshBody::getCellCount()
{
    if (_mesh != nullptr)
        return _mesh->GetNumberOfCells();
    return -1;
}

void FCMeshBody::resetOffset()
{
    idOffset = 0;
    pointIDOffset = 1;
    cellIDOffset = 1;
}

void FCMeshBody::setDimension(int d)
{
    _dimension = d;
}

int FCMeshBody::getDimension()
{
    return _dimension;
}

void FCMeshBody::writeBinaryFile(QDataStream* dataStream)
{
    *dataStream << mId << _visible << mName << _path;
    *dataStream << _pointIDOffset << _cellIDOffset;
    
    const int nNode = _mesh->GetNumberOfPoints();
    *dataStream << nNode;;
    for (int i = 0; i < nNode; ++i)
    {
        double* coor = _mesh->GetPoint(i);
        *dataStream << i << coor[0] << coor[1] << coor[2];
    }
    
    const int nele = _mesh->GetNumberOfCells();
    *dataStream << nele;
    for (int i = 0; i < nele; ++i)
    {
        vtkCell* cell = _mesh->GetCell(i);
        int cellType = cell->GetCellType();
        vtkIdList* ids = cell->GetPointIds();
        const int n = ids->GetNumberOfIds();
        *dataStream << i << cellType << n;
        
        for (int i = 0; i < n; ++i)
        {
            int id = ids->GetId(i);
            *dataStream << id;
        }
    }
}

void FCMeshBody::readBinaryFile(QDataStream* dataStream)
{
    int KernalID = 0;                        //KernalID
    bool visible = false;                    //KernalVisible
    QString MeshName, MeshPath;              //MeshName,MeshPath
    *dataStream >> KernalID >> visible >> MeshName >> MeshPath;
    
    this->setID(KernalID);
    this->setVisible(visible);
    this->setName(MeshName);
    this->setPath(MeshPath);
    
    int nodeOffset = 0, cellOffset = 0;
    *dataStream >> nodeOffset >> cellOffset;
    this->setCellIDOFfset(cellOffset);
    this->setPointIDOFfset(nodeOffset);
    
    int nNode = 0;
    *dataStream >> nNode;
    vtkSmartPointer<vtkUnstructuredGrid> ung = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    int nodeid = 0;                                    //NodeID
    double node_x, node_y, node_z;                     //Nodecoordinate(x,y,z)
    for (int i = 0; i < nNode; ++i)
    {
        *dataStream >> nodeid >> node_x >> node_y >> node_z;
        points->InsertNextPoint(node_x, node_y, node_z);
    }
    ung->SetPoints(points);
    
    int nElement{ 0 }, eletype{ 0 }, ElementID{ 0 }, eleNodeCount{0};	//ElementNumber,ElementType,ElementID
    *dataStream >> nElement;
    for (int i = 0; i < nElement; ++i)
    {
        *dataStream >> ElementID >> eletype >>eleNodeCount;
        VTKCellType celltype = VTKCellType(eletype);
        //			int nVertex = GetNodeCountByElementType(celltype);	//不同类型的element的节点个数
        vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
        
        int id = 0;
        for (int i = 0; i < eleNodeCount; ++i)
        {
            *dataStream >> id;
            idlist->InsertNextId(id);
        }
        ung->InsertNextCell(celltype, idlist);
    }
    
    this->setMeshData(ung);
}

void FCMeshBody::setGmshSetting(FCDataBase* data)
{
    _gmshSetting = data;
}

FCDataBase* FCMeshBody::getGmshSetting()
{
    return _gmshSetting;
}

void FCMeshBody::setSpecificColor(bool enable, QColor c)
{
    _specificColor.first = enable;
    _specificColor.second = c;
}

void FCMeshBody::setSpecificColor(bool enable, double r, double g, double b, double alpha)
{
    _specificColor.first = enable;
    _specificColor.second.setRedF(r);
    _specificColor.second.setGreenF(g);
    _specificColor.second.setBlueF(b);
    _specificColor.second.setAlpha(alpha);
}

QColor FCMeshBody::getSpecificColor(bool &isEnable)
{
    isEnable = _specificColor.first;
    return _specificColor.second;
}

} // namespace FC
