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

#include "FCCoreAPI.h"
#include "FCAbstractOperator.h"
#include <QObject>
#include <QHash>
#include <QString>
#include <functional>

namespace FC
{
/**
 * @brief 创建操作器与维护操作器
 */
class FCCORE_API FCOperatorRepoPrivate : public QObject
{
    Q_OBJECT
public:
    explicit FCOperatorRepoPrivate(QHash<QString, std::function<FCAbstractOperator*()>>& funs);
    virtual ~FCOperatorRepoPrivate();

    FCAbstractOperator* getOperator(const QString& key);
    void removeOperator(const QString& key, bool removeFun = true);
    void registerOperatorFunction(const QString& key, std::function<FCAbstractOperator*()> fun);

private:
    FCAbstractOperator* createOperator(const QString& key);

private slots:
    void operatorDestoryedSlot(FCAbstractOperator* oper);

private:
    QHash<QString, std::function<FCAbstractOperator*()>>& _createFuns;
    QHash<QString, FCAbstractOperator*> _existOperators{};
};
}

#endif
