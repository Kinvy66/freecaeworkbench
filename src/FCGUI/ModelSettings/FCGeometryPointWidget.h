/**
 * @file FCGeometryPointWidget.h
 * @brief 自定义三维坐标点拾取部件
 * @date 2025-12-02
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPOINTWIDGET_H
#define FCGEOMETRYPOINTWIDGET_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCGeometryPointWidget;
}

namespace FC 
{

class FCGUI_API FCGeometryPointWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FCGeometryPointWidget(QWidget *parent = nullptr);
    ~FCGeometryPointWidget();
    
private:
    Ui::FCGeometryPointWidget *ui;
};
} // namespace FC


#endif // FCGEOMETRYPOINTWIDGET_H
