/**
 * @file FCDataManagerInterface.h
 * @brief 数据管理接口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCDATAMANAGERINTERFACE_H
#define FCDATAMANAGERINTERFACE_H

#include "FCInterfaceAPI.h"
#include "FCBaseInterface.h"
// #include "FCData.h"
// #include "FCDataManager.h"
class QUndoStack;

namespace FC {
class FCCoreInterface;

class FCINTERFACE_API FCDataManagerInterface : public FCBaseInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCDataManagerInterface)
public:
    FCDataManagerInterface(FCCoreInterface* c, QObject* par = nullptr);
    ~FCDataManagerInterface();
};

} // namespace FC

#endif // FCDATAMANAGERINTERFACE_H
