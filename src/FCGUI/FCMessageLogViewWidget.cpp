/******************************************************************************
 * File     : FCMessageLogViewWidget.h
 * Brief    : 日志窗口，用于显示全局的消息
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCMessageLogViewWidget.h"
#include "ui_FCMessageLogViewWidget.h"
#include <QDebug>
#include <QMenu>
#include <QItemSelectionModel>
#include <QClipboard>
#include <QApplication>
#include <QKeyEvent>
#include <QPushButton>

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

FCMessageLogViewWidget::FCMessageLogViewWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCMessageLogViewWidget)
{
    ui->setupUi(this);
    
    auto btn = new QPushButton(this);
    btn->setText("Log View");
}

FCMessageLogViewWidget::~FCMessageLogViewWidget()
{
    delete ui;
}
