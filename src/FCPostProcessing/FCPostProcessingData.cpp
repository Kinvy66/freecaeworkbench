/**
 * @file FCPostProcessingData.cpp
 * @brief 全局后处理数据管理类
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingData.h"
#include "FCPostProcessingKernal.h"
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
FCPostProcessingData* FCPostProcessingData::mInstance = nullptr;

FCPostProcessingData* FCPostProcessingData::getInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new FCPostProcessingData;
    }
    return mInstance;
}

FCPostProcessingData::~FCPostProcessingData()
{
    for (int i = 0; i < mPostProcessingList.size(); ++i)
    {
        FCPostProcessingKernal* k = mPostProcessingList.at(i);
        delete k;
    }
    mPostProcessingList.clear();
}

void FCPostProcessingData::appendPostProcessingKernal(FCPostProcessingKernal* keneral)
{
    mPostProcessingList.append(keneral);
}

void FCPostProcessingData::appendPostProcessingKernal(IdType id, FCPostProcessingKernal* keneral)
{
    bool isExist = false;
    for (const auto& key : mPostProcessingKernals.keys()) {
        if (id == key) {
            isExist = true;
        }
    }
    if (isExist) {
        qDebug() << "Modify PostProcessing Kernal id: " << id;
    } else {
        qDebug() << "Add PostProcessing Kernal id: " << id;
    }
    mPostProcessingKernals.insert(id, keneral);
}

int FCPostProcessingData::getKernalCount()
{
    return mPostProcessingKernals.count();
}

FCPostProcessingKernal* FCPostProcessingData::getKernalAt(const int index)
{
    if(index >= 0 && index < mPostProcessingList.size())
        return mPostProcessingList.at(index);
    return nullptr;
}

FCPostProcessingKernal* FCPostProcessingData::getPostProcessingKernalByID(const IdType id)
{
    FCPostProcessingKernal* k = mPostProcessingKernals.value(id, nullptr);
    return k;
}

QList<FCDataBase::IdType> FCPostProcessingData::getAllPostProcessingID()
{
    return mPostProcessingKernals.keys();
}

void FCPostProcessingData::removeKernalAt(const int index)
{
    FCPostProcessingKernal* k = getKernalAt(index);
    delete k;
    mPostProcessingList.removeAt(index);
}

void FCPostProcessingData::removeKernalByID(const IdType id)
{
    mPostProcessingKernals.remove(id);
}

void FCPostProcessingData::clear()
{
    int n = this->getKernalCount();
    for (int i = 0; i < n; ++i)
    {
        FCPostProcessingKernal* k = this->getKernalAt(i);
        delete k;
    }
    mPostProcessingList.clear();
    
    FCPostProcessingKernal::resetOffset();
}

QString FCPostProcessingData::getMD5()
{
    const int n = mPostProcessingList.size();
    if (n < 1) return "";
    
    QDataStream stream;
    for (int i = 0; i < n; ++i)
    {
        mPostProcessingList[i]->dataToStream(&stream);
    }
    
    char* s;
    stream >> s;
    QString md5 = QCryptographicHash::hash(s, QCryptographicHash::Md5);
    return md5;
}

QDomElement& FCPostProcessingData::writeToProjectFile(QDomDocument* doc, QDomElement* parent)
{
    QDomElement postNode = doc->createElement("PostProcessing");
    const int n = mPostProcessingList.size();
    QDomElement FCPostProcessingKernalList = doc->createElement("Kernel");
    for (int i = 0; i < n; ++i)
    {
        FCPostProcessingKernal* k = mPostProcessingList.at(i);
        k->writeToProjectFile(doc, &FCPostProcessingKernalList);
    }
    postNode.appendChild(FCPostProcessingKernalList);
    
    parent->appendChild(postNode);
    return postNode;
}

void FCPostProcessingData::readFromProjectFile(QDomNodeList* nodelist)
{
    QDomElement postRoot = nodelist->at(0).toElement();
    QDomNodeList postList = postRoot.elementsByTagName("PostProcessingKernal");
    const int nPost = postList.size();
    for (int i = 0; i < nPost; ++i)
    {
        QDomElement postKernelEle = postList.at(i).toElement();
        FCPostProcessingKernal* k = new FCPostProcessingKernal;
        mPostProcessingList.append(k);
        k->readDataFromProjectFile(&postKernelEle);
    }
}

int FCPostProcessingData::getIDByDataSet(vtkDataSet* datset)
{
    const int n = mPostProcessingList.size();
    for (int i = 0; i < n; ++i)
    {
        FCPostProcessingKernal* k = mPostProcessingList.at(i);
        vtkDataSet* s = k->getPostProcessingData();
        if (s == datset)
            return k->getID();
    }
    return -1;
}

bool FCPostProcessingData::isContainsKernal(const IdType id)
{
    return mPostProcessingKernals.contains(id);
}

void FCPostProcessingData::writeBinaryFile(QDataStream* dataStream)
{
    const int nk = mPostProcessingList.size();
    *dataStream << nk;
    for (int i = 0; i < nk; ++i)
    {
        FCPostProcessingKernal* k = mPostProcessingList.at(i);
        k->writeBinaryFile(dataStream);
    }
}

void FCPostProcessingData::readBinaryFile(QDataStream* dataStream)
{
    int nk = 0;
    *dataStream >> nk;
    for (int i = 0; i < nk; ++i)
    {
        FCPostProcessingKernal* k = new FCPostProcessingKernal;
        mPostProcessingList.append(k);
        k->readBinaryFile(dataStream);
    }
}

} // namespace FC

