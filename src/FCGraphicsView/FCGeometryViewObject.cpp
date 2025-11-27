/**
 * @file FCFCGeometryViewObject.cpp
 * @brief 单个可视化对象
 * @date 2025-11-26
 * @version V0.0.1
 * @details 几何的的最小单元(面/边/点/实体)管理类
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryViewObject.h"
#include "FCGeometrySet.h"
#include "FCGeometrySetViewData.h"
#include "FCGeometryViewObject.h"
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>


namespace FC 
{
	FCGeometryViewObject::FCGeometryViewObject(ViewObjType type,
                                           int beg, int end,
                                           Handle(TopoDS_TShape) ts)
		: mType(type), mBegin(beg), mEnd(end), mTshape(ts) {}
    
    /**
     * @brief 获取范围
     * @param beg
     * @param end
     */
    void FCGeometryViewObject::getRange(int &beg, int &end)
    {
        beg = mBegin;
        end = mEnd;
    }
    
    /**
     * @brief 添加实体面
     * @param f
     */
    void FCGeometryViewObject::appendSolidFace(int f)
    {
        mSolidFaces.append(f);
    }
    
    /**
     * @brief 获取实体面
     * @return 
     */
    QList<int> FCGeometryViewObject::getSolidFace()
    {
        return mSolidFaces;
    }
    
    /**
     * @brief 设置索引
     * @param index
     */
    void FCGeometryViewObject::setIndex(int index)
    {
        mIndex = index;
    }
    
    /**
     * @brief 获取索引
     * @return 
     */
    int FCGeometryViewObject::getIndex()
    {
        return mIndex;
    }
    
    /**
     * @brief 获取原始几何集合
     * @return 
     */
    FCGeometrySet *FCGeometryViewObject::getGeometySet()
    {
        if (mSetViewObj == nullptr)
            return nullptr;
        return mSetViewObj->getGeometrySet();
    }
    
    /**
     * @brief 获取几何集合可视化对象
     * @return 
     */
    FCGeometrySetViewData *FCGeometryViewObject::getGeoSetViewObject()
    {
        return mSetViewObj;
    }
    
    /**
     * @brief 获取(高亮)显示状态
     * @return 
     */
    FCGeometryViewObject::ViewStates FCGeometryViewObject::getStates()
    {
        return mStates;
    }
    
    /**
     * @brief 设置(高亮)显示状态
     * @param s
     */
    void FCGeometryViewObject::setStates(ViewStates s)
    {
        mStates = s;
    }
    
    /**
     * @brief 将vtkPolyData和几何集合可视化对对象关联
     * @param poly
     * @param setViewObj
     */
    void FCGeometryViewObject::setConnectionData(vtkPolyData *poly, FCGeometrySetViewData *setViewObj)
    {
        mPolys = poly;
        mSetViewObj = setViewObj;
    }
    
    /**
     * @brief 重置为默认颜色
     */
    void FCGeometryViewObject::resetColor()
    {
        QColor color;
        switch (mType)
        {
        case FCGeometryViewObject::Point:
            color = QColor(128,0,128,255); // Setting::BusAPI::instance()->getGraphOption()->getGeometryPointColor();
            break;
        case FCGeometryViewObject::Edge:
            color = QColor(0,128,128,255); // Setting::BusAPI::instance()->getGraphOption()->getGeometryCurveColor();
            break;
        case FCGeometryViewObject::Face:
        case FCGeometryViewObject::Solid:
            color =  QColor(255,255,255,255);//Setting::BusAPI::instance()->getGraphOption()->getGeometrySurfaceColor();
            break;
        default:
            break;
        }
        this->setObjectColor(color);
        mStates = Normal;
    }
    
    /**
     * @brief 鼠标悬停高亮
     */
    void FCGeometryViewObject::preHighLight()
    {
        // QColor c = Setting::BusAPI::instance()->getGraphOption()->getPreHighLightColor();
        // this->setObjectColor(c);
        mStates = PreHigh;
    }
    
    /**
     * @brief 选中高亮
     */
    void FCGeometryViewObject::highLight()
    {
        // QColor c = Setting::BusAPI::instance()->getGraphOption()->getHighLightColor();
        // this->setObjectColor(c);
        mStates = HighLigh;
    }
    
    /**
     * @brief 设置对象颜色
     * @param color
     */
    void FCGeometryViewObject::setObjectColor(QColor color)
    {
        vtkDataArray *dataArray = nullptr;
        if (mType == Solid)
        {
            setSolidColor(color);
            return;
        }
        if (mPolys == nullptr)
            return;
        if (mType == Point)
            dataArray = mPolys->GetPointData()->GetScalars();
        else
            dataArray = mPolys->GetCellData()->GetScalars();
        for (int i = mBegin; i <= mEnd; ++i)
        {
            dataArray->SetComponent(i, 0, color.red());
            dataArray->SetComponent(i, 1, color.green());
            dataArray->SetComponent(i, 2, color.blue());
        }
        dataArray->Modified();
    }
    
    /**
     * @brief 设置实体颜色
     * @param color
     */
    void FCGeometryViewObject::setSolidColor(QColor color)
    {
        for (int index : mSolidFaces)
        {
            auto vobj = mSetViewObj->getFaceViewObjByIndex(index);
            if (vobj != nullptr)
                vobj->setObjectColor(color);
        }
    }
    
    
} // namespace FC
