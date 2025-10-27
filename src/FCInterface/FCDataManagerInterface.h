/******************************************************************************
 * File     : FCDataManagerInterface.h
 * Brief    : 数据管理接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
