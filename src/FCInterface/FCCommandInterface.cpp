/**
 * @file FCCommandInterface.cpp
 * @brief 命令接口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 程序自己维护QUndoStack，并注册到QUndoGroup中
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
