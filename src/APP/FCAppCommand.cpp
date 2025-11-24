/**
 * @file FCAppCommand.cpp
 * @brief App的命令管理类
 * @date 2025-10-28
 * @version V0.0.1
 * @details 所有的固定stack都从这里能获取到，一些非固定stack不进行管理 
 * QUndoGroup管理所有的栈
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCAppCommand.h"

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

//===================================================
// FCAppCommand
//===================================================
FCAppCommand::FCAppCommand(FCUIInterface* u) : FCCommandInterface(u)
{
}

FCAppCommand::~FCAppCommand()
{
}

void FCAppCommand::setDataManagerStack(QUndoStack* s)
{
    mDataManagerStack = s;
    addStack(s);
}

QUndoStack* FCAppCommand::getDataManagerStack() const
{
    return mDataManagerStack.data();
}
