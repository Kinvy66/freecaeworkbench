/**
 * @file FCParameterBase.cpp
 * @brief 参数基类
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCParameterBase.h"
#include <QDomElement>
#include <QDomDocument>
#include <QDomAttr>
#include <QDebug>

namespace FC 
{

FCParameterBase::FCParameterBase(ParaType t)
    :mType(t)
{
    
}


void FCParameterBase::setDescribe(QString s)
{
    mDescribe = s;
}
QString FCParameterBase::getDescribe()
{
    return mDescribe;
}
void FCParameterBase::setParaType(ParaType t)
{
    mType = t;
}
ParaType FCParameterBase::getParaType()
{
    return mType;
}
void FCParameterBase::writeParameter(QDomDocument* doc, QDomElement* parent)
{
    //		QDomElement paraEle = doc->createElement("Parameter");
    
    QDomAttr tyattr = doc->createAttribute("Type");
    QString stype = ParaTypeToString(mType);
    tyattr.setValue(stype);
    parent->setAttributeNode(tyattr);
    
    QDomAttr desAttr = doc->createAttribute("Describe");
    desAttr.setValue(mDescribe);
    parent->setAttributeNode(desAttr);
    
    QDomAttr chineAttr = doc->createAttribute("Chinese");
    chineAttr.setValue(mChinese);
    parent->setAttributeNode(chineAttr);
    
    QDomAttr editattr = doc->createAttribute("Editable");
    QString attrs = "false";
    if (mEditable) attrs = "true";
    editattr.setValue(attrs);
    parent->setAttributeNode(editattr);
    
    QDomAttr visattr = doc->createAttribute("Visible");
    QString vis = "false";
    if (mVisible) vis = "true";
    visattr.setValue(vis);
    parent->setAttributeNode(visattr);
    
}
void FCParameterBase:: readParameter(QDomElement* e)
{
    QString des = e->attribute("Describe");
    this->setDescribe(des);
    QString chinese = e->attribute("Chinese");
    this->setChinese(chinese);
    QString edit = e->attribute("Editable");
    if (edit.toLower() == "false")
        mEditable = false;
    QString visible = e->attribute("Visible");
    if (visible.toLower() == "false")
        mVisible = false;
}
bool FCParameterBase::isEditable()
{
    return mEditable;
}

QString FCParameterBase::ParaTypeToString(ParaType t)
{
    QString stype = "";
    
    switch (t)
    {
    case Para_Int: stype = "Int"; break;
    case Para_Double: stype = "Double"; break;
    case Para_Color: stype = "Color"; break;
    case Para_String: stype = "String"; break;
    case Para_Bool: stype = "Bool"; break;
    case Para_Selectable: stype = "Selectable"; break;
    case Para_Path: stype = "Path"; break;
    case Para_Table: stype = "Table"; break;
    default: break;
    }
    
    return stype;
}
ParaType FCParameterBase::StringToParaType(QString stype)
{
    ParaType t = Para_Blank;
    
    if (stype == "Int") t = Para_Int;
    else if (stype == "Double") t = Para_Double;
    else if (stype == "Color") t = Para_Color;
    else if (stype == "String") t = Para_String;
    else if (stype == "Bool") t = Para_Bool;
    else if (stype == "Selectable") t = Para_Selectable;
    else if (stype == "Path") t = Para_Path;
    else if (stype == "Table") t = Para_Table;
    
    return t;
}

void FCParameterBase::copy(FCParameterBase* ori, bool valueOnly)
{
    if (valueOnly) return;
    mType = ori->getParaType();
    mDescribe = ori->getDescribe();
    mEditable = ori->isEditable();
    mVisible = ori->isVisible();
    mChinese = ori->getChinese();
}
void FCParameterBase::setVisible(bool v)
{
    mVisible = v;
}
bool FCParameterBase::isVisible()
{
    return mVisible;
}

void FCParameterBase::setEditable(bool e)
{
    mEditable = e;
}

bool FCParameterBase::isSameValueWith(FCParameterBase* p)
{
    Q_UNUSED(p)
    return false;
}

void FCParameterBase::copyStatus(FCParameterBase* p)
{
    //		qDebug() << _describe << "   " << p->getDescribe();
    mEditable = p->isEditable();
    mVisible = p->isVisible();
    //		qDebug() << _visible;
}

void FCParameterBase::appendObserver(FCParameterObserver* obs)
{
    if (!mObserverList.contains(obs))
        mObserverList.append(obs);
}

QList<FCParameterObserver*> FCParameterBase::getObserverList()
{
    return mObserverList;
}

QString FCParameterBase::valueToString()
{
    qDebug() << "paraBase, not override";
    return QString();
}

void FCParameterBase::setChinese(QString chinese)
{
    mChinese = chinese;
}

QString FCParameterBase::getChinese()
{
    return mChinese;
}


int FCParameterBase::getDataID()
{
    return _dataID;
}

void FCParameterBase::setDataID(int id)
{
    _dataID = id;
}

int FCParameterBase::getDataIndex()
{
    return _dataIndex;
}

void FCParameterBase::setDataIndex(int index)
{
    _dataIndex = index;
}

QString FCParameterBase::getGroupName()
{
    return _groupName;
}

void FCParameterBase::setGroupName(QString group)
{
    _groupName = group;
}

QString FCParameterBase::genAbsoluteName()
{
    QString name;
    if (_groupName.isEmpty())
    {
        name = mDescribe;
    }
    else
    {
        name = QString("%1/%2").arg(_groupName).arg(mDescribe);
    }
    return name;
}

void FCParameterBase::setValueFromString(QString v)
{
    
}


} // namespace FC
