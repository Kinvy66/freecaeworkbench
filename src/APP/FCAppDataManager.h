/**
 * @file FCAppDataManager.h
 * @brief FC的工程数据管理
 * @date 2025-11-18
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
