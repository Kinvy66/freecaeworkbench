/******************************************************************************
 * File     : FCGraphicOperateWidget.h
 * Brief    : 可视化交互窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-31
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCGraphicOperateWidget.h"
#include <QPushButton>

namespace FC 
{

FCGraphicOperateWidget::FCGraphicOperateWidget(QWidget *parent)
 : QWidget(parent)
{
    
    QPushButton* btn = new QPushButton(this);
}

FCGraphicOperateWidget::~FCGraphicOperateWidget()
{
    
}

} // namespace FC
