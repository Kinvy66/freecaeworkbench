/**
 * @file FCSettingParametersWidget.h
 * @brief 模型参数设置窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCSETTINGPARAMETERSWIDGET_H
#define FCSETTINGPARAMETERSWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"

namespace FC 
{
class FCGeometrySet;

class FCGUI_API FCSettingParametersWidget : public QWidget
{
    Q_OBJECT
public:
    FCSettingParametersWidget(QWidget* parent = nullptr);
    ~FCSettingParametersWidget();
    
    void createCube();
    
signals:
    void boxModelCreated(FCGeometrySet* set, bool r);
    
};
} // namespace FC



#endif // FCSETTINGPARAMETERSWIDGET_H
