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
#include <vtkSmartPointer.h>


class QVTKOpenGLNativeWidget;
class vtkRenderer;


namespace FC 
{
class FCGeometrySet;

class FCGUI_API FCGraphicOperateWidget : public QWidget
{
    Q_OBJECT
public:
    FCGraphicOperateWidget(QWidget* parent = nullptr);
    ~FCGraphicOperateWidget();
    
public slots:
    void showModel(FCGeometrySet* set, bool r);

    
private:
   
    QVTKOpenGLNativeWidget* mVTKWidget = NULL;
    vtkSmartPointer<vtkRenderer> mRenderer;
    
    
signals:
};
} // namespace FC



#endif // FCGRAPHICOPERATEWIDGET_H
