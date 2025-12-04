/**
 * @file FCTorusSettingsWidget.cpp
 * @brief 环面参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCTorusSettingsWidget.h"
#include "ui_FCTorusSettingsWidget.h"

FCTorusSettingsWidget::FCTorusSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCTorusSettingsWidget)
{
    ui->setupUi(this);
}

FCTorusSettingsWidget::~FCTorusSettingsWidget()
{
    delete ui;
}
