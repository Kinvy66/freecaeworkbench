/**
 * @file FCParameterList.h
 * @brief 参数列表
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPARAMETERLIST_H
#define FCPARAMETERLIST_H
#include "FCDataAPI.h"
#include "FCParameterBase.h"

class QDataStream;
class QDomDocument;
class QDomElement;


namespace FC 
{

class FCParameterBase;
class FCDataBase;

class FCDATA_API FCParameterList
{
public:
    FCParameterList() = default;
    ~FCParameterList();
    void copy(FCParameterList* data);
    /**
     * @brief 向参数列表追加参数
     * @param para 要追加的参数
     */
    virtual void appendParameter(FCParameterBase* para);
    
    /**
     * @brief 根据类型创建新的参数，并追加到参数列表
     * @param type 要创建参数的类型
     * @return ParameterBase* 创建的参数
     */
    virtual FCParameterBase* appendParameter(ParaType type);
    
    /**
     * @brief 根据索引值获取参数列表中的参数
     * @param i 要获取参数的索引值
     * @return ParameterBase* 返回获取到的参数
     * @attention 索引值越界时会返回nullptr
     */
    FCParameterBase* getParameterAt(const int i);
    
    /**
     * @brief 获取参数列表中参数的数量
     * @return int 返回列表中参数的数量
     */
    int getParameterCount();
    
    /**
     * @brief 获取参数列表中可见参数的数量
     * @return int 返回参数列表中可见参数的数量
     */
    int getVisibleParaCount();
    
    /**
     * @brief 将参数从参数列表中移除
     * @param p 要移除的参数
     */
    virtual void removeParameter(FCParameterBase* p);
    
    /**
     * @brief 将索引值为i的参数从参数列表中移除
     * @param i 要移除的参数的索引
     */
    void removeParameterAt(int i);
    
    /**
     * @brief 获取索引值为i的可见参数
     * @param i 可见参数的索引值
     * @return ParameterBase* 返回获取到的可见参数
     * @attention 索引值i为所有可见参数组成的列表中的索引值，而不是所有参数（包括不可见参数）列表中的索引值，如果索引值越界，则返回nullptr
     */
    FCParameterBase* getVisibleParameterAt(const int i);
    
    /**
     * @brief 根据指定的类型创建参数
     * @param t 要创建参数的类型
     * @return ParameterBase* 创建的参数
     * @attention 如果参数类型为DataProperty::Para_Blank，则返回nullptr
     */
    static FCParameterBase* createParameterByType(ParaType t);
    
    /**
     * @brief 根据指定的类型创建参数
     * @param stype 要创建参数的类型的字符串值
     * @return ParameterBase* 创建的参数
     * @attention 如果参数stype不合法，则返回nullptr
     */
    static FCParameterBase* createParameterByType(QString stype);
    
    /**
     * @brief 根据指定的参数，创建同类型参数，并拷贝其内容
     * @param p 创建参数时要参照的参数
     * @return ParameterBase* 创建的参数
     * @attention 如果p为nullptr，则返回nullptr
     */
    static FCParameterBase* copyParameter(FCParameterBase* p);
    
    /**
     * @brief 将参数对象写入到工程文件
     * @param doc 工程文件的QDomDocument对象
     * @param parent 要追加该参数的父节点
     */
    virtual void writeParameters(QDomDocument* doc, QDomElement* parent);
    
    /**
     * @brief 从工程文件中对应节点读取参数
     * @param ele 工程文件中对应的节点对象
     */
    virtual void readParameters(QDomElement* ele);
    
    /**
     * @brief 根据名称获取参数列表中的参数
     * @param name 要获取参数的名称
     * @return ParameterBase* 获取到的参数
     * @attention 当参数列表中不存在名称为name的参数时返回nullptr
     */
    virtual FCParameterBase* getParameterByName(QString name);
    
    /**
     * @brief 将参数列表转换为二进制流
     * @param datas 转换后的二进制流
     */
    virtual void dataToStream(QDataStream* datas);
    /**
     * @brief 获取参数列表中所有参数的列表
     * @return QList<ParameterBase*> 返回所有参数的列表
     */
    QList<FCParameterBase*> getParaList();
    
    
protected:
    /**
     * @brief 参数的列表
     */
    QList<FCParameterBase*> _paraList{};
    
};
} // namespace FC



#endif // FCPARAMETERLIST_H
