/**
 * @file FCMeshData.cpp
 * @brief 全局网格数据管理类
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshData.h"
#include "FCMeshKernal.h"
#include <assert.h>
#include <QDataStream>
#include <QCryptographicHash>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QFileInfo>
#include <QDebug>

namespace FC 
{
FCMeshData* FCMeshData::_instance = nullptr;

FCMeshData* FCMeshData::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new FCMeshData;
    }
    return _instance;
}

FCMeshData::~FCMeshData()
{
    for (int i = 0; i < _meshList.size(); ++i)
    {
        FCMeshKernal* k = _meshList.at(i);
        delete k;
    }
    _meshList.clear();
}
void FCMeshData::appendMeshBody(FCMeshKernal* keneral)
{
    _meshList.append(keneral);
}
int FCMeshData::getKernalCount()
{
    return _meshList.size();
}
FCMeshKernal* FCMeshData::getKernalAt(const int index)
{
    if(index >= 0 && index < _meshList.size())
        return _meshList.at(index);
    return nullptr;
}
FCMeshKernal* FCMeshData::getKernalByID(const int id)
{
    const int n = _meshList.size();
    for (int i = 0; i < n; ++i)
    {
        FCMeshKernal* k = _meshList.at(i);
        if (k->getID() == id)
            return k;
    }
    return nullptr;
}
void FCMeshData::removeKernalAt(const int index)
{
    FCMeshKernal* k = getKernalAt(index);
    
    // QList<MeshSet*> setlist{};
    // for (int i = 0; i < _setList.size(); ++i)
    // {
    //     MeshSet* s = _setList.at(i);
    //     //			if (s->getDataSetID() == k->getID())
    //     int kid = k->getID();
    //     if (s->isContainsKernal(kid))
    //         setlist.append(s);
    // }
    // for (int i = 0; i < setlist.size(); ++i)
    // {
    //     MeshSet* s = setlist.at(i);
    //     _setList.removeOne(s);
    //     delete s;
    // }
    
    delete k;
    _meshList.removeAt(index);
}

void FCMeshData::removeKernalByID(const int id)
{
    auto k = this->getKernalByID(id);
    int index = _meshList.indexOf(k);
    if (index < 0) return;
    this->removeKernalAt(index);
}

void FCMeshData::clear()
{
    int n = this->getKernalCount();
    for (int i = 0; i < n; ++i)
    {
        FCMeshKernal* k = this->getKernalAt(i);
        delete k;
    }
    _meshList.clear();
    
    // n = _setList.size();
    // for (int i = 0; i < n; ++i)
    // {
    //     MeshSet *s = _setList.at(i);
    //     delete s;
    // }
    // _setList.clear();
    
    FCMeshKernal::resetOffset();
    // DataProperty::ComponentBase::resetMaxID();
}
QString FCMeshData::getMD5()
{
    const int n = _meshList.size();
    if (n < 1) return"";
    
    QDataStream stream;
    for (int i = 0; i < n; ++i)
    {
        _meshList[i]->dataToStream(&stream);
    }
    // for (auto set : _setList)
    // {
    //     set->dataToStream(&stream);
    // }
    
    char* s;
    stream >> s;
    QString md5 = QCryptographicHash::hash(s, QCryptographicHash::Md5);
    return md5;
}
QDomElement& FCMeshData::writeToProjectFile(QDomDocument* doc, QDomElement* parent)
{
    QDomElement meshNode = doc->createElement("Mesh");
    const int n = _meshList.size();
    QDomElement FCMeshKernalList = doc->createElement("Kernel");
    for (int i = 0; i < n; ++i)
    {
        FCMeshKernal* k = _meshList.at(i);
        k->writeToProjectFile(doc, &FCMeshKernalList);
    }
    meshNode.appendChild(FCMeshKernalList);
    
    // const int nset = _setList.size();
    // QDomElement setList = doc->createElement("Set");
    // for (int i = 0; i < nset; ++i)
    // {
    //     MeshSet* s = _setList.at(i);
    //     s->writeToProjectFile(doc, &setList);
    // }
    // meshNode.appendChild(setList);
    
    parent->appendChild(meshNode);
    return meshNode;
}
void FCMeshData::readFromProjectFile(QDomNodeList* nodelist)
{
    QDomElement meshRoot = nodelist->at(0).toElement();
    QDomNodeList meshList = meshRoot.elementsByTagName("MeshKernel");
    const int nMesh = meshList.size();
    for (int i = 0; i < nMesh; ++i)
    {
        QDomElement meshKernelEle = meshList.at(i).toElement();
        // 			QDomNodeList pathlist = meshKernelEle.elementsByTagName("Path");
        // 			if (pathlist.size() != 1) continue;
        // 			QDomElement pathele = pathlist.at(0).toElement();
        // 			QString fpath = pathele.text();
        // 			QFileInfo finfo(fpath);
        // 			if (!finfo.exists()) return;
        // 			QString suffix = finfo.suffix().toLower();
        // 			if (suffix == "vtk" || suffix == "stl")
        // 			{
        // 				VTKdataExchange reader(fpath);
        // 				if (!reader.read()) continue;
        // 			}
        // 			else if (suffix == "neu")
        // 			{
        // 				NEUdataExchange reader(fpath);
        // 				if (!reader.read()) continue;
        // 			}
        FCMeshKernal* k = new FCMeshKernal;
        _meshList.append(k);
        k->readDataFromProjectFile(&meshKernelEle);
    }
    // QDomNodeList setList = meshRoot.elementsByTagName("MeshSet");
//     const int nSet = setList.size();
//     for (int i = 0; i < nSet; ++i)
//     {
//         MeshSet* s = nullptr;
//         QDomElement setEle = setList.at(i).toElement();
//         QString type = setEle.attribute("Type");
//         if (type == "CgnsBCZone")
//         {
//             s = new CgnsBCZone;
//         }
//         else if (type == "CgnsFamily")
//         {
//             s = new CgnsFamily;
//         }
//         else
//         {
//             s = new MeshSet;
//         }
        
//         _setList.append(s);
//         s->readDataFromProjectFile(&setEle);
//         //			s->generateDisplayDataSet();
//     }
}
int FCMeshData::getIDByDataSet(vtkDataSet* datset)
{
    const int n = _meshList.size();
    for (int i = 0; i < n; ++i)
    {
        FCMeshKernal* k = _meshList.at(i);
        vtkDataSet* s = k->getMeshData();
        if (s == datset)
            return k->getID();
    }
    return -1;
}
// void FCMeshData::appendMeshSet(MeshSet* s)
// {
//     _setList.append(s);
// }
// int FCMeshData::getMeshSetCount()
// {
//     return _setList.size();
// }
// MeshSet* FCMeshData::getMeshSetAt(const int index)
// {
//     assert(index >= 0 && index < _setList.size());
//     return _setList.at(index);
// }
// MeshSet* FCMeshData::getMeshSetByID(const int id)
// {
//     const int n = _setList.size();
//     for (int i = 0; i < n; ++i)
//     {
//         MeshSet* set = _setList.at(i);
//         int sid = set->getID();
//         if (sid == id) return set;
//     }
//     return nullptr;
// }
// MeshSet* FCMeshData::getMeshSetByName(const QString name)
// {
//     const int n = _setList.size();
//     for (int i = 0; i < n; ++i)
//     {
//         MeshSet* set = _setList.at(i);
//         QString n = set->getName();
//         if (name == n) return set;
//     }
//     return nullptr;
    
// }
// void FCMeshData::removeMeshSetAt(const int index)
// {
//     assert(index >= 0 && index < _setList.size());
//     MeshSet* s = _setList.at(index);
//     delete s;
//     _setList.removeAt(index);
// }
QList<int> FCMeshData::getSetIDFromKernal(int kid)
{
    QList<int> ids;
    // int n = _setList.size();
    // for (int i = 0; i < n; ++i)
    // {
    //     MeshSet* set = _setList.at(i);
    //     //int id = set->getDataSetID();
    //     //if (id == kid)
    //     if (set->isContainsKernal(kid))
    //         ids.append(set->getID());
    // }
    return ids;
}

bool FCMeshData::isContainsKernal(FCMeshKernal* ker)
{
    return _meshList.contains(ker);
}

void FCMeshData::generateDisplayDataSet()
{
    // const int n = this->getMeshSetCount();
    // for (int i = 0; i < n; ++i)
    // {
    //     MeshSet* s = this->getMeshSetAt(i);
    //     s->generateDisplayDataSet();
    // }
}

void FCMeshData::writeBinaryFile(QDataStream* dataStream)
{
    //写出二进制文件
    const int nk = _meshList.size();
    *dataStream << nk;
    for (int i = 0; i < nk; ++i)
    {
        FCMeshKernal* k = _meshList.at(i);
        k->writeBinaryFile(dataStream);
    }
    
    // const int ns = _setList.size();
    // *dataStream << ns;
    // for (int i = 0; i < ns; ++i)
    // {
    //     MeshSet* s = _setList.at(i);
    //     s->writeBinaryFile(dataStream);
    // }
}

void FCMeshData::readBinaryFile(QDataStream* dataStream)
{
    //读入二进制文件
    int nk = 0;
    int ns = 0;
    *dataStream >> nk;
    for (int i = 0; i < nk; ++i)
    {
        FCMeshKernal* k = new FCMeshKernal;
        _meshList.append(k);
        k->readBinaryFile(dataStream);
    }
    
    *dataStream >> ns;
    // for (int i = 0; i < ns; ++i)
    // {
    //     int type = 0;
    //     *dataStream >> type;
    //     MeshSet* s = MeshFactory::CreateMeshSet(type);
    //     // 			switch (type)
    //     // 			{
    //     // 			case 1:
    //     // 			case 2: s = new MeshSet(QString(), SetType(type)); break;
    //     // 			case 3: s = new CgnsFamily; break;
    //     // 			case 4: s = new CgnsBCZone; break;
    //     // 			default:break;
    //     // 			}
    //     if (s == nullptr) continue;
    //     _setList.append(s);
    //     s->readBinaryFile(dataStream);
    // }
}

} // namespace FC
