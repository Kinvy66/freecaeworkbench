/**
 * @file FCGeometryCreateBox.cpp
 * @brief 创建立方体
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateBox.h"
#include <QDebug>
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS.hxx>
#include "FCGeometrySet.h"
#include "FCGeometryParaBox.h"
#include "FCUniqueIDGenerater.h"

namespace FC 
{
// FCGeometryCreateBox::FCGeometryCreateBox() {}

FCGeometryCreateBox::FCGeometryCreateBox(QObject *parent)
    : FCGeometryModelBase(parent)
{
    
}

void FCGeometryCreateBox::setName(QString name)
{
    mName = name;
}

void FCGeometryCreateBox::setLocation(double *loca)
{
    mLoaction[0] = loca[0];
    mLoaction[1] = loca[1];
    mLoaction[2] = loca[2];
}

void FCGeometryCreateBox::setGeoPara(double *para)
{
    mGeoPara[0] = para[0];
    mGeoPara[1] = para[1];
    mGeoPara[2] = para[2];
}

/**
 * @brief FCGeometryCreateBox::execute
 * @return 
 * @todo 编辑模式不要重新生成set，在原有的set上编辑参数
 */
bool FCGeometryCreateBox::execute()
{
    gp_Pnt pt(mLoaction[0], mLoaction[1], mLoaction[2]);
    TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(pt, mGeoPara[0], mGeoPara[1], mGeoPara[2]).Shape();
    TopoDS_Shape *shape = new TopoDS_Shape;
    IdType id = 0;
    *shape = aTopoBox;
    if (shape->IsNull())
    {
        delete shape;
        return false;
    }
    
    FCGeometrySet *set = new FCGeometrySet(STEP);
    
    set->setShape(shape);
    mResult = set;
    
    if (mIsEdit) {
        id = mEditSetID;
        mGeoData->replaceSet(id, set);
        emit removeDisplayGeometryActor(id);        
    } else {
        id  = FCUniqueIDGenerater::id_uint64();
        mGeoData->appendGeometrySet(id, set);
    }
    
    FCGeometryParaBox  *para = new FCGeometryParaBox;
    para->setName(mName);
    para->setLocation(mLoaction);
    para->setGeoPara(mGeoPara);
    mResult->setParameter(para);
    set->setName(mName);
    
    emit updateGeoTree(id, mName);    
    emit showSet(id, true);
        
    qDebug() << "Create Cube,name:" << mName
             << ", para:" <<  mGeoPara[0] << mGeoPara[1] << mGeoPara[2]
             << ", location:" << mLoaction[0] << mLoaction[1] << mLoaction[2];     

    return true;
}

void FCGeometryCreateBox::undo()
{
    
}

void FCGeometryCreateBox::redo()
{
    
}

void FCGeometryCreateBox::releaseResult()
{
    
}

void FCGeometryCreateBox::setVisible(bool r)
{
    // if (mResult == nullptr) return;
    // emit showSet(mResult, r);   
}

} // namespace FC

