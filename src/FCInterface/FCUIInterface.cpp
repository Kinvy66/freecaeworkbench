/******************************************************************************
 * File     : FCUIInterface.h
 * Brief    : 界面相关接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   : 界面相关的接口都继承此接口
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCUIInterface.h"
#include "FCUIExtendInterface.h"
#include "FCActionsInterface.h"
#include <QEvent>
#include "SARibbonMainWindow.h"

namespace FC {
class FCUIInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCUIInterface)
public:
    PrivateData(FCUIInterface* p);
    
public:
    SARibbonMainWindow* mMainWindow;
    FCCommandInterface* mCmd { nullptr };
    FCActionsInterface* mActionMgr { nullptr };
    QList< FCUIExtendInterface* > mExtends;
};

//===================================================
// FCAppUIInterfacePrivate
//===================================================

FCUIInterface::PrivateData::PrivateData(FCUIInterface* p) : q_ptr(p)
{
}
//===================================================
// FCAppUIInterface
//===================================================
FCUIInterface::FCUIInterface(SARibbonMainWindow* m, FCCoreInterface* c)
    : FCBaseInterface(c, m), FC_PIMPL_CONSTRUCT
{
    d_ptr->mMainWindow = m;
    if (m) {
        m->installEventFilter(this);
    }
}

FCUIInterface::~FCUIInterface()
{
    if (mainWindow()) {
        mainWindow()->removeEventFilter(this);
    }
}

/**
 * @brief 获取主窗口
 * @return 返回主窗口指针
 */
SARibbonMainWindow* FCUIInterface::mainWindow() const
{
    return (d_ptr->mMainWindow);
}


/**
 * @brief 发生语言变更时会调用此函数
 *
 * @sa DAAppUIInterface 的 @sa retranslateUi 不做任何动作，其继承的类可以通过重载此函数实现翻译
 */
void FCUIInterface::retranslateUi()
{
    int es = getExtendCount();
    for (int i = 0; i < es; ++i) {
        // getExtend(i)->retranslateUi();
    }
    if (d_ptr->mActionMgr) {
        d_ptr->mActionMgr->retranslateUi();
    }
}

void FCUIInterface::registeAction(FCActionsInterface* ac)
{
    d_ptr->mActionMgr = ac;
}

/**
 * @brief 注册扩展
 *
 * 界面是由各个扩展组成，包括最原始的界面，是由FCAppDockingAreaInterface和FCAppRibbonAreaInterface，
 * 这两个扩展组成
 *
 * @param ex
 */
void FCUIInterface::registeExtend(FCUIExtendInterface* ex)
{
    d_ptr->mExtends.append(ex);
}

/**
 * @brief 注册命令接口
 * @param cmd
 */
void FCUIInterface::registeCommand(FCCommandInterface* cmd)
{
    d_ptr->mCmd = cmd;
}

/**
 * @brief 获取扩展的数量
 * @return
 */
int FCUIInterface::getExtendCount() const
{
    return d_ptr->mExtends.size();
}

/**
 * @brief 获取扩展
 * @param index
 * @return 如果超出索引范围，返回nullptr
 */
FCUIExtendInterface* FCUIInterface::getExtend(int index)
{
    return d_ptr->mExtends.value(index, nullptr);
}

/**
 * @brief 获取命令接口
 * @sa registeCommand
 * @return 如果没有注册命令接口，返回nullptr
 */
FCCommandInterface* FCUIInterface::getCommandInterface() const
{
    return d_ptr->mCmd;
}

/**
 * @brief 获取action管理器
 * @return
 */
FCActionsInterface* FCUIInterface::getActionInterface() const
{
    return d_ptr->mActionMgr;
}

bool FCUIInterface::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == mainWindow()) {
        // 如果发现语言变更，调用retranslateUi()
        if (event && (event->type() == QEvent::LanguageChange)) {
            retranslateUi();
        }
    }
    return (QObject::eventFilter(watched, event));
}

} // namespace FC



