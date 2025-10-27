/******************************************************************************
 * File     : FCCommandInterface.h
 * Brief    : 命令接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   : 程序自己维护QUndoStack，并注册到QUndoGroup中
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCCommandInterface.h"
#include "FCUIInterface.h"

namespace FC {
class FCCommandInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCCommandInterface)
public:
    PrivateData(FCCommandInterface* p);
    QUndoGroup mUndoGroup;
};

//===================================================
// FCCommandInterfacePrivate
//===================================================
FCCommandInterface::PrivateData::PrivateData(FCCommandInterface* p) : q_ptr(p)
{
}
//===================================================
// FCCommandInterface
//===================================================
FCCommandInterface::FCCommandInterface(FCUIInterface* u)
    : FCBaseInterface(u->core(), u), FC_PIMPL_CONSTRUCT
{
}

FCCommandInterface::~FCCommandInterface()
{
}

/**
 * @brief 获取undo/redoGroup
 * @return
 */
QUndoGroup& FCCommandInterface::undoGroup()
{
    return d_ptr->mUndoGroup;
}

/**
 * @brief 添加stack
 * @param stack
 */
void FCCommandInterface::addStack(QUndoStack* stack)
{
    d_ptr->mUndoGroup.addStack(stack);
}

void FCCommandInterface::removeStack(QUndoStack* stack)
{
    d_ptr->mUndoGroup.removeStack(stack);
}


} // namespace FC
