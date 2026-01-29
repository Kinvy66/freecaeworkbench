/**
 * @file FCAbstractOperator.cpp
 * @brief 操作器抽象基类声明
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */

#include "FCAbstractOperator.h"

namespace FC
{
FCAbstractOperator::~FCAbstractOperator()
{
}

void FCAbstractOperator::setEmitter(QObject *obj)
{
    mEmitter = obj;
}

void FCAbstractOperator::setArgs(const QString& argName, QVariant arg)
{
    //如果已经存在则直接覆盖
    mOperArgs.insert(argName, arg);
}

void FCAbstractOperator::removeArgs(const QString &argName)
{
    mOperArgs.remove(argName);
}

bool FCAbstractOperator::hasArgs(const QString& argName)
{
    return mOperArgs.contains(argName);
}

void FCAbstractOperator::clearArgs()
{
    //指针类型存放在QVarient中不会被delete
    mOperArgs.clear();
}


}
