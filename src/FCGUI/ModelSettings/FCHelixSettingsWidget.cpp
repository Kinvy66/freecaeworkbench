/**
 * @file FCHelixSettingsWidget.cpp
 * @brief 螺旋参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCHelixSettingsWidget.h"
#include "ui_FCHelixSettingsWidget.h"

FCHelixSettingsWidget::FCHelixSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCHelixSettingsWidget)
{
    ui->setupUi(this);
}

FCHelixSettingsWidget::~FCHelixSettingsWidget()
{
    delete ui;
}
