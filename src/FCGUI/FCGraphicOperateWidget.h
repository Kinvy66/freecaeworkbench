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
class FCGraphViewWindow;

class FCGUI_API FCGraphicOperateWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCGraphicOperateWidget(QWidget* parent = nullptr);
    ~FCGraphicOperateWidget();
    
    // 更新前处理Actor
    void updateActors();
    
    // 更新前处理网格Actor
    void updateMeshActor();
    
    // 更新前处理几何Actor
    void updateGeometryActor();
    
    FCGraphViewWindow*	getGraphViewWindow();
    
signals:
    void showGeoSet(FCGeometrySet *set, bool render = true);
    void removeGeometryAcotr(const IdType id);
public slots:
    void showModel(FCGeometrySet* set, bool r);

    
private:
   
    QVTKOpenGLNativeWidget* mVTKWidget = NULL;
    vtkSmartPointer<vtkRenderer> mRenderer;
    
    // 图形显示窗口
    FCGraphViewWindow* mGraphViewWindow;
    
};
} // namespace FC



#endif // FCGRAPHICOPERATEWIDGET_H
