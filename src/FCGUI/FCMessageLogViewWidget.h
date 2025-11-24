/**
 * @file FCMessageLogViewWidget.h
 * @brief 日志窗口，用于显示全局的消息
 * @date 2025-10-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
