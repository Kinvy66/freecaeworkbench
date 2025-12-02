/**
 * @file FCGeometryPointWidget.cpp
 * @brief 自定义三维坐标点拾取部件
 * @date 2025-12-02
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryPointWidget.h"
#include "ui_FCGeometryPointWidget.h"

namespace FC 
{
FCGeometryPointWidget::FCGeometryPointWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCGeometryPointWidget)
{
    ui->setupUi(this);
}

FCGeometryPointWidget::~FCGeometryPointWidget()
{
    delete ui;
}

} // namespace FC

