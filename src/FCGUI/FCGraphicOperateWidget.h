/**
 * @file FCGraphicOperateWidget.h
 * @brief 可视化交互窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
