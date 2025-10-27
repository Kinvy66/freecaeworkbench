/******************************************************************************
 * File     : FCCoreInterface.h
 * Brief    : APP的核心接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   : 所有接口都可以通过此接口获取，这个接口是最关键的接口
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCCOREINTERFACE_H
#define FCCOREINTERFACE_H

#include "FCInterfaceAPI.h"
#include <QObject>
#include <QDir>
#include <QTemporaryDir>

class SARibbonMainWindow;

namespace FC {

class FCUIInterface;
class FCDataManagerInterface;
class FCProjectInterface;

class FCINTERFACE_API FCCoreInterface  : public QObject
{
    Q_OBJECT
public:
    FCCoreInterface(QObject* parent = nullptr);
    virtual ~FCCoreInterface();
    
    // 初始化函数，初始化函数里构造出FCAppUIInterface，FCDataManagerInterface等实例
    virtual bool initialized() = 0;
    
    // 获取FCAppRibbonAreaInterface
    virtual FCUIInterface* getUiInterface() const = 0;
    // 获取工程管理借口
    virtual FCProjectInterface* getProjectInterface() const = 0;
    // 获取数据管理接口
    virtual FCDataManagerInterface* getDataManagerInterface() const = 0;
    
public:
    // 工程是否dirty的操作
    bool isProjectDirty() const;
    void setProjectDirty(bool on);
    
    // 工程的临时目录
    QDir getTempDir() const;
    
public:
    // 调用此函数，创建DAAppRibbonAreaInterface，此函数的调用应该发生在SARibbonMainWindow的构造过程
    virtual void createUi(SARibbonMainWindow* mainwindow) = 0;
    
private:
    QTemporaryDir mTempDir;  // 工程临时工作目录
};

} // namespace DA

#endif // FCCOREINTERFACE_H
