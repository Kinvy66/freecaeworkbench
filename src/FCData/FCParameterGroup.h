/**
 * @file FCParameterGroup.h
 * @brief 参数组类
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPARAMETERGROUP_H
#define FCPARAMETERGROUP_H
#include "FCDataAPI.h"
#include "FCParameterList.h"
#include "FCParameterBase.h"
#include <QDataStream>
#include <QString>

namespace FC 
{
class FCParameterBase;
class FCDataBase;


class FCDATA_API FCParameterGroup : public FCParameterList
{
public:
    FCParameterGroup() = default;
    ~FCParameterGroup();
    
    /**
     * @brief 拷贝data中的内容
     * @param data 要拷贝的对象
     */
    void copy(FCParameterGroup* data);
    
    /**
     * @brief 增加参数到参数组
     * @param p 要增加的参数
     */
    void appendParameter(FCParameterBase* p) override;
    
    /**
     * @brief 根据类型创建新的参数，并放入参数组
     * @param type 要创建参数的类型
     * @return ParameterBase* 返回创建的参数
     */
    FCParameterBase* appendParameter(ParaType type) override;
    
    /**
     * @brief 设置参数组的名称
     * @param des 要设置为参数组的名称
     */
    void setDescribe(QString des);
    
    /**
     * @brief 获取参数组的名称
     * @return QString 参数组的名称
     */
    QString getDescribe();
    
    /**
     * @brief 设置参数组是否可见
     * @param v 要设置参数组可见性的布尔值
     */
    void setVisible(bool v);
    
    /**
     * @brief 获取参数组的可见性
     * @return bool 参数组的可见性
     */
    bool isVisible();
    
    /**
     * @brief 拷贝参数组的属性（可见性）
     * @param g 要拷贝属性的源参数组
     */
    void copyStates(FCParameterGroup* g);
    
    /**
     * @brief 将参数对象写入到工程文件
     * @param doc 工程文件的QDomDocument对象
     * @param parent 要追加该参数的父节点
     */
    void writeParameters(QDomDocument* doc, QDomElement* parent) override;
    
    /**
     * @brief 从工程文件中对应节点读取参数
     * @param ele 工程文件中对应的节点对象
     */
    void readParameters(QDomElement* ele) override;
    
    /**
     * @brief 获取参数组的二进制流
     * @param datas 参数组的二进制流
     */
    virtual void dataToStream(QDataStream* datas) override;
    
private:
    
    /**
     * @brief 参数组的名称
     */
    QString _describe{};
    
    /**
     * @brief 参数组的可见性
     */
    bool _visible{ true };
    
};
} // namespace FC

#endif // FCPARAMETERGROUP_H
