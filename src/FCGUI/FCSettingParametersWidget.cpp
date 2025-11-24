/**
 * @file FCSettingParametersWidget.cpp
 * @brief 模型参数设置窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
