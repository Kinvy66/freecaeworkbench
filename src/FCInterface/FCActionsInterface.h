/**
 * @file FCActionsInterface.h
 * @brief action 管理类
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCACTIONSINTERFACE_H
#define FCACTIONSINTERFACE_H

#include <QAction>
#include "FCGlobals.h"
#include "FCUIInterface.h"

class QActionGroup;

namespace FC {
class FCCoreInterface;

class FCINTERFACE_API FCActionsInterface : public FCBaseInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCActionsInterface)
public:
    FCActionsInterface(FCUIInterface* u);
    ~FCActionsInterface();
    //创建一个action,并管理
    QAction* createAction(const char* objname);
    QAction* createAction(const char* objname, bool checkable, bool checked = false, QActionGroup* actGroup = nullptr);
    QAction* createAction(const char* objname, const char* iconpath);
    QAction* createAction(const char* objname, const char* iconpath, bool checkable, bool checked = false, QActionGroup* actGroup = nullptr);
    //记录action，action要保证有独立的object name
    void recordAction(QAction* act);
    //发生语言变更时会调用此函数
    virtual void retranslateUi();
    //查找action
    QAction* findAction(const char* objname);
    QAction* findAction(const QString& objname);
};


} // namespace FC

#endif // FCACTIONSINTERFACE_H

