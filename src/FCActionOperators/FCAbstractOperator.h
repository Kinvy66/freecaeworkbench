/**
 * @file FCAbstractOperator.h
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
#include <QHash>
#include <QVariant>

namespace FC
{
/**
 * @brief 操作器抽象基类
 */
class FCACTIONOPERATORS_API FCAbstractOperator : public QObject
{
    Q_OBJECT
public:
    explicit FCAbstractOperator() = default;
    virtual ~FCAbstractOperator() = 0;
    
    /**
     * @brief 设置触发对象
     * @param[i]  obj            触发对象
     */
    virtual void setEmitter(QObject* obj);
    
    
    void setArgs(const QString& argName, QVariant arg);
    
    /**
     * @brief  移除参数
     * @param[i]  argName        参数名称
     */
    void removeArgs(const QString& argName);
    
    /**
     * @brief 是否包含参数
     * @param[i]  argName      参数名称
     * @return true
     * @return false
     */
    bool hasArgs(const QString& argName);
    
    /**
     * @brief 清空全部参数
     */
    virtual void clearArgs();
    

    /**
     * @brief  获取参数
     * @param[i]  name            参数名称
     * @return T
     */
    template < typename T >
    bool argValue(const QString& name, T& value)
    {
        if (!mOperArgs.contains(name)) return false;
        auto arg = mOperArgs.value(name);
        value = arg.value< T >();
        return true;
    }
    
    
    /**
     * @brief  获取参数，指针类型
     * @param[i]  name            参数名称
     * @return T
     */
    template < typename T >
    T* argValuePtr(const QString& name)
    {
        if (!mOperArgs.contains(name)) return nullptr;
        auto arg = mOperArgs.value(name);
        //先转成基类，防止QVarient直接类型转换需要QObject宏
        QObject* absObj = arg.value<QObject*>(); 
        return dynamic_cast< T* >(absObj);
    }

signals:
    /** 操作器被释放时发出，供仓库移除映射 */
    void operatorDestoryedSig(FCAbstractOperator* oper);
    
    /**
     * @brief 操作器抽象信号
     */
    void operatorAbstractSig();
    void operatorAbstractSig1(FCAbstractOperator* oper);
    void operatorAbstractSig2(FCAbstractOperator* oper, const QVariant& value);
    void operatorAbstractSig3(FCAbstractOperator* oper, void* value);
    
protected:
    /**
     * @brief 参数列表
     */
    QHash<QString, QVariant> mOperArgs{};
    
    /**
     * @brief 触发器
     */
    QObject* mEmitter{};
};
}

#endif
