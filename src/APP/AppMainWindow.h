/******************************************************************************
 * File     : AppMainWindow.h
 * Brief    : 主窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef DAMETHODEDITORMAINWINDOW_H
#define DAMETHODEDITORMAINWINDOW_H

#include "SARibbonMainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AppMainWindow;
}
QT_END_NAMESPACE

class QCloseEvent;
namespace FC
{
class FCAppCore;
class FCAppRibbonArea;
class FCAppUI;
class FCAppDockingArea;
class FCAppController;
class FCAppConfig;
class FCConfigsManager;
class FCAppSettingDialog;

class AppMainWindow : public SARibbonMainWindow
{
    Q_OBJECT
    friend class DAAppRibbonArea;
public:
    AppMainWindow(QWidget* parent = nullptr);
    ~AppMainWindow();
    
private:
    FCAppCore* mCore { nullptr };
    FCAppUI* mUI { nullptr };
    FCAppDockingArea* mDockArea { nullptr };
    FCAppController* mController { nullptr };
};

}  // namespace FC
#endif  // METHODMAINWINDOW_H
