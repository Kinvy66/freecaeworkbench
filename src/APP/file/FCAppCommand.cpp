/******************************************************************************
 * File     : FCAppCommand.cpp
 * Brief    : App的命令管理类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   : 所有的固定stack都从这里能获取到，一些非固定stack不进行管理
 *            QUndoGroup管理所有的栈
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
