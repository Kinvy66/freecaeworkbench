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
#include "FCGeometryData.h"

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
    
    // setCurrentWidget(cubeSettingsWidget);
}

void FCSettingParametersWidget::createCylinder()
{
    FCCylinderSettingsWidget* cylinderSettingsWidget = new FCCylinderSettingsWidget(this);
    connect(cylinderSettingsWidget, &FCCylinderSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    
    setCurrentWidget(cylinderSettingsWidget);
}

/**
 * @brief 显示当前选中的item的参数页面
 * @param id
 * @param name
 */
void FCSettingParametersWidget::updateCurrentSettingWidget(const IdType id,
                                                           const QString& name)
{
    Q_UNUSED(name)
    FCGeometrySet* editSet = FCGeometryData::getInstance()->getGeometrySetByID(id);
    if (!editSet) {
        return;
    }

    FCBoxSettingsWidget* cubeSettingsWidget = new FCBoxSettingsWidget(id, this);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::removeActor, this,
            &FCSettingParametersWidget::removeGeometryAcotr);
    
    
    setCurrentWidget(cubeSettingsWidget);
    
    // qDebug() << "updateCurrentWidget id" << id;
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
