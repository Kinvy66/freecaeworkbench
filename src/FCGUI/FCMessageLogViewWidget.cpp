/**
 * @file FCMessageLogViewWidget.cpp
 * @brief 日志窗口，用于显示全局的消息
 * @date 2025-10-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
