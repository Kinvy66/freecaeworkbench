/**
 * @file FCPostProcessingKernal.cpp
 * @brief 单个后处理结果，包含数据和属性
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingKernal.h"
#include <vtkPoints.h>
#include <vtkCell.h>
#include <QDataStream>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomText>
#include <vtkIdList.h>
#include <vtkUnstructuredGrid.h>
#include <QDebug>

namespace FC 
{
int FCPostProcessingKernal::s_idOffset = 0;

FCPostProcessingKernal::FCPostProcessingKernal()
{
    s_idOffset++;
    setID(s_idOffset);
}

void FCPostProcessingKernal::setPostProcessingData(vtkDataSet* dataset)
{
    mPostData = dataset;
}

vtkDataSet* FCPostProcessingKernal::getPostProcessingData()
{
    return mPostData;
}

double* FCPostProcessingKernal::getPointAt(const int index)
{
    if (!mPostData) return nullptr;
    return mPostData->GetPoint(index);
}

vtkCell* FCPostProcessingKernal::getCellAt(const int index)
{
    if (!mPostData) return nullptr;
    return mPostData->GetCell(index);
}

bool FCPostProcessingKernal::isVisible()
{
    return mVisible;
}

void FCPostProcessingKernal::setVisible(bool v)
{
    mVisible = v;
}

int FCPostProcessingKernal::getPointCount()
{
    if (!mPostData) return 0;
    return mPostData->GetNumberOfPoints();
}

int FCPostProcessingKernal::getCellCount()
{
    if (!mPostData) return 0;
    return mPostData->GetNumberOfCells();
}

void FCPostProcessingKernal::dataToStream(QDataStream* s)
{
    if (!mPostData) {
        *s << mId << mName << 0 << 0;
        return;
    }
    *s << mId << mName << mPostData->GetNumberOfPoints() << mPostData->GetNumberOfCells();
}

void FCPostProcessingKernal::setID(IdType id)
{
    FCDataBase::setID(id);
    if (id > s_idOffset)
        s_idOffset = id;
}

void FCPostProcessingKernal::resetMaxID()
{
    s_idOffset = 0;
}

int FCPostProcessingKernal::getMaxID()
{
    return s_idOffset;
}

void FCPostProcessingKernal::resetOffset()
{
    s_idOffset = 0;
}

QDomElement& FCPostProcessingKernal::writeToProjectFile(QDomDocument* doc, QDomElement* ele)
{
    QDomElement postEle = doc->createElement("PostProcessingKernal");
    postEle.setAttribute("ID", QString::number(mId));
    postEle.setAttribute("Name", mName);
    postEle.setAttribute("Visible", mVisible ? "1" : "0");
    postEle.setAttribute("ScalarFieldName", mScalarFieldName);
    postEle.setAttribute("BindedMeshID", QString::number(mBindedMeshID));
    
    if (mColorMap.first) {
        QDomElement colorMapEle = doc->createElement("ColorMap");
        colorMapEle.setAttribute("Enable", "1");
        colorMapEle.setAttribute("MinR", mColorMap.second.first.red());
        colorMapEle.setAttribute("MinG", mColorMap.second.first.green());
        colorMapEle.setAttribute("MinB", mColorMap.second.first.blue());
        colorMapEle.setAttribute("MaxR", mColorMap.second.second.red());
        colorMapEle.setAttribute("MaxG", mColorMap.second.second.green());
        colorMapEle.setAttribute("MaxB", mColorMap.second.second.blue());
        postEle.appendChild(colorMapEle);
    }
    
    ele->appendChild(postEle);
    return postEle;
}

void FCPostProcessingKernal::readDataFromProjectFile(QDomElement* e)
{
    if (e->tagName() != "PostProcessingKernal") return;
    
    mId = e->attribute("ID").toULongLong();
    mName = e->attribute("Name");
    mVisible = (e->attribute("Visible") == "1");
    mScalarFieldName = e->attribute("ScalarFieldName");
    mBindedMeshID = e->attribute("BindedMeshID").toULongLong();
    
    QDomNodeList colorMapList = e->elementsByTagName("ColorMap");
    if (colorMapList.size() > 0) {
        QDomElement colorMapEle = colorMapList.at(0).toElement();
        mColorMap.first = (colorMapEle.attribute("Enable") == "1");
        if (mColorMap.first) {
            int r = colorMapEle.attribute("MinR").toInt();
            int g = colorMapEle.attribute("MinG").toInt();
            int b = colorMapEle.attribute("MinB").toInt();
            mColorMap.second.first = QColor(r, g, b);
            
            r = colorMapEle.attribute("MaxR").toInt();
            g = colorMapEle.attribute("MaxG").toInt();
            b = colorMapEle.attribute("MaxB").toInt();
            mColorMap.second.second = QColor(r, g, b);
        }
    }
}

void FCPostProcessingKernal::writeBinaryFile(QDataStream* dataStream)
{
    *dataStream << mId << mName << mVisible;
    *dataStream << mScalarFieldName;
    *dataStream << mBindedMeshID;
    *dataStream << mColorMap.first;
    if (mColorMap.first) {
        *dataStream << mColorMap.second.first.rgb() << mColorMap.second.second.rgb();
    }
}

void FCPostProcessingKernal::readBinaryFile(QDataStream* dataStream)
{
    *dataStream >> mId >> mName >> mVisible;
    *dataStream >> mScalarFieldName;
    *dataStream >> mBindedMeshID;
    *dataStream >> mColorMap.first;
    if (mColorMap.first) {
        QRgb minRgb, maxRgb;
        *dataStream >> minRgb >> maxRgb;
        mColorMap.second.first = QColor(minRgb);
        mColorMap.second.second = QColor(maxRgb);
    }
}

void FCPostProcessingKernal::setScalarFieldName(const QString& name)
{
    mScalarFieldName = name;
}

QString FCPostProcessingKernal::getScalarFieldName() const
{
    return mScalarFieldName;
}

void FCPostProcessingKernal::setColorMap(bool enable, const QColor& minColor, const QColor& maxColor)
{
    mColorMap.first = enable;
    if (enable) {
        mColorMap.second.first = minColor;
        mColorMap.second.second = maxColor;
    }
}

QPair<bool, QPair<QColor, QColor>> FCPostProcessingKernal::getColorMap() const
{
    return mColorMap;
}

void FCPostProcessingKernal::bindMesh(IdType meshID)
{
    mBindedMeshID = meshID;
}

FCPostProcessingKernal::IdType FCPostProcessingKernal::getBindedMesh() const
{
    return mBindedMeshID;
}

} // namespace FC

