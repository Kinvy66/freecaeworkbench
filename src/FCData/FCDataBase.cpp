/******************************************************************************
 * File     : FCDataBase.cpp
 * Brief    : 数据基类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-22
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCDataBase.h"
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

void FCDataBase::setID(uint64_t id)
{
    mId = id;
    
}

/**
 * @brief 获取数据的ID值
 * @return int 返回ID值
 */
int64_t FCDataBase::getID() const
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

QDomElement &FCDataBase::writeToProjectFile(QDomDocument *doc, QDomElement *parent)
{
    // todo
    static QDomElement dummy;  
    return dummy;
}

void FCDataBase::readDataFromProjectFile(QDomElement *e)
{
    
}

void FCDataBase::readParameters(QDomElement *ele)
{
    
}

void FCDataBase::writeParameters(QDomDocument *doc, QDomElement *parent)
{
    
}

QString FCDataBase::getName()
{
    return "FFFF";
}

} // namespace FC

