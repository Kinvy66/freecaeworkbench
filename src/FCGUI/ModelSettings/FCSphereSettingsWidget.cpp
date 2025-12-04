/**
 * @file FCSphereSettingsWidget.cpp
 * @brief 球体参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCSphereSettingsWidget.h"
#include "ui_FCSphereSettingsWidget.h"

FCSphereSettingsWidget::FCSphereSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCSphereSettingsWidget)
{
    ui->setupUi(this);
}

FCSphereSettingsWidget::~FCSphereSettingsWidget()
{
    delete ui;
}
