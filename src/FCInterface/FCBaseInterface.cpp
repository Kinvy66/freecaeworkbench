/**
 * @file FCBaseInterface.cpp
 * @brief 基础接口类
 * @date 2025-10-27
 * @version V0.0.1
 * @details 数据，action,ui等都继承自此类
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */

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

FCBaseInterface::PrivateData::PrivateData(FCBaseInterface* p, FCCoreInterface* c)
    : q_ptr(p), mCore(c)
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

