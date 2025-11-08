/******************************************************************************
 * File     : FCProgressWidget.h
 * Brief    : 进度显示窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-08
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCPROGRESSWIDGET_H
#define FCPROGRESSWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"

namespace Ui {
class FCProgressWidget;
}
namespace FC 
{
class FCGUI_API FCProgressWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FCProgressWidget(QWidget *parent = nullptr);
    ~FCProgressWidget();
    
private:
    Ui::FCProgressWidget *ui;
};
} // namespace FC



#endif // FCPROGRESSWIDGET_H
