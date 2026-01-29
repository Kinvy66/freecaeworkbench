/**
 * @file FCOperatorRepoPrivate.h
 * @brief 创建并维护操作器类声明
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef _FC_OPERATOR_REPO_PRIVATE_H__
#define _FC_OPERATOR_REPO_PRIVATE_H__

#include "FCActionOperatorsAPI.h"
#include "FCAbstractOperatorBase.h"
#include <QObject>
#include <QHash>
#include <QString>
#include <functional>

namespace FC
{
/**
 * @brief 创建操作器与维护操作器
 */
class FCACTIONOPERATORS_API FCOperatorRepoPrivate : public QObject
{
    Q_OBJECT
public:
    explicit FCOperatorRepoPrivate(QHash<QString, std::function<FCAbstractOperatorBase*()>>& funs);
    virtual ~FCOperatorRepoPrivate();

    FCAbstractOperatorBase* getOperator(const QString& key);
    void removeOperator(const QString& key, bool removeFun = true);
    void registerOperatorFunction(const QString& key, std::function<FCAbstractOperatorBase*()> fun);

private:
    FCAbstractOperatorBase* createOperator(const QString& key);

private slots:
    void operatorDestoryedSlot(FCAbstractOperatorBase* oper);

private:
    QHash<QString, std::function<FCAbstractOperatorBase*()>>& _createFuns;
    QHash<QString, FCAbstractOperatorBase*> _existOperators{};
};
}

#endif
