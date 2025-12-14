/**
 * @file FCPostProcessingViewObject.cpp
 * @brief 后处理的显示层对象
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingViewObject.h"
#include "FCPostProcessingData.h"
#include "FCPostProcessingKernal.h"
//vtk
#include <vtkUnstructuredGrid.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkScalarsToColors.h>
#include <vtkMapper.h>
#include <QDebug>

namespace FC 
{
FCPostProcessingViewObject::FCPostProcessingViewObject(IdType kid)
    : mPostProcessingID(kid), mDisplayData(nullptr),
      mPostProcessingData(FCPostProcessingData::getInstance())
{
    mActor = vtkActor::New();
    mLookupTable = vtkLookupTable::New();
    // 立即设置Actor属性，确保边界线默认隐藏
    if (mActor) {
        vtkProperty* prop = mActor->GetProperty();
        if (prop) {
            prop->SetEdgeVisibility(false); // 默认不显示边界线
            prop->SetInterpolationToGouraud(); // 使用平滑着色
        }
    }
    this->init();
}

FCPostProcessingViewObject::~FCPostProcessingViewObject()
{
    if (mDisplayData != nullptr)
        mDisplayData->Delete();
    if (mActor != nullptr)
        mActor->Delete();
    if (mLookupTable != nullptr)
        mLookupTable->Delete();
}

vtkDataSet* FCPostProcessingViewObject::getDisplayData()
{
    return mDisplayData;
}

vtkActor* FCPostProcessingViewObject::getActor()
{
    return mActor;
}

vtkLookupTable* FCPostProcessingViewObject::getLookupTable()
{
    return mLookupTable;
}

void FCPostProcessingViewObject::highLight()
{
    if (mActor) {
        mActor->GetProperty()->SetColor(1.0, 1.0, 0.0); // 黄色高亮
        mIsKernalHighLight = true;
    }
}

void FCPostProcessingViewObject::clearHighLight()
{
    if (mActor) {
        // 恢复原始颜色
        mIsKernalHighLight = false;
        updateDisplayData();
    }
}

bool FCPostProcessingViewObject::isKernalHighLight()
{
    return mIsKernalHighLight;
}

void FCPostProcessingViewObject::updateDisplayData()
{
    FCPostProcessingKernal* kernal = mPostProcessingData->getPostProcessingKernalByID(mPostProcessingID);
    if (!kernal) {
        qWarning() << "updateDisplayData: kernal not found for postID" << mPostProcessingID;
        return;
    }
    
    vtkDataSet* postData = kernal->getPostProcessingData();
    if (!postData) {
        qWarning() << "updateDisplayData: postData is null for postID" << mPostProcessingID;
        return;
    }
    
    qDebug() << "updateDisplayData: postID" << mPostProcessingID 
             << "points:" << postData->GetNumberOfPoints() 
             << "cells:" << postData->GetNumberOfCells();
    
    // 如果显示数据已存在，先删除
    if (mDisplayData) {
        mDisplayData->Delete();
        mDisplayData = nullptr;
    }
    
    // 深拷贝数据
    mDisplayData = postData->NewInstance();
    mDisplayData->DeepCopy(postData);
    
    // 创建mapper
    vtkDataSetMapper* mapper = vtkDataSetMapper::New();
    mapper->SetInputData(mDisplayData);
    
    // 设置标量场
    vtkDataArray* scalars = mDisplayData->GetPointData()->GetScalars();
    bool usePointData = true;
    if (!scalars) {
        scalars = mDisplayData->GetCellData()->GetScalars();
        usePointData = false;
    }
    
    if (scalars) {
        if (usePointData) {
            mapper->SetScalarModeToUsePointData();
        } else {
            mapper->SetScalarModeToUseCellData();
        }
        
        if (scalars->GetNumberOfComponents() == 1) {
            double range[2];
            scalars->GetRange(range);
            mapper->SetScalarRange(range);
            qDebug() << "updateDisplayData: scalar range" << range[0] << "to" << range[1];
        }
        
        // 创建或更新颜色查找表
        createLookupTable();
        if (mLookupTable) {
            mapper->SetLookupTable(static_cast<vtkScalarsToColors*>(mLookupTable));
        }
    } else {
        // 如果没有标量场，使用默认颜色
        mapper->ScalarVisibilityOff();
        qWarning() << "updateDisplayData: no scalars found";
    }
    
    if (mActor) {
        // 如果已有mapper，先删除
        vtkMapper* oldMapper = mActor->GetMapper();
        if (oldMapper) {
            oldMapper->Delete();
        }
        mActor->SetMapper(mapper);
        mActor->VisibilityOn();
        
        // 设置Actor属性
        vtkProperty* prop = mActor->GetProperty();
        if (prop) {
            prop->SetRepresentationToSurface();
            // 不显示网格线
            prop->SetEdgeVisibility(false);
            // 使用Gouraud着色，避免转动时出现色块闪动
            prop->SetInterpolationToGouraud();
            // 如果没有标量场，设置默认颜色
            if (!scalars) {
                prop->SetColor(0.8, 0.8, 0.8); // 浅灰色
            }
        }
        
        qDebug() << "updateDisplayData: actor mapper set, visibility on, representation: surface";
    } else {
        qWarning() << "updateDisplayData: actor is null";
        mapper->Delete();
    }
}

void FCPostProcessingViewObject::init()
{
    // 先创建颜色查找表
    createLookupTable();
    // 如果数据已存在，更新显示数据
    FCPostProcessingKernal* kernal = mPostProcessingData->getPostProcessingKernalByID(mPostProcessingID);
    if (kernal && kernal->getPostProcessingData()) {
        updateDisplayData();
    }
}

void FCPostProcessingViewObject::createLookupTable()
{
    FCPostProcessingKernal* kernal = mPostProcessingData->getPostProcessingKernalByID(mPostProcessingID);
    if (!kernal) return;
    
    auto colorMap = kernal->getColorMap();
    
    if (colorMap.first) {
        // 使用自定义颜色映射
        mLookupTable->SetNumberOfTableValues(256);
        QColor minColor = colorMap.second.first;
        QColor maxColor = colorMap.second.second;
        
        for (int i = 0; i < 256; ++i) {
            double t = i / 255.0;
            int r = minColor.red() + (maxColor.red() - minColor.red()) * t;
            int g = minColor.green() + (maxColor.green() - minColor.green()) * t;
            int b = minColor.blue() + (maxColor.blue() - minColor.blue()) * t;
            mLookupTable->SetTableValue(i, r / 255.0, g / 255.0, b / 255.0, 1.0);
        }
    } else {
        // 使用默认颜色映射（彩虹色）
        mLookupTable->SetNumberOfTableValues(256);
        mLookupTable->SetHueRange(0.667, 0.0); // 蓝到红
        mLookupTable->SetSaturationRange(1.0, 1.0);
        mLookupTable->SetValueRange(1.0, 1.0);
        mLookupTable->Build();
    }
    
    if (mDisplayData) {
        vtkDataArray* scalars = mDisplayData->GetPointData()->GetScalars();
        if (!scalars) {
            scalars = mDisplayData->GetCellData()->GetScalars();
        }
        if (scalars && scalars->GetNumberOfComponents() == 1) {
            double range[2];
            scalars->GetRange(range);
            mLookupTable->SetTableRange(range);
        }
    }
}

void FCPostProcessingViewObject::setDisplayForm(int form)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (!prop) return;
    
    switch (form) {
    case 0: // 面
        prop->SetRepresentationToSurface();
        prop->SetEdgeVisibility(false);
        // 使用Gouraud着色，避免转动时出现色块闪动
        prop->SetInterpolationToGouraud();
        break;
    case 1: // 线框
        prop->SetRepresentationToWireframe();
        break;
    case 2: // 点
        prop->SetRepresentationToPoints();
        break;
    default:
        break;
    }
}

void FCPostProcessingViewObject::setTransparency(double opacity)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        prop->SetOpacity(opacity);
    }
}

void FCPostProcessingViewObject::setPointSize(int size)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        prop->SetPointSize(size);
    }
}

void FCPostProcessingViewObject::setLineWidth(int width)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        prop->SetLineWidth(width);
    }
}

void FCPostProcessingViewObject::setShadingMethod(int method)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (!prop) return;
    
    switch (method) {
    case 0: // 平面着色
        prop->SetInterpolationToFlat();
        break;
    case 1: // Gouraud着色
        prop->SetInterpolationToGouraud();
        break;
    case 2: // Phong着色
        prop->SetInterpolationToPhong();
        break;
    default:
        break;
    }
}

void FCPostProcessingViewObject::setLightingProperties(double specularCoeff, double specularIntensity, 
                                                        double ambientCoeff, double diffuseCoeff)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        prop->SetSpecular(specularCoeff);
        prop->SetSpecularPower(specularIntensity);
        prop->SetAmbient(ambientCoeff);
        prop->SetDiffuse(diffuseCoeff);
    }
}

void FCPostProcessingViewObject::setBoundaryColor(double r, double g, double b)
{
    if (!mActor) return;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        prop->SetEdgeColor(r, g, b);
        // 不自动启用边界线显示，边界线显示由其他方法控制（如setDisplayForm）
        // 默认情况下后处理不显示网格线
        // prop->SetEdgeVisibility(true);
    }
}

int FCPostProcessingViewObject::getDisplayForm() const
{
    if (!mActor) return 0;
    
    vtkProperty* prop = mActor->GetProperty();
    if (!prop) return 0;
    
    int rep = prop->GetRepresentation();
    if (rep == VTK_SURFACE) {
        return 0; // 面
    } else if (rep == VTK_WIREFRAME) {
        return 1; // 线框
    } else if (rep == VTK_POINTS) {
        return 2; // 点
    }
    return 0;
}

double FCPostProcessingViewObject::getTransparency() const
{
    if (!mActor) return 1.0;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        return prop->GetOpacity();
    }
    return 1.0;
}

int FCPostProcessingViewObject::getPointSize() const
{
    if (!mActor) return 2;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        return static_cast<int>(prop->GetPointSize());
    }
    return 2;
}

int FCPostProcessingViewObject::getLineWidth() const
{
    if (!mActor) return 1;
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        return static_cast<int>(prop->GetLineWidth());
    }
    return 1;
}

int FCPostProcessingViewObject::getShadingMethod() const
{
    if (!mActor) return 0;
    
    vtkProperty* prop = mActor->GetProperty();
    if (!prop) return 0;
    
    int interp = prop->GetInterpolation();
    if (interp == VTK_FLAT) {
        return 0; // 平面着色
    } else if (interp == VTK_GOURAUD) {
        return 1; // Gouraud着色
    } else if (interp == VTK_PHONG) {
        return 2; // Phong着色
    }
    return 0;
}

void FCPostProcessingViewObject::getLightingProperties(double& specularCoeff, double& specularIntensity, 
                                                        double& ambientCoeff, double& diffuseCoeff) const
{
    if (!mActor) {
        specularCoeff = 0.0;
        specularIntensity = 100.0;
        ambientCoeff = 0.0;
        diffuseCoeff = 1.0;
        return;
    }
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        specularCoeff = prop->GetSpecular();
        specularIntensity = prop->GetSpecularPower();
        ambientCoeff = prop->GetAmbient();
        diffuseCoeff = prop->GetDiffuse();
    } else {
        specularCoeff = 0.0;
        specularIntensity = 100.0;
        ambientCoeff = 0.0;
        diffuseCoeff = 1.0;
    }
}

void FCPostProcessingViewObject::getBoundaryColor(double& r, double& g, double& b) const
{
    if (!mActor) {
        r = 0.0; g = 0.0; b = 1.0; // 默认蓝色
        return;
    }
    
    vtkProperty* prop = mActor->GetProperty();
    if (prop) {
        double color[3];
        prop->GetEdgeColor(color);
        r = color[0];
        g = color[1];
        b = color[2];
    } else {
        r = 0.0; g = 0.0; b = 1.0;
    }
}

} // namespace FC

