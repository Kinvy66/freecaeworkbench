/******************************************************************************
 * File     : FCModelTreeWidget.cpp
 * Brief    : 模型树
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-12
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCMODELTREEWIDGET_H
#define FCMODELTREEWIDGET_H
#include "FCGuiAPI.h"

#include <QObject>
#include <QWidget>

namespace FC 
{
class FCGUI_API FCModelTreeWidget : public QWidget
{
Q_OBJECT
    
public:
    explicit FCModelTreeWidget(QWidget *parent = nullptr);
    ~FCModelTreeWidget();
};
} // namespace FC



#endif // FCMODELTREEWIDGET_H
