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

#include "FCBaseInterface.h"
#include "FCCoreInterface.h"

namespace FC {
//===================================================
// FCBaseInterfacePrivate
//===================================================
class FCBaseInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCBaseInterface)
public:
    PrivateData(FCBaseInterface* p, FCCoreInterface* c);
    
    FCCoreInterface* mCore;
};

FCBaseInterface::PrivateData::PrivateData(FCBaseInterface* p, FCCoreInterface* c) : q_ptr(p), mCore(c)
{
}
//===================================================
// FCBaseInterface
//===================================================
FCBaseInterface::FCBaseInterface(FCCoreInterface* c, QObject* par)
    : QObject(par), d_ptr(std::make_unique< FCBaseInterface::PrivateData >(this, c))
{
}

FCBaseInterface::~FCBaseInterface()
{
}

FCCoreInterface* FCBaseInterface::core() const
{
    return d_ptr->mCore;
}

} // namespace FC

