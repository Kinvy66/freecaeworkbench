/******************************************************************************
 * File     : FCProgressWidget.cpp
 * Brief    : 进度显示窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-08
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCProgressWidget.h"
#include "ui_FCProgressWidget.h"

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

FCProgressWidget::FCProgressWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCProgressWidget)
{
    ui->setupUi(this);
}

FCProgressWidget::~FCProgressWidget()
{
    delete ui;
}
