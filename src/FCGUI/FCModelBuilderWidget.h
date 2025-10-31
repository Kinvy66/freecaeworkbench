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
#ifndef FCMODELBUILDERWIDGET_H
#define FCMODELBUILDERWIDGET_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace FC 
{
class FCGUI_API FCModelBuilderWidget : public QWidget
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCModelBuilderWidget)
public:
    FCModelBuilderWidget(QWidget* parent = nullptr);
    ~FCModelBuilderWidget();
    
signals:
};

} // namespace FC

#endif // FCMODELBUILDERWIDGET_H
