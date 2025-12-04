/**
 * @file FCConeSettingsWidget.cpp
 * @brief 圆锥参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCConeSettingsWidget.h"
#include "ui_FCConeSettingsWidget.h"

FCConeSettingsWidget::FCConeSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCConeSettingsWidget)
{
    ui->setupUi(this);
}

FCConeSettingsWidget::~FCConeSettingsWidget()
{
    delete ui;
}
