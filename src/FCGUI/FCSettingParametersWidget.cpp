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
#include "FCSettingParametersWidget.h"
#include <QLabel>

namespace FC 
{

FCSettingParametersWidget::FCSettingParametersWidget(QWidget *parent)
 : QWidget(parent)
{
    QLabel* lab = new QLabel(this);
    lab->setText("Test");
}

FCSettingParametersWidget::~FCSettingParametersWidget()
{
    
}

} // namespace FC
