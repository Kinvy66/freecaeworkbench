/******************************************************************************
 * File     : FCUIInterface.h
 * Brief    : 界面相关接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   : 界面相关的接口都继承此接口
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCUIINTERFACE_H
#define FCUIINTERFACE_H

#include "FCBaseInterface.h"
#include "FCInterfaceAPI.h"
#include "FCGlobals.h"
#include <QObject>
#include "FCBaseInterface.h"

class SARibbonMainWindow;
class QMainWindow;

namespace FC
{
class FCCoreInterface;
class FCUIExtendInterface;
class FCActionsInterface;
class FCCommandInterface;
class FCDockingAreaInterface;
class FCRibbonAreaInterface;

class FCINTERFACE_API FCUIInterface : public FCBaseInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCUIInterface)
public:
    FCUIInterface(SARibbonMainWindow* m, FCCoreInterface* c);
    ~FCUIInterface();
    
    
    //获取主窗口
    SARibbonMainWindow* mainWindow() const;
    
    //发生语言变更时会调用此函数,此函数将调用所有扩展的retranslateUi函数
    virtual void retranslateUi();
    
    //注册action管理器
    void registeAction(FCActionsInterface* ac);
    
    //注册扩展
    void registeExtend(FCUIExtendInterface* ex);
    
    //注册命令接口
    void registeCommand(FCCommandInterface* cmd);
    
    //获取扩展数量
    int getExtendCount() const;
    
    //获取扩展
    FCUIExtendInterface* getExtend(int index);
    
    //获取命令接口，如果没有注册命令接口，返回nullptr，当前设计为一个命令接口
    FCCommandInterface* getCommandInterface() const;
    
    //获取action管理器
    FCActionsInterface* getActionInterface() const;
    
public:
    //下面是默认的extend
    //获取主程序,此函数和getRibbonArea()->app()是一样的返回结果
    virtual QMainWindow* getMainWindow() const = 0;
    
    //获取界面的docking区域
    virtual FCDockingAreaInterface* getDockingArea() = 0;
    
    //获取界面的ribbon区域
    virtual FCRibbonAreaInterface* getRibbonArea() = 0;
    
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
};

} // namespace FC

#endif // FCUIINTERFACE_H
