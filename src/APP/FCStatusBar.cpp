/******************************************************************************
 * File     : FCStatusBar.h
 * Brief    : 状态栏
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-14
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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

