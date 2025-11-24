/**
 * @file FCAppCommand.h
 * @brief App的命令管理类
 * @date 2025-10-28
 * @version V0.0.1
 * @details 所有的固定stack都从这里能获取到，一些非固定stack不进行管理 
 * QUndoGroup管理所有的栈
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCAPPCOMMAND_H
#define FCAPPCOMMAND_H

#include <FCCommandInterface.h>
#include <QUndoStack>
#include <QPointer>

namespace FC 
{

class FCAppCommand : public FCCommandInterface
{
    Q_OBJECT
public:
    FCAppCommand(FCUIInterface* u);
    ~FCAppCommand();
    
public:
    // 数据管理的redo/undo栈
    QUndoStack* getDataManagerStack() const;
    // TODO:工作流的redo/undo栈
    
    // TODO:绘图的redo/undo栈（每个图片一个栈）
public:
    void setDataManagerStack(QUndoStack* s);
    
private:
    QPointer< QUndoStack > mDataManagerStack;
    
};

} // namespace FC


#ifndef FC_APP_COMMAND
/**
 * @def 获取@sa FCAppCommand 实例
 *
 * @note 需要以下include：
 * @code
 * #include "FCAppCore.h"
 * #include "FCAppUI.h"
 * @endcode
 *
 */
#define FC_APP_COMMAND FC::FCAppCore::getInstance().getUi()->getAppCmd()
#endif

#endif // FCAPPCOMMAND_H
