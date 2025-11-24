/**
 * @file FCStatusBar.cpp
 * @brief 状态栏
 * @date 2025-11-14
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCStatusBar.h"
#include <QLabel>


namespace FC 
{

FCStatusBar::FCStatusBar(QWidget *par)
    : QStatusBar(par)
{
    QLabel* lab = new QLabel(this);
    lab->setText("Status");
}

} // namespace FC

