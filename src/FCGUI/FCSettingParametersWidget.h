/******************************************************************************
 * File     : FCSettingParametersWidget.h
 * Brief    : 模型参数设置窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-31
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCSETTINGPARAMETERSWIDGET_H
#define FCSETTINGPARAMETERSWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"

namespace FC 
{
class FCGUI_API FCSettingParametersWidget : public QWidget
{
    Q_OBJECT
public:
    FCSettingParametersWidget(QWidget* parent = nullptr);
    ~FCSettingParametersWidget();
    
signals:
};
} // namespace FC



#endif // FCSETTINGPARAMETERSWIDGET_H
