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
#include <QVBoxLayout>
#include "FCBoxSettingsWidget.h"

namespace FC 
{

FCSettingParametersWidget::FCSettingParametersWidget(QWidget *parent)
 : QWidget(parent)
{
    // QLabel* lab = new QLabel(this);
    // lab->setText("Setting Docking");
}

FCSettingParametersWidget::~FCSettingParametersWidget()
{
    
}

void FCSettingParametersWidget::createCube()
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    FCBoxSettingsWidget* cubeSettingsWidget = new FCBoxSettingsWidget(this);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::boxModelCreated,
            this, &FCSettingParametersWidget::boxModelCreated);
    
    
    vLayout->addWidget(cubeSettingsWidget);
}

} // namespace FC
