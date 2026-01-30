/**
 * @file FCOperatorRepoPrivate.cpp
 * @brief 创建并维护操作器类声明
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#include "FCOperatorRepoPrivate.h"

namespace FC
{
FCOperatorRepoPrivate::FCOperatorRepoPrivate(QHash<QString, std::function<FCAbstractOperator*()>>& funs)
    : _createFuns(funs)
{
}

FCOperatorRepoPrivate::~FCOperatorRepoPrivate()
{
    QList<FCAbstractOperator*> opers = _existOperators.values();
    for (auto oper : opers)
        if (oper != nullptr)
            delete oper;
    _existOperators.clear();
}

FCAbstractOperator* FCOperatorRepoPrivate::getOperator(const QString& key)
{
    if (_existOperators.contains(key))
        return _existOperators.value(key);
    return createOperator(key);
}

void FCOperatorRepoPrivate::removeOperator(const QString& key, bool removeFun)
{
    if (_existOperators.contains(key))
    {
        FCAbstractOperator* oper = _existOperators.value(key);
        _existOperators.remove(key);
        if (oper != nullptr)
            delete oper;
    }
    if (!removeFun)
        return;
    if (_createFuns.contains(key))
        _createFuns.remove(key);
}

void FCOperatorRepoPrivate::registerOperatorFunction(const QString& key,
                                                     std::function<FCAbstractOperator*()> fun)
{
    _createFuns.insert(key, fun);
}

FCAbstractOperator* FCOperatorRepoPrivate::createOperator(const QString& key)
{
    auto fun = _createFuns.value(key);
    if (!fun)
        return nullptr;
    FCAbstractOperator* op = fun();
    if (op == nullptr)
        return nullptr;
    _existOperators.insert(key, op);
    connect(op, &FCAbstractOperator::operatorDestoryedSig,
            this, &FCOperatorRepoPrivate::operatorDestoryedSlot);
    return op;
}

void FCOperatorRepoPrivate::operatorDestoryedSlot(FCAbstractOperator* oper)
{
    const QString name = _existOperators.key(oper);
    if (!_existOperators.contains(name))
        return;
    _existOperators.remove(name);
}
}
