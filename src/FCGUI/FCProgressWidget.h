/**
 * @file FCProgressWidget.h
 * @brief 进度显示窗口
 * @date 2025-11-08
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
