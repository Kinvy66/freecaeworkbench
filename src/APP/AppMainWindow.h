/**
 * @file AppMainWindow.h
 * @brief 主窗口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef DAMETHODEDITORMAINWINDOW_H
#define DAMETHODEDITORMAINWINDOW_H

#include "SARibbonMainWindow.h"

// #include <Aspect_Handle.hxx>
// #include <AIS_InteractiveContext.hxx>
// #include <V3d_Viewer.hxx>
// #include <AIS_Shape.hxx>
// #include <BRepPrimAPI_MakeBox.hxx>

QT_BEGIN_NAMESPACE
namespace Ui {
class AppMainWindow;
}
QT_END_NAMESPACE

class QCloseEvent;
class QEvent;
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
    // 初始化
    void init();
    
    // 初始化插件
    void initPlugins();
    
    
private:
    FCAppCore* mCore { nullptr };
    FCAppUI* mUI { nullptr };
    FCAppDockingArea* mDockArea { nullptr };
    FCAppController* mController { nullptr };
    bool mFirstShow { true };  // 标记是否是首次显示
};

}  // namespace FC
#endif  // METHODMAINWINDOW_H
