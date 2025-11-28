/**
 * @file FCParameterGroup.cpp
 * @brief 参数组类
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCParameterGroup.h"

namespace FC 
{

FCParameterGroup::~FCParameterGroup()
{
    
}

void FCParameterGroup::copy(FCParameterGroup *data)
{
    
}

void FCParameterGroup::appendParameter(FCParameterBase *p)
{
    
}

FCParameterBase *FCParameterGroup::appendParameter(ParaType type)
{
    return nullptr;
}

void FCParameterGroup::setDescribe(QString des)
{
}

QString FCParameterGroup::getDescribe()
{
    return QString("");  
}

void FCParameterGroup::setVisible(bool v)
{
}

bool FCParameterGroup::isVisible()
{
    return false;  
}

void FCParameterGroup::copyStates(FCParameterGroup *g)
{
}

void FCParameterGroup::writeParameters(QDomDocument *doc, QDomElement *parent)
{
}

void FCParameterGroup::readParameters(QDomElement *ele)
{
}

void FCParameterGroup::dataToStream(QDataStream *datas)
{
}

} // namespace FC
