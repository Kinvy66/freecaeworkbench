/**
 * @file FCCommandInterface.h
 * @brief 命令接口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 程序自己维护QUndoStack，并注册到QUndoGroup中
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCCOMMANDINTERFACE_H
#define FCCOMMANDINTERFACE_H

#include <QObject>
#include "FCInterfaceAPI.h"
#include "FCBaseInterface.h"
#include <QUndoGroup>
class QUndoStack;

namespace FC {
class FCCoreInterface;
class FCUIInterface;
class FCINTERFACE_API FCCommandInterface : public FCBaseInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCCommandInterface)
public:
    FCCommandInterface(FCUIInterface* u);
    ~FCCommandInterface();
    //获取FCAppUIInterface
    FCUIInterface* ui() const;
    //获取undo/redoGroup
    QUndoGroup& undoGroup();
    //添加stack
    void addStack(QUndoStack* stack);
    //移除stack
    void removeStack(QUndoStack* stack);
};

} // namespace FC
#endif // FCCOMMANDINTERFACE_H
