/**
 * @file FCGeometryParaBox.cpp
 * @brief 立方体参数
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryParaBox.h"

namespace FC 
{

FCGeometryParaBox::FCGeometryParaBox()
{
    mType = GeometryParaCreateBox;
}

void FCGeometryParaBox::setName(QString name)
{
    mName = name;
}

QString FCGeometryParaBox::getName()
{
    return mName;
}

void FCGeometryParaBox::setLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        mLocation[i] = loc[i];
}

void FCGeometryParaBox::getLocation(double *loc)
{
    for (int i = 0; i < 3; ++i)
        loc[i] = mLocation[i];
}

void FCGeometryParaBox::setGeoPara(double *para)
{
    for (int i = 0; i < 3; ++i)
        mGeoPara[i] = para[i];
}

void FCGeometryParaBox::getGeoPara(double *para)
{
    for (int i = 0; i < 3; ++i)
        para[i] = mGeoPara[i];
}

/**
 * @brief 写入数据到工程文件中
 * @param doc
 * @param parent
 * @return 
 * @note 写入的是临时目录下的工程文件
 */
QDomElement &FCGeometryParaBox::writeToProjectFile(QDomDocument *doc, QDomElement *parent)
{
    QDomElement element = doc->createElement("Parameter"); //创建子节点
    QDomAttr typeattr = doc->createAttribute("Type");
    typeattr.setValue(this->typeToString());
    element.setAttributeNode(typeattr);
    
    QDomAttr nameattr = doc->createAttribute("Name");
    nameattr.setValue(mName);
    element.setAttributeNode(nameattr);
    
    QDomElement locationEle = doc->createElement("Location");
    QString locstr = QString("%1,%2,%3").arg(mLocation[0]).arg(mLocation[1]).arg(mLocation[2]);
    QDomText locText = doc->createTextNode(locstr);
    locationEle.appendChild(locText);
    element.appendChild(locationEle);
    
    QDomElement geoParaEle = doc->createElement("GeoPara");
    QString geoParaStr = QString("%1,%2,%3").arg(mGeoPara[0]).arg(mGeoPara[1]).arg(mGeoPara[2]);
    QDomText paraText = doc->createTextNode(geoParaStr);
    geoParaEle.appendChild(paraText);
    element.appendChild(geoParaEle);
    
    parent->appendChild(element);
    return element;
}

void FCGeometryParaBox::readDataFromProjectFile(QDomElement *e)
{
    mName = e->attribute("Name");
    QDomNodeList locList = e->elementsByTagName("Location");
    if (locList.size() != 1)
        return;
    QDomElement locele = locList.at(0).toElement();
    QString locstr = locele.text();
    QStringList locsl = locstr.split(",");
    if (locsl.size() != 3)
        return;
    for (int i = 0; i < 3; ++i)
    {
        mLocation[i] = locsl.at(i).toDouble();
    }
    
    QDomNodeList paraList = e->elementsByTagName("GeoPara");
    if (paraList.size() != 1)
        return;
    QDomElement paraele = paraList.at(0).toElement();
    QString parastr = paraele.text();
    QStringList parasl = parastr.split(",");
    if (parasl.size() != 3)
        return;
    for (int i = 0; i < 3; ++i)
    {
        mGeoPara[i] = parasl.at(i).toDouble();
    }
}

} // namespace FC
