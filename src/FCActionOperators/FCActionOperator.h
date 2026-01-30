/**
 * @file FCActionOperator.h
 * @brief action点击事件处理基类
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef FCACTIONOPERATOR_H
#define FCACTIONOPERATOR_H

#include "FCActionOperatorsAPI.h"
#include "FCAbstractOperator.h"

namespace FC 
{
class  FCACTIONOPERATORS_API FCActionOperator : public FCAbstractOperator
{
    Q_OBJECT
public:
    explicit FCActionOperator() = default;
    virtual ~FCActionOperator();
    
    /**
     * @brief 点击事件处理方法
     * @return true：执行成功， false：执行失败
     */
    virtual bool actionTriggered();
    
    /**
     * @brief 界面逻辑
     * @return true：执行成功， false：执行失败
     */
    virtual bool execGUI();
    
    /**
     * @brief 业务处理逻辑，在execGUI后执行
     * @return true：执行成功， false：执行失败
     */
    virtual bool execProfession();
    
protected:
    
    /**
     * @brief 参数预处理
     */
    virtual void preArgs();
    
};
} // namespace FC



#endif // FCACTIONOPERATOR_H
