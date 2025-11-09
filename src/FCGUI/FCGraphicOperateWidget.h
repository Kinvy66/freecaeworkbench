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
#ifndef FCGRAPHICOPERATEWIDGET_H
#define FCGRAPHICOPERATEWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"

#define VTK_TEST_DEMO

#ifdef OCC_TEST_DEMO
#include <Aspect_Handle.hxx>
#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#endif

#ifdef VTK_TEST_DEMO
class QVTKOpenGLNativeWidget;
#endif

namespace FC 
{

class FCGUI_API FCGraphicOperateWidget : public QWidget
{
    Q_OBJECT
public:
    FCGraphicOperateWidget(QWidget* parent = nullptr);
    ~FCGraphicOperateWidget();
    
private:
   
    #ifdef VTK_TEST_DEMO
    QVTKOpenGLNativeWidget* _pVTKWidget = NULL;
    #endif
    
#ifdef OCC_TEST_DEMO
    Handle(V3d_Viewer) mViewer;
    Handle(V3d_View) mView;
    Handle(AIS_InteractiveContext) mContext;
    
protected:
    void paintEvent(QPaintEvent* ) override;
    void resizeEvent(QResizeEvent *) override;
#endif
signals:
};
} // namespace FC



#endif // FCGRAPHICOPERATEWIDGET_H
