/**
 * @file FCParameterBase.h
 * @brief 参数基类
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPARAMETERBASE_H
#define FCPARAMETERBASE_H
#include "FCDataAPI.h"
#include <QString>
#include <QObject>
#include <QList>

class QDomDocument;
class QDomElement;

namespace FC 
{

class FCParameterObserver;

/**
 * @brief 参数类型枚举值
 * @note 未定义类型（Para_Blank）一般用于初始化，说明未指定参数类型
 */
enum  ParaType
{
    Para_Blank = 0, ///< 未定义类型
    Para_Int, ///< 整型参数
    Para_Double, ///< 双精度浮点型参数
    Para_Color, ///< 颜色类型参数（=QColor）
    Para_String, ///< 字符串参数
    Para_Bool, ///< 布尔类型参数
    Para_Selectable, ///< 枚举类型参数
    Para_Path, ///< 路径类型参数
    Para_Table, ///< 表格类型参数
};

class FCDATA_API FCParameterBase : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param t 参数类型
     */
    FCParameterBase(ParaType t);
    
    /**
     * @brief 构造函数
     */
    FCParameterBase() = default;
    
    /**
     * @brief 析构函数
     */
    ~FCParameterBase() = default;
    
    /**
     * @brief 从ori中拷贝内容
     * @param ori 要拷贝内容的源参数对象
     * @param valueOnly 是否仅仅拷贝值
     */
    virtual void copy(FCParameterBase* ori, bool valueOnly = false);
    
    /**
     * @brief 获取参数类型
     * @return ParaType 参数的类型
     */
    ParaType getParaType();
    
    /**
     * @brief 设置参数的类型
     * @param type 参数的类型
     */
    void setParaType(ParaType type);
    
    /**
     * @brief 获取参数的名称
     * @return QString 参数的名称
     */
    QString getDescribe();
    
    /**
     * @brief 设置参数的名称
     * @param s 参数的名称
     */
    void setDescribe(QString s);
    
    /**
     * @brief 设置参数是否可见
     * @param v 参数是否可见的布尔值
     */
    void setVisible(bool v);
    
    /**
     * @brief 获取参数是否可见
     * @return bool 参数是否可见的布尔值
     */
    bool isVisible();
    
    /**
     * @brief 设置参数是否可以被编辑
     * @param e 参数是否可以被编辑的布尔值
     */
    void setEditable(bool e);
    
    /**
     * @brief 获取参数是否可以被编辑
     * @return bool 参数是否可以被编辑的布尔值
     */
    bool isEditable();
    
    /**
     * @brief 设置参数的中文名称，与setDescribe()对应
     * @param chinese 参数的中文名称
     */
    void setChinese(QString chinese);
    
    /**
     * @brief 获取参数的中文名称
     * @return QString 参数的中文名称
     */
    QString getChinese();
    
    /**
     * @brief 将参数转换为字符串类型（QString）值
     * @return QString 转换后得到的字符串值
     */
    virtual QString valueToString();
    
    /**
     * @brief 设置从字符串对象获取参数值（转换）
     * @param v 要操作的字符串
     * @note 函数定义请参考子类的重载函数
     */
    virtual void setValueFromString(QString v);
    
    /**
     * @brief 设置参数的模块类型
     * @param t 参数的模块类型
     */
    // void setModuleType(ModuleType t);
    
    /**
     * @brief 获取参数的模块类型
     * @return ModuleType 参数的模块类型
     */
    // ModuleType getModuleType();
    
    //获取数据ID(DataBase)
    int getDataID();
    //设置数据ID
    void setDataID(int id);
    //获取数据索引
    int getDataIndex();
    //设置数据索引
    void setDataIndex(int index);
    
    /**
     * @brief 获取参数的组名
     * @return QString 
     */
    QString getGroupName();
    
    /**
     * @brief 设置参数所在的组
     * @param group 要设置的组名
     */
    void setGroupName(QString group);
    
    /**
     * @brief 以<groupName>/<paraName>的格式返回名称
     * @return QString 参数的名称
     * @note 如果groupName为空，则返回<paraName>
     */
    QString genAbsoluteName();
    
    /**
     * @brief 追加观察者到观察者列表
     * @param obs 要追加的观察者对象
     */
    void appendObserver(FCParameterObserver* obs);
    
    /**
     * @brief 获取观察者列表
     * @return QList<FCParameterObserver*> 观察者列表
     */
    QList<FCParameterObserver*> getObserverList();
    
    /**
     * @brief 判断对象是否与参数p值相等
     * @param p 要比较的参数对象
     * @return bool 
     */
    virtual bool isSameValueWith(FCParameterBase* p);
    
    /**
     * @brief 拷贝参数的状态（是否可见、可编辑）
     * @param p 要拷贝状态的源参数对象
     */
    virtual void copyStatus(FCParameterBase* p);
    
    /**
     * @brief 将参数对象写入到工程文件
     * @param doc 工程文件的QDomDocument对象
     * @param parent 要追加该参数的父节点
     */
    virtual void writeParameter(QDomDocument* doc, QDomElement* parent);
    
    /**
     * @brief 从工程文件中对应节点读取参数
     * @param e 工程文件中对应的节点对象
     */
    virtual void readParameter(QDomElement* e);
    
    /**
     * @brief 参数类型转换为字符串
     * @param t 参数类型
     * @return QString 返回转换后的字符串
     * @attention 未定义类型（Para_Blank）会返回空字符串
     */
    static QString ParaTypeToString(ParaType t);
    
    /**
     * @brief 字符串转换为参数类型
     * @param stype 要转换的字符串
     * @return ParaType 参数类型
     * @attention 字符串不合法时返回未定义类型（Para_Blank）
     */
    static ParaType StringToParaType(QString stype);
    
signals:
    /**
     * @brief 当参数值发生变化时，触发该信号
     */
    void dataChanged();
    
    
protected:
    /**
     * @brief 参数类型
     */
    ParaType mType{ Para_Blank };
    
    /**
     * @brief 参数名称
     */
    QString mDescribe{};
    
    /**
     * @brief 参数中文名称
     */
    QString mChinese{};
    
    /**
     * @brief 参数是否可编辑
     */
    bool mEditable{ true };
    
    /**
     * @brief 参数是否可见
     */
    bool mVisible{ true };
    
    /**
     * @brief 观察者列表（参见观察者模式）
     */
    QList<FCParameterObserver*> mObserverList{};
    
    //****与参数隶属的模块相关信息,与DataBase相同********
    // ModuleType _moduleType{ Module_None };
    int _dataID{ -1 };
    int _dataIndex{ -1 };
    QString _groupName{};
    //**************************************************
};
} // namespace FC



#endif // FCPARAMETERBASE_H
