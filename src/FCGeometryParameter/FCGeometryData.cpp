/**
 * @file FCGeometryData.cpp
 * @brief 几何数据管理基类
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */

#include "FCGeometryData.h"
#include <gp_Ax3.hxx>
#include <assert.h>
#include <QCryptographicHash>
#include <gp_Ax3.hxx>
#include <QDomDocument>
#include <QDomElement>
#include <QDataStream>

#include "FCGeometrySet.h"

namespace FC 
{

FCGeometryData *FCGeometryData::mInstance = nullptr;

FCGeometryData *FCGeometryData::getInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new FCGeometryData;
    }
    return mInstance;
}

FCGeometryData::~FCGeometryData()
{
    
}

void FCGeometryData::appendGeometrySet(FCGeometrySet *set)
{
    mGeometryList.append(set);
}

void FCGeometryData::appendGeometryDatum(FCGeometryDatum *plane)
{
    mGeomtretryDatumList.append(plane);
    
}

QList<FCGeometryDatum *> FCGeometryData::getGeometryDatum()
{
    return mGeomtretryDatumList;
    
}

int FCGeometryData::getGeometrySetCount()
{
    return mGeometryList.size();
}

bool FCGeometryData::isEmpty()
{
    int n = mGeometryList.size();
    bool b = n < 1;
    return b;
}

FCGeometrySet *FCGeometryData::getGeometrySetAt(const int index)
{
    if (index >= 0 && index < mGeometryList.size())
        return mGeometryList.at(index);
    return nullptr;
}

int FCGeometryData::getIndexByGeoometrySet(FCGeometrySet *s)
{
    const int n = mGeometryList.size();
    for (int i = 0; i < n; ++i)
    {
        auto c = mGeometryList.at(i);
        if (c == s)
            return i;
    }
    return -1;
}

void FCGeometryData::removeGeometrySet(const int index)
{
    assert(index >= 0 && index < mGeometryList.size());
    FCGeometrySet *set = mGeometryList.at(index);
    delete set;
    mGeometryList.removeAt(index);
}

void FCGeometryData::replaceSet(FCGeometrySet *newset, FCGeometrySet *oldset)
{
    const int index = mGeometryList.indexOf(oldset);
    if (index >= 0)
    {
        mGeometryList.replace(index, newset);
    }
}

void FCGeometryData::removeTopGeometrySet(FCGeometrySet *set)
{
    mGeometryList.removeOne(set);
    
}

bool FCGeometryData::hasGeometrySet(FCGeometrySet *set)
{
    bool ishas{false};
    if (mGeometryList.contains(set))
        ishas = true;
    return ishas;
}

void FCGeometryData::removeGeometryDatum(FCGeometryDatum *plane)
{
    if (mGeomtretryDatumList.contains(plane))
        mGeomtretryDatumList.removeOne(plane);
}

void FCGeometryData::setVisable(int index, bool visable)
{
    if (index >= 0 && index < mGeometryList.size())
    {
        mGeometryList[index]->setVisible(visable);
    }
}

void FCGeometryData::clear()
{
    const int n = this->getGeometrySetCount();
    for (int i = 0; i < n; ++i)
    {
        FCGeometrySet *set = mGeometryList.at(i);
        delete set;
    }
    mGeometryList.clear();
    
    const int nd = mGeomtretryDatumList.size();
    for (int i = 0; i < nd; ++i)
    {
        auto set = mGeomtretryDatumList.at(i);
        delete set;
    }
    mGeomtretryDatumList.clear();
    
    if (mSketchPlan != nullptr)
    {
        delete mSketchPlan;
        mSketchPlan = nullptr;
    }
    
    // const int nc = _geoCpList.size();
    // for (int i = 0; i < nc; ++i)
    // {
    //     auto gc = _geoCpList.at(i);
    //     delete gc;
    //     gc = nullptr;
    // }
    // _geoCpList.clear();
    // GeometrySet::resetMaxID();
}

FCGeometrySet *FCGeometryData::getGeometrySetByID(const int id)
{
    const int n = this->getGeometrySetCount();
    for (int i = 0; i < n; ++i)
    {
        FCGeometrySet *set = mGeometryList.at(i);
        FCGeometrySet *res = nullptr;// set->getSetByID(id);
        if (res != nullptr)
            return res;
    }
    return nullptr;
}

FCGeometryDatum *FCGeometryData::getDatumByIndex(const int index)
{
    FCGeometryDatum *d = nullptr;
    if (index >= 0 && index < mGeomtretryDatumList.size())
        d = mGeomtretryDatumList.at(index);
    return d;
}

QString FCGeometryData::getMD5()
{
    const int n = mGeometryList.size();
    if (n < 1)
        return "";
    
    QDataStream stream;
    for (int i = 0; i < n; ++i)
    {
        FCGeometrySet *set = mGeometryList[i];
        stream << set->getID() << set->getName() << set->getShape() /*<<set->getStlDataSet()*/;
    }
    char *s;
    stream >> s;
    QString md5 = QCryptographicHash::hash(s, QCryptographicHash::Md5);
    return md5;
}

void FCGeometryData::setSketchPlane(double *loc, double *dir)
{
    if (mSketchPlan == nullptr)
        mSketchPlan = new gp_Ax3;
    mSketchPlan->SetAxis(gp_Ax1(gp_Pnt(loc[0], loc[1], loc[2]), gp_Dir(1.00001, 0.00001, 0))); //向量修改有崩溃风险  OCC bug
    mSketchPlan->SetDirection(gp_Dir(dir[0], dir[1], dir[2]));
}

gp_Ax3 *FCGeometryData::getSketchPlane()
{
    return mSketchPlan;
    
}



} // namespace FC
