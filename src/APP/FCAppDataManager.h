/******************************************************************************
 * File     : FCAppDataManager.h
 * Brief    : FC的工程数据管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-18
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCAPPDATAMANAGER_H
#define FCAPPDATAMANAGER_H
#include <QObject>
#include "FCDataManagerInterface.h"
#include <memory>
#include "FCGlobals.h"

namespace FC 
{
FC_IMPL_FORWARD_DECL(FCAppDataManager)

class FCCoreInterface;


class FCAppDataManager : public FCDataManagerInterface
{
    Q_OBJECT
public:
    FCAppDataManager(FCCoreInterface* c, QObject* p = nullptr);
    ~FCAppDataManager();
    
    
};
} // namespace FC

#ifndef FC_APP_DATA
/**
 * @def 获取@sa DataManager 实例
 * @note 使用此宏需要以下头文件：
 * -# FCAppCore.h
 */
#define FC_APP_DATA FC::FCAppCore::getInstance().getDatas()
#endif

#endif // FCAPPDATAMANAGER_H
