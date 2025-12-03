/**
 * @file FCDataBase.cpp
 * @brief 数据基类
 * @date 2025-11-22
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCDataBase.h"
#include "FCParameterGroup.h"
#include <QDomElement>
#include <QDomNodeList>
#include <QDebug>
// #include "FCUniqueIDGenerater.h"

namespace FC 
{
/**
 * @brief 设置数据的ID值
 * @param id ID值
 */
void FCDataBase::copy(FCDataBase *data)
{
    
}

void FCDataBase::setID(IdType id)
{
    mId = id;
    
}

/**
 * @brief 获取数据的ID值
 * @return int 返回ID值
 */
FCDataBase::IdType FCDataBase::getID() const
{
    return mId;
}

/**
 * @brief 设置数据的名称
 * @param name 名称
 */
void FCDataBase::setName(const QString &name)
{
    mName = name;
}

/**
 * @brief 获取数据的名称
 * @return QString 返回名称
 */
QString FCDataBase::getName() const
{
    return mName;
}

void FCDataBase::dataToStream(QDataStream *datas)
{
    
}

QDomElement &FCDataBase::writeToProjectFile(QDomDocument *doc, QDomElement *ele)
{

    this->writeParameters(doc, ele);
    return *ele;
}

void FCDataBase::readDataFromProjectFile(QDomElement *e)
{
    
}

void FCDataBase::readParameters(QDomElement *ele)
{
    
}

/**
 * @brief 参数写出
 * @param doc
 * @param parent
 */
void FCDataBase::writeParameters(QDomDocument *doc, QDomElement *parent)
{
    const int ngroup = mParaGroupList.size();
    for (int i = 0; i < ngroup; ++i)
    {
        FCParameterGroup *g = mParaGroupList.at(i);
        g->writeParameters(doc, parent);
    }
    FCParameterList::writeParameters(doc, parent);
}

QString FCDataBase::getName()
{
    return mName;
}

} // namespace FC

