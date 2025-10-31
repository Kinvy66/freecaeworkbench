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
#ifndef FCMESSAGELOGVIEWWIDGET_H
#define FCMESSAGELOGVIEWWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"
class QMenu;

namespace Ui {
class FCMessageLogViewWidget;
}

namespace FC 
{
class FCGUI_API FCMessageLogViewWidget : public QWidget
{
    Q_OBJECT
    
public:
    FCMessageLogViewWidget(QWidget *parent = nullptr);
    ~FCMessageLogViewWidget();
    
private:
    Ui::FCMessageLogViewWidget *ui;
};
} // namespace FC

#endif // FCMESSAGELOGVIEWWIDGET_H
