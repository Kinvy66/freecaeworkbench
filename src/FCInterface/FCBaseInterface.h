/**
 * @file FCBaseInterface.h
 * @brief 基础接口类
 * @date 2025-10-27
 * @version V0.0.1
 * @details 数据，action,ui等都继承自此类
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCBASEINTERFACE_H
#define FCBASEINTERFACE_H

#include <QObject>
#include "FCInterfaceAPI.h"

namespace FC {
class FCCoreInterface;
class FCINTERFACE_API FCBaseInterface : public QObject
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCBaseInterface)
    
public:
    FCBaseInterface(FCCoreInterface* c, QObject* par = nullptr);
    ~FCBaseInterface();
    //返回核心接口指针
    FCCoreInterface* core() const;
};

} // namespace FC



#endif // FCBASEINTERFACE_H
