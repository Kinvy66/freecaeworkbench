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
#include "FCCylinderSettingsWidget.h"

namespace FC 
{

FCSettingParametersWidget::FCSettingParametersWidget(QWidget *parent)
 : QWidget(parent)
{
    // QLabel* lab = new QLabel(this);
    // lab->setText("Setting Docking");
    mLayout = new QVBoxLayout(this);
    
}

FCSettingParametersWidget::~FCSettingParametersWidget()
{
    
}

void FCSettingParametersWidget::createCube()
{
    FCBoxSettingsWidget* cubeSettingsWidget = new FCBoxSettingsWidget(this);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    cubeSettingsWidget->create();
    
    setCurrentWidget(cubeSettingsWidget);
    
}

void FCSettingParametersWidget::createCylinder()
{
    FCCylinderSettingsWidget* cylinderSettingsWidget = new FCCylinderSettingsWidget(this);
    connect(cylinderSettingsWidget, &FCCylinderSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    
    setCurrentWidget(cylinderSettingsWidget);
}

void FCSettingParametersWidget::setCurrentWidget(QWidget *w)
{
    if (mCurrentWidget) {
        mLayout->removeWidget(mCurrentWidget);
        mCurrentWidget->deleteLater();
    }
    mCurrentWidget = w;
    mLayout->addWidget(w);
}

} // namespace FC
