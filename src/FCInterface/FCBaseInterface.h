/******************************************************************************
 * File     : FCBaseInterface.h
 * Brief    : 基础接口类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   : 数据，action,ui等都继承自此类
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
