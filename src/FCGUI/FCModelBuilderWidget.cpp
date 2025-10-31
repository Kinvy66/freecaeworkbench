/******************************************************************************
 * File     : FCModelBuilderWidget.h
 * Brief    : 模型构建窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-31
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCModelBuilderWidget.h"
#include <QDebug>

namespace FC 
{
class FCModelBuilderWidget::PrivateData
{
public:
    FC_DECLARE_PUBLIC(FCModelBuilderWidget)
    PrivateData(FCModelBuilderWidget* p);
    
};
FCModelBuilderWidget::PrivateData::PrivateData(FCModelBuilderWidget* p)
    : q_ptr(p)
{
}

FCModelBuilderWidget::FCModelBuilderWidget(QWidget *parent)
    : QWidget(parent)
{
    
}

FCModelBuilderWidget::~FCModelBuilderWidget()
{
    
}

} // namespace FC
