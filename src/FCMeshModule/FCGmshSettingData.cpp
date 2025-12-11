/**
 * @file FCGmshSettingData.cpp
 * @brief 
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGmshSettingData.h"
#include "FCGmshThread.h"

namespace FC 
{

FCGmshSettingData::FCGmshSettingData()
{
    
}

FCGmshSettingData::~FCGmshSettingData()
{
    
}

void FCGmshSettingData::copy(FCDataBase* data)
{
    FCGmshSettingData* d = dynamic_cast<FCGmshSettingData*>(data);
    if (d == nullptr)return;
    
    FCDataBase::copy(data);
    
    this->setSolidHash(d->getSolidHash());
    this->setSurfaceHash(d->getSurfaceHash());
    this->setSelectAll(d->getSelectAll());
    this->setSelectVisiable(d->getSelectVisiable());
    this->setElementOrder(d->getElementOrder());
    this->setElementType(d->getElementType());
    this->setMethod(d->getMethod());
    this->setSizeFactor(d->getSizeFactor());
    this->setMinSize(d->getMinSize());
    this->setMaxSize(d->getMaxSize());
    this->setGeoClean(d->getGeoClean());
    this->setGridCoplanar(d->getGridCoplanar());
    this->setSmoothIteration(d->getSmoothIteration());
    // this->setLocalDesities(d->getLocalDesities());
}

void FCGmshSettingData::setSolidHash(QMultiHash<int, int> sh)
{
    mSolidHash = sh;
}

QMultiHash<int, int> FCGmshSettingData::getSolidHash()
{
    return mSolidHash;
}

void FCGmshSettingData::setSurfaceHash(QMultiHash<int, int> sh)
{
    mSurfaceHash = sh;
}

QMultiHash<int, int> FCGmshSettingData::getSurfaceHash()
{
    return mSurfaceHash;
}

void FCGmshSettingData::setElementType(QString type)
{
    mElementType = type;
}

QString FCGmshSettingData::getElementType()
{
    return mElementType;
}

void FCGmshSettingData::setElementOrder(int order)
{
    mElementOrder = order;
}

int FCGmshSettingData::getElementOrder()
{
    return mElementOrder;
}

void FCGmshSettingData::setMethod(int m)
{
    mMethod = m;
}

int FCGmshSettingData::getMethod()
{
    return mMethod;
}

void FCGmshSettingData::setSizeFactor(double sf)
{
    mSizeFactor = sf;
}

double FCGmshSettingData::getSizeFactor()
{
    return mSizeFactor;
}

void FCGmshSettingData::setMinSize(double min)
{
    mMinSize = min;
}

double FCGmshSettingData::getMinSize()
{
    return mMinSize;
}

void FCGmshSettingData::setMaxSize(double max)
{
    mMaxSize = max;
}

double FCGmshSettingData::getMaxSize()
{
    return mMaxSize;
}

void FCGmshSettingData::setGeoClean(bool c)
{
    mGeoclean = c;
}

bool FCGmshSettingData::getGeoClean()
{
    return mGeoclean;
}

void FCGmshSettingData::setSmoothIteration(int smooth)
{
    mSmoothIteration = smooth;
}

int FCGmshSettingData::getSmoothIteration()
{
    return mSmoothIteration;
}

void FCGmshSettingData::setGridCoplanar(bool gc)
{
    mGridCoplanar = gc;
}

bool FCGmshSettingData::getGridCoplanar()
{
    return mGridCoplanar;
}

void FCGmshSettingData::setSizeAtPoints(QString ps)
{
    QStringList points = ps.split(";");
    for (QString s : points)
    {
        QStringList coors = s.split(",");
        if (coors.size() != 4) continue;
        
        bool ok = false;
        double x = coors.at(0).toDouble(&ok);
        if (!ok)continue;
        double y = coors.at(1).toDouble(&ok);
        if (!ok)continue;
        double z = coors.at(2).toDouble(&ok);
        if (!ok)continue;
        double v = coors.at(3).toDouble(&ok);
        if (!ok)continue;
        
        // LocalPoint* lp = new LocalPoint;
        // lp->_type = LocalType::PointSize;
        // lp->_x = x; lp->_y = y; lp->_z = z; lp->_value = v;
        
        // _locals.append(lp);
    }
}


void FCGmshSettingData::setSizeFields(QString fs)
{
    QStringList solids{};
    QStringList fields = fs.split(";");
    for (QString s : fields)
    {
        QStringList field = s.split(",");
        
        if (field.size() <= 0) continue;
        
        bool ok = false;
        int t = field.at(0).toInt(&ok);
        if (!ok) continue;
        
        switch (t)
        {
        case 1:
            appendBoxField(field);
            break;
        case 2:
            appendBallField(field);
            break;
        case 3:
            appendCylinderField(field);
            break;
        case 4:
            solids.append(s);
            break;
        case 5:
            appendFrustumField(field);
            break;
        default:
            break;
        }
    }
    
    if (solids.size() > 0)
        appendSolidsField(solids);
}

// void FCGmshSettingData::setLocalDesities(QList<LocalDensity*> list)
// {
//     // _locals = list;
// }


// QList<LocalDensity*> FCGmshSettingData::getLocalDesities()
// {
//     // return _locals;
// }

void FCGmshSettingData::setSelectAll(bool b)
{
    mSelectall = b;
}

bool FCGmshSettingData::getSelectAll()
{
    return mSelectall;
}

void FCGmshSettingData::setSelectVisiable(bool b)
{
    mSelectvisible = b;
}

bool FCGmshSettingData::getSelectVisiable()
{
    return mSelectvisible;
}

void FCGmshSettingData::setMeshID(int id)
{
    mMeshID = id;
}

int FCGmshSettingData::getMeshID()
{
    return mMeshID;
}

void FCGmshSettingData::setCells(QList<int> cells)
{
    mCells = cells;
}

QList<int> FCGmshSettingData::getCells()
{
    return mCells;
}

void FCGmshSettingData::setDimension(int dim)
{
    mDimension = dim;
}

int FCGmshSettingData::getDimension()
{
    return mDimension;
}

void FCGmshSettingData::appendBoxField(QStringList list)
{
    //QStringList list = s.split(",");
    const int n = list.size();
    // if (n != 11)return;
    
    // double val[9] = { 0 };
    // bool ok = false;
    // for (int i = 1; i < 10; i++)
    // {
    //     double v = list.at(i).toDouble(&ok);
    //     if (!ok) return;
    //     val[i - 1] = v;
    // }
    
    // Box* b = new Box;
    // b->_type = LocalType::BoxField;
    // b->_thickness = val[0];
    // b->_vIn = val[1];
    // b->_vOut = val[2];
    // b->_x = val[3];
    // b->_y = val[4];
    // b->_z = val[5];
    // b->_length = val[6];
    // b->_width = val[7];
    // b->_height = val[8];
    // if (list.at(10).toInt() == 1)
    //     b->_backgroundField = true;
    
    // _locals.append(b);
}

void FCGmshSettingData::appendBallField(QStringList list)
{
    // const int n = list.size();
    // if (n != 9)return;
    
    // double val[7] = { 0 };
    // bool ok = false;
    // for (int i = 1; i < 8; i++)
    // {
    //     double v = list.at(i).toDouble(&ok);
    //     if (!ok) return;
    //     val[i - 1] = v;
    // }
    
    // Ball* b = new Ball;
    // b->_type = LocalType::BallField;
    // b->_radius = val[0];
    // b->_thickness = val[1];
    // b->_vIn = val[2];
    // b->_vOut = val[3];
    // b->_x = val[4];
    // b->_y = val[5];
    // b->_z = val[6];
    
    // if (list.at(8).toInt() == 1)
    //     b->_backgroundField = true;
    
    // _locals.append(b);
    
}

void FCGmshSettingData::appendCylinderField(QStringList list)
{
    // const int n = list.size();
    // if (n != 12)return;
    
    // double val[10] = { 0 };
    // bool ok = false;
    // for (int i = 1; i < 11; i++)
    // {
    //     double v = list.at(i).toDouble(&ok);
    //     if (!ok) return;
    //     val[i - 1] = v;
    // }
    
    // Cylinder* c = new Cylinder;
    // c->_type = LocalType::CylinderField;
    // c->_radius = val[0];
    // c->_length = val[1];
    // c->_x = val[2];
    // c->_y = val[3];
    // c->_z = val[4];
    // c->_xAxis = val[5];
    // c->_yAxis = val[6];
    // c->_zAxis = val[7];
    // c->_vIn = val[8];
    // c->_vOut = val[9];
    
    // if (list.at(11).toInt() == 1)
    //     c->_backgroundField = true;
    
    // _locals.append(c);
}

void FCGmshSettingData::appendSolidsField(QStringList list)
{
    // QMultiHash<int, int> solidHash;
    // double val[3] = { 0 };
    // bool back{ false };
    // for (QString s : list)
    // {
    //     QStringList solid = s.split(",");
    //     const int n = solid.size();
    //     if (n != 7)continue;
        
    //     bool ok = false;
    //     val[0] = solid.at(1).toDouble(&ok);
    //     if (!ok)continue;
    //     val[1] = solid.at(2).toDouble(&ok);
    //     if (!ok)continue;
    //     val[2] = solid.at(3).toDouble(&ok);
    //     if (!ok)continue;
    //     int setid = solid.at(4).toDouble(&ok);
    //     if (!ok)continue;
    //     int sindex = solid.at(5).toDouble(&ok);
    //     if (!ok)continue;
        
    //     solidHash.insert(setid, sindex);
        
    //     if (solid.at(6).toInt() == 1)
    //         back = true;
    // }
    
    // SolidFields* solid = new SolidFields;
    // solid->_type = LocalType::SolidField;
    // solid->_vIn = val[0];
    // solid->_vOut = val[1];
    // solid->_thickness = val[2];
    // solid->_solidHash = solidHash;
    // solid->_backgroundField = back;
    
    // _locals.append(solid);
}

void FCGmshSettingData::appendFrustumField(QStringList list)
{
    
    // const int n = list.size();
    // if (n != 15)return;
    
    // double val[13] = { 0 };
    // bool ok = false;
    // for (int i = 1; i < 14; i++)
    // {
    //     double v = list.at(i).toDouble(&ok);
    //     if (!ok) return;
    //     val[i - 1] = v;
    // }
    
    // Frustum* f = new Frustum;
    // f->_type = LocalType::FrustumField;
    // f->_iRadius = val[0];
    // f->_oRadius = val[1];
    // f->_iTopRadius = val[2];
    // f->_oTopRadius = val[3];
    // f->_length = val[4];
    // f->_x = val[5];
    // f->_y = val[6];
    // f->_z = val[7];
    // f->_xAxis = val[8];
    // f->_yAxis = val[9];
    // f->_zAxis = val[10];
    // f->_vIn = val[11];
    // f->_vOut = val[12];
    
    // if (list.at(14).toInt() == 1)
    //     f->_backgroundField = true;
    
    // _locals.append(f);
}

} // namespace FC
