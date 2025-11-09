/******************************************************************************
 * File     : FCGraphicOperateWidget.h
 * Brief    : 可视化交互窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-31
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCGraphicOperateWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <array>

#ifdef VTK_TEST_DEMO
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
#endif

// OCC
#ifdef OCC_TEST_DEMO
#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx>
#include <V3d_View.hxx>
#endif 

namespace FC 
{

FCGraphicOperateWidget::FCGraphicOperateWidget(QWidget *parent)
 : QWidget(parent)
{
    
    QLabel* lab = new QLabel(this);
    lab->setText("GraphicOperateWidget");
    

#ifdef VTK_TEST_DEMO
    _pVTKWidget = new QVTKOpenGLNativeWidget(this);
    // 使用布局让 _pVTKWidget 填满整个 FCGraphicOperateWidget
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);  // 去掉边距
    layout->addWidget(_pVTKWidget);
    
    // 立方体
    std::array<std::array<double,3>,8> pts ={ // 8顶点
        {{{0, 0, 0}},
         {{1, 0, 0}},
         {{1, 1, 0}},
         {{0, 1, 0}},
         {{0, 0, 1}},
         {{1, 0, 1}},
         {{1, 1, 1}},
         {{0, 1, 1}}}
    };
    
    // 定义每个面用到的顶点
    std::array<std::array<vtkIdType, 4>,6> ordering = {
        {{{0, 1, 2, 3}},
         {{4, 5, 6, 7}},
         {{0, 1, 5, 4}},
         {{1, 2, 6, 5}},
         {{2, 3, 7, 6}},
         {{3, 0, 4, 7}}}
    };
    
    // 定义立方体
    vtkNew<vtkPolyData> cube;
    vtkNew<vtkPoints> points;
    vtkNew<vtkCellArray> polys;
    vtkNew<vtkFloatArray> scalars;      // 定义属性
    
    
    // 把定义的点数据添加到vtk points
    for (size_t i = 0; i < pts.size(); ++i) {
        points->InsertPoint(i, pts[i].data());
        scalars->InsertTuple1(i, i);
        
    }
    
    for (auto&& i : ordering) {
        polys->InsertNextCell(vtkIdType(i.size()), i.data());
    }
    
    cube->SetPoints(points);
    cube->SetPolys(polys);
    cube->GetPointData()->SetScalars(scalars);
    
    
    vtkNew<vtkPolyDataMapper> mapper;
    vtkNew<vtkActor> actor;
    mapper->SetInputData(cube);
    mapper->SetScalarRange(cube->GetScalarRange());
    actor->SetMapper(mapper);
    
    // renderer 
    vtkNew<vtkRenderer> renderer;
    renderer->SetBackground(230.0 / 255.0, 242.0 / 255.0, 255.0 / 255.0);
    renderer->SetBackground2(250.0 / 255.0, 251.0 / 255.0, 255.0 / 255.0);
    renderer->GradientBackgroundOn();
    
    renderer->AddActor(actor);
    
    this->_pVTKWidget->renderWindow()->AddRenderer(renderer);
    this->_pVTKWidget->renderWindow()->Render();
    
#endif
    
#ifdef OCC_TEST_DEMO
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    
    // Graphic driver
    Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(nullptr);
    mViewer = new V3d_Viewer(driver);
    mViewer->SetDefaultLights();
    mViewer->SetLightOn();
    
    // Create view and window
    mView = mViewer->CreateView();
    Handle(WNT_Window) wnd = new WNT_Window((HWND)winId());
    mView->SetWindow(wnd);
    if (!wnd->IsMapped())
        wnd->Map();
    
    mContext = new AIS_InteractiveContext(mViewer);
    
    // Display a box
    TopoDS_Shape box = BRepPrimAPI_MakeBox(100, 80, 60).Shape();
    Handle(AIS_Shape) aisBox = new AIS_Shape(box);
    mContext->Display(aisBox, Standard_True);
    
    // Initial draw
    mView->FitAll();
    mView->Redraw();
#endif 
    
}

FCGraphicOperateWidget::~FCGraphicOperateWidget()
{
    
}

#ifdef OCC_TEST_DEMO
void FCGraphicOperateWidget::paintEvent(QPaintEvent *)
{
    if (!mView.IsNull())
        mView->Redraw();
}

void FCGraphicOperateWidget::resizeEvent(QResizeEvent *)
{
    if (!mView.IsNull())
        mView->MustBeResized();
}
#endif 

} // namespace FC
