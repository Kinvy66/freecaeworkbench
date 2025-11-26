/**
 * @file FCFCGeometryViewObject.cpp
 * @brief 
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryViewObject.h"
#include "FCGeometrySet.h"
#include "FCGeometrySetViewObject.h"
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
    
    void FCGeometryViewObject::getRange(int &beg, int &end)
    {
        beg = mBegin;
        end = mEnd;
    }
    
    void FCGeometryViewObject::appendSolidFace(int f)
    {
        mSolidFaces.append(f);
    }
    
    QList<int> FCGeometryViewObject::getSolidFace()
    {
        return mSolidFaces;
    }
    
    void FCGeometryViewObject::setIndex(int index)
    {
        mIndex = index;
    }
    
    int FCGeometryViewObject::getIndex()
    {
        return mIndex;
    }
    
    FCGeometrySet *FCGeometryViewObject::getGeometySet()
    {
        // if (_setViewObj == nullptr)
        //     return nullptr;
        // return _setViewObj->getGeometrySet();
        return nullptr;
    }
    
    FCGeometrySetViewObject *FCGeometryViewObject::getGeoSetViewObject()
    {
        return mSetViewObj;
    }
    
    FCGeometryViewObject::ViewStates FCGeometryViewObject::getStates()
    {
        return mStates;
    }
    
    void FCGeometryViewObject::setStates(ViewStates s)
    {
        mStates = s;
        ;
    }
    
    void FCGeometryViewObject::setConnectionData(vtkPolyData *poly, FCGeometrySetViewObject *setViewObj)
    {
        mPolys = poly;
        mSetViewObj = setViewObj;
    }
    
    void FCGeometryViewObject::resetColor()
    {
        QColor color;
        // switch (_type)
        // {
        // case MainWidget::FCGeometryViewObject::Point:
        //     color = Setting::BusAPI::instance()->getGraphOption()->getGeometryPointColor();
        //     break;
        // case MainWidget::FCGeometryViewObject::Edge:
        //     color = Setting::BusAPI::instance()->getGraphOption()->getGeometryCurveColor();
        //     break;
        // case MainWidget::FCGeometryViewObject::Face:
        // case MainWidget::FCGeometryViewObject::Solid:
        //     color = Setting::BusAPI::instance()->getGraphOption()->getGeometrySurfaceColor();
        //     break;
        // default:
        //     break;
        // }
        this->setObjectColor(color);
        mStates = Normal;
    }
    
    void FCGeometryViewObject::preHighLight()
    {
        // QColor c = Setting::BusAPI::instance()->getGraphOption()->getPreHighLightColor();
        // this->setObjectColor(c);
        mStates = PreHigh;
    }
    
    void FCGeometryViewObject::highLight()
    {
        // QColor c = Setting::BusAPI::instance()->getGraphOption()->getHighLightColor();
        // this->setObjectColor(c);
        mStates = HighLigh;
    }
    
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
    
    void FCGeometryViewObject::setSolidColor(QColor color)
    {
        // for (int index : _solidFaces)
        // {
        //     auto vobj = _setViewObj->getFaceViewObjByIndex(index);
        //     if (vobj != nullptr)
        //         vobj->setObjectColor(color);
        // }
    }
    
    
} // namespace FC
