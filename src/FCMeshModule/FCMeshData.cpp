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
#include "FCUniqueIDGenerater.h"

namespace FC 
{
FCMeshData* FCMeshData::mInstance = nullptr;

FCMeshData* FCMeshData::getInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new FCMeshData;
    }
    return mInstance;
}

FCMeshData::~FCMeshData()
{
    for (int i = 0; i < mMeshList.size(); ++i)
    {
        FCMeshKernal* k = mMeshList.at(i);
        delete k;
    }
    mMeshList.clear();
}
void FCMeshData::appendMeshKernal(FCMeshKernal* keneral)
{
    mMeshList.append(keneral);
}

void FCMeshData::appendMeshKernal(IdType id, FCMeshKernal *keneral)
{
    bool isExist = false;
    for (const auto& key : mMeshKernals.keys()) {
        if (id == key) {
            isExist = true;
        }
    }
    if (isExist) {
        qDebug() << "Modify Mesh Kernal id: " << id;
        
    } else {
        qDebug() << "Add Mesh Kernal id: " << id;
        
    }
    mMeshKernals.insert(id, keneral);
}
int FCMeshData::getKernalCount()
{
    // return mMeshList.size();
    return mMeshKernals.count();
}
FCMeshKernal* FCMeshData::getKernalAt(const int index)
{
    if(index >= 0 && index < mMeshList.size())
        return mMeshList.at(index);
    return nullptr;
}
FCMeshKernal* FCMeshData::getMeshKernalByID(const IdType  id)
{
    // const int n = mMeshList.size();
    // for (int i = 0; i < n; ++i)
    // {
    //     FCMeshKernal* k = mMeshList.at(i);
    //     if (k->getID() == id)
    //         return k;
    // }
    // return nullptr;
    
    
    if (id==0) {
        return nullptr;
    }
    FCMeshKernal* k = mMeshKernals.value(id);
    if (k->getGmshSetting()) {
        return k;
    }
    
    return nullptr;
}
void FCMeshData::removeKernalAt(const int index)
{
    FCMeshKernal* k = getKernalAt(index);
    
    delete k;
    mMeshList.removeAt(index);
}

void FCMeshData::removeKernalByID(const int id)
{
    auto k = this->getMeshKernalByID(id);
    int index = mMeshList.indexOf(k);
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
    mMeshList.clear();
    
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
    const int n = mMeshList.size();
    if (n < 1) return"";
    
    QDataStream stream;
    for (int i = 0; i < n; ++i)
    {
        mMeshList[i]->dataToStream(&stream);
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
    const int n = mMeshList.size();
    QDomElement FCMeshKernalList = doc->createElement("Kernel");
    for (int i = 0; i < n; ++i)
    {
        FCMeshKernal* k = mMeshList.at(i);
        k->writeToProjectFile(doc, &FCMeshKernalList);
    }
    meshNode.appendChild(FCMeshKernalList);
    
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
        mMeshList.append(k);
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
    const int n = mMeshList.size();
    for (int i = 0; i < n; ++i)
    {
        FCMeshKernal* k = mMeshList.at(i);
        vtkDataSet* s = k->getMeshData();
        if (s == datset)
            return k->getID();
    }
    return -1;
}

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
    return mMeshList.contains(ker);
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
    const int nk = mMeshList.size();
    *dataStream << nk;
    for (int i = 0; i < nk; ++i)
    {
        FCMeshKernal* k = mMeshList.at(i);
        k->writeBinaryFile(dataStream);
    }

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
        mMeshList.append(k);
        k->readBinaryFile(dataStream);
    }
    
    *dataStream >> ns;
    
}

} // namespace FC
