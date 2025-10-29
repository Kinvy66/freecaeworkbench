/******************************************************************************
 * File     : FCAppCore.h
 * Brief    : FC的核心接口,作为单例存在
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCAPPCORE_H
#define FCAPPCORE_H

#include "FCCoreInterface.h"

namespace FC 
{

class FCAppCommand;
class FCAppUI;
class FCAppRibbonArea;
class FCAppDataManager;
class FCAppProject;

class FCAppCore : public FCCoreInterface
{
    Q_OBJECT
    FCAppCore(QObject* p = nullptr);
    
public:
    static FCAppCore& getInstance();
    // 初始化
    virtual bool initialized() override;
    // 获取DAAppRibbonAreaInterface
    virtual FCUIInterface* getUiInterface() const override;
    // 获取项目管理借口
    virtual FCProjectInterface* getProjectInterface() const override;
    // 调用此函数，创建DAAppUIInterface，此函数的调用应该发生在SARibbonMainWindow的构造过程
    void createUi(SARibbonMainWindow* mainwindow) override;
    // python内核是否初始化成功
    // bool isPythonInterpreterInitialized() const;
    // 获取数据管理接口
    FCDataManagerInterface* getDataManagerInterface() const override;
    
    
public:
    // 获取DAAppUI，省去qobject_cast
    FCAppUI* getAppUi();
    // 获取DAProject
    FCAppProject* getAppProject();
    // 获取DAAppDataManager，省去qobject_cast
    FCAppDataManager* getAppDatas();
    // 获取DAAppCommand，省去qobject_cast
    FCAppCommand* getAppCmd();
    
private:
    FCAppCommand* mAppCmd;
    FCAppUI* mAppUI;
    FCAppDataManager* mDataManager;
    bool mIsPythonInterpreterInitialized;
    FCAppProject* mProject;
};

} // namespace FC

#ifndef FC_APP_CORE
/**
 * @def 获取@sa FCAppCore 实例
 */
#define FC_APP_CORE FC::FCAppCore::getInstance()
#endif


#endif // FCAPPCORE_H
