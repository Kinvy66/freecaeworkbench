/******************************************************************************
 * File     : FCActionsInterface.cpp
 * Brief    : action 管理类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCActionsInterface.h"
#include "FCCoreInterface.h"
#include <QHash>
#include <QDebug>
#include <QActionGroup>

namespace FC {
class FCActionsInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCActionsInterface)
public:
    PrivateData(FCActionsInterface* p);
    
public:
    QHash< QString, QAction* > mObjectToAction;
};
}

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================
using namespace FC;

/**
 * @brief FCAppActionsInterfacePrivate
 * @param p
 */
FCActionsInterface::PrivateData::PrivateData(FCActionsInterface* p)
    : q_ptr(p)
{
}

/**
 * @brief FCActionsInterface
 * @param u
 */
FCActionsInterface::FCActionsInterface(FCUIInterface* u)
    : FCBaseInterface(u->core(), u), FC_PIMPL_CONSTRUCT
{
}

FCActionsInterface::~FCActionsInterface()
{
    
}

/**
 * @brief 创建一个action，并记录它
 *
 * action的Enabled状态会根据PythonInterpreterInitialized进行设置
 * @param objname
 * @param iconpath
 * @return
 */
QAction* FCActionsInterface::createAction(const char* objname)
{
    QAction* act = new QAction(this);
    act->setObjectName(QString::fromUtf8(objname));
    recordAction(act);
    return act;
}

/**
 * @brief FCActionsInterface::createAction
 * @param objname
 * @param checkable
 * @param checked
 * @return
 */
QAction* FCActionsInterface::createAction(const char* objname,
                                          bool checkable, bool checked,
                                          QActionGroup* actGroup)
{
    QAction* act = createAction(objname);
    act->setCheckable(checkable);
    act->setChecked(checked);
    if (actGroup) {
        act->setActionGroup(actGroup);
    }
    return act;
}

/**
 * @brief 创建一个action，并记录它
 *
 * action的Enabled状态会根据PythonInterpreterInitialized进行设置
 * @param objname
 * @param iconpath
 * @return
 */
QAction* FCActionsInterface::createAction(const char* objname,
                                          const char* iconpath)
{
    QAction* act = createAction(objname);
    act->setIcon(QIcon(iconpath));
    return act;
}
/**
 * @brief 创建一个action，并记录它
 * @param objname
 * @param iconpath
 * @param checkable
 * @param checked
 * @return
 */
QAction* FCActionsInterface::createAction(const char* objname,
                                          const char* iconpath,
                                          bool checkable, bool checked,
                                          QActionGroup* actGroup)
{
    QAction* act = createAction(objname, iconpath);
    act->setCheckable(checkable);
    act->setChecked(checked);
    if (actGroup) {
        act->setActionGroup(actGroup);
    }
    return act;
}
/**
 * @brief 记录action，action要保证有独立的object name
 * @param act
 */
void FCActionsInterface::recordAction(QAction* act)
{
    if (nullptr == act) {
        qWarning() << tr("FCAppActionsInterface::recordAction get null action");
        return;
    }
#ifdef QT_DEBUG
    if (d_ptr->mObjectToAction.contains(act->objectName())) {
        qWarning() << tr("FCAppActionsInterface::recordAction(QAction objname=%1) "
                         "receive same object name, and the "
                         "previous record will be overwritten")
                          .arg(act->objectName());
    }
#endif
    d_ptr->mObjectToAction[ act->objectName() ] = act;
}

/**
 * @brief 实例化的接口需要继承此函数实现语言切换的文本变更
 */
void FCActionsInterface::retranslateUi()
{
}

/**
 * @brief 查找action
 * @param objname
 * @return 如果没有返回nullptr
 */
QAction* FCActionsInterface::findAction(const char* objname)
{
    return d_ptr->mObjectToAction.value(objname, nullptr);
}

/**
 * @brief 查找action
 * @param objname
 * @return 如果没有返回nullptr
 */
QAction* FCActionsInterface::findAction(const QString& objname)
{
    return d_ptr->mObjectToAction.value(objname, nullptr);
}
