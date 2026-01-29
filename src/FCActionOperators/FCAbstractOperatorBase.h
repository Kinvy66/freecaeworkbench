/**
 * @file FCAbstractOperatorBase.h
 * @brief 操作器抽象基类声明
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef _FC_ABSTRACT_OPERATOR_BASE_H__
#define _FC_ABSTRACT_OPERATOR_BASE_H__

#include "FCActionOperatorsAPI.h"
#include <QObject>

namespace FC
{
/**
 * @brief 操作器抽象基类
 */
class FCACTIONOPERATORS_API FCAbstractOperatorBase : public QObject
{
    Q_OBJECT
public:
    explicit FCAbstractOperatorBase() = default;
    virtual ~FCAbstractOperatorBase() = 0;

signals:
    /** 操作器被释放时发出，供仓库移除映射 */
    void operatorDestoryedSig(FCAbstractOperatorBase* oper);
};
}

#endif
