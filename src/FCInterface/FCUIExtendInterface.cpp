/**
 * @file FCUIExtendInterface.cpp
 * @brief FCAppUIInterface下面的扩展模块
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCUIExtendInterface.h"
#include "FCUIInterface.h"

namespace FC 
{
//===================================================
// DAAppUIExtendInterface
//===================================================
FCUIExtendInterface::FCUIExtendInterface(FCUIInterface* u)
    : FCBaseInterface(u->core(), u)
{
}

FCUIExtendInterface::~FCUIExtendInterface()
{
}

FCUIInterface* FCUIExtendInterface::ui() const
{
    return qobject_cast< FCUIInterface* >(parent());
}
} // namespace FC
