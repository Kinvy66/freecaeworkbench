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
    
protected:
    // 处理窗口显示事件，在窗口首次显示时设置最大化状态，避免闪动
    void showEvent(QShowEvent* event) override;
    // 处理窗口状态变化事件，避免在最大化状态下设置几何尺寸
    void changeEvent(QEvent* event) override;
    
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
