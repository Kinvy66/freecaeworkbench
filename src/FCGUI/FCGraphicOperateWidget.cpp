/**
 * @file FCGraphicOperateWidget.cpp
 * @brief 可视化交互窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGraphicOperateWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <array>
#include "FCGeometrySet.h"

// vtk
#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <array>
#include <vtkConeSource.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkInteractorStyleTrackballCamera.h>

// OCC
#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx>
#include <V3d_View.hxx>
#include <Aspect_Handle.hxx>
#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>

namespace FC 
{

FCGraphicOperateWidget::FCGraphicOperateWidget(QWidget *parent)
 : QWidget(parent)
{
    
    // QLabel* lab = new QLabel(this);
    // lab->setText("GraphicOperateWidget");
    
    mVTKWidget = new QVTKOpenGLNativeWidget(this);
    // 使用布局让 _pVTKWidget 填满整个 FCGraphicOperateWidget
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);  // 去掉边距
    layout->addWidget(mVTKWidget);
    
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    
    // vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    mRenderer->SetBackground(1.0, 1.0, 1.0);
    
    // vtkSmartPointer<Snar
    mVTKWidget->renderWindow()->AddRenderer(mRenderer);
    
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> interractor =
        vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    
    interractor->SetDefaultRenderer(mRenderer);
    mVTKWidget->interactor()->SetInteractorStyle(interractor);
    
}

FCGraphicOperateWidget::~FCGraphicOperateWidget()
{
    
}

void FCGraphicOperateWidget::showModel(FCGeometrySet *set, bool r)
{
    TopoDS_Shape* shape =  set->getShape();
    Handle(IVtkOCC_Shape) aShapeImpl = new IVtkOCC_Shape(*shape);
    vtkNew<IVtkTools_ShapeDataSource> DS;
    DS->SetShape(aShapeImpl);
    DS->Update();
    vtkNew<IVtkTools_DisplayModeFilter> filter;
    filter->SetInputData(DS->GetOutput());
    filter->SetDisplayMode(DM_Shading);
    filter->SetSmoothShading(true);
    filter->Update();
    vtkNew<vtkPolyDataMapper> mapper;                
    mapper->SetInputData(filter->GetOutput());
    
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    mRenderer->AddActor(actor);
    mRenderer->ResetCamera();
    mRenderer->ResetCameraClippingRange();
    mVTKWidget->renderWindow()->Render();
}

 

} // namespace FC
