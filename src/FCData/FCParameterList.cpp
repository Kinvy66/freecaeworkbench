/**
 * @file FCParameterList.cpp
 * @brief 参数列表
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCParameterList.h"#include <QDomElement>
#include <QDomNodeList>
#include <QDomDocument>
#include "FCParameterInt.h"
#include "FCParameterDouble.h"
#include "FCParameterBool.h"
#include "FCParameterSelectable.h"
#include "FCParameterTable.h"
#include "FCParameterString.h"
#include "FCParameterPath.h"
#include "FCParameterColor.h"
#include "FCDataBase.h"
#include <QDebug>
#include <QDataStream>

namespace FC 
{

FCParameterList::~FCParameterList()
{

}

void FCParameterList::copy(FCParameterList *data)
{
    
}

void FCParameterList::appendParameter(FCParameterBase *para)
{
    
}

FCParameterBase *FCParameterList::appendParameter(ParaType type)
{
    return nullptr;
}

FCParameterBase *FCParameterList::getParameterAt(const int i)
{
    return nullptr;
}

int FCParameterList::getParameterCount()
{
    return -1;
}

int FCParameterList::getVisibleParaCount()
{
    return -1;
}

void FCParameterList::removeParameter(FCParameterBase *p)
{
    
}

void FCParameterList::removeParameterAt(int i)
{
    
}

FCParameterBase *FCParameterList::getVisibleParameterAt(const int i)
{
    return nullptr;
}

FCParameterBase *FCParameterList::createParameterByType(ParaType t)
{
    return nullptr;
}

FCParameterBase *FCParameterList::createParameterByType(QString stype)
{
    return nullptr;
}

FCParameterBase *FCParameterList::copyParameter(FCParameterBase *p)
{
    return nullptr;
}

void FCParameterList::writeParameters(QDomDocument *doc, QDomElement *parent)
{
    const int n = this->getParameterCount();
    for (int i = 0; i < n; ++i)
    {
        FCParameterBase* p = _paraList.at(i);
        if (p == nullptr) continue;
        QDomElement ele = doc->createElement("Parameter");
        p->writeParameter(doc, &ele);
        parent->appendChild(ele);
    }
}

void FCParameterList::readParameters(QDomElement *ele)
{
    
}

FCParameterBase *FCParameterList::getParameterByName(QString name)
{
    return nullptr;
}

void FCParameterList::dataToStream(QDataStream *datas)
{
    
}

QList<FCParameterBase *> FCParameterList::getParaList()
{
    QList<FCParameterBase *> temp;
    return temp;
}

} // namespace FC
