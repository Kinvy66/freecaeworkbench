/******************************************************************************
 * File     : FCUIExtendInterface.h
 * Brief    : FCAppUIInterface下面的扩展模块
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
