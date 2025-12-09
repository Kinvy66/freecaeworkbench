/**
 * @file FCParameterDouble.h
 * @brief 双精度浮点类型参数
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPARAMETERDOUBLE_H
#define FCPARAMETERDOUBLE_H
#include "FCDataAPI.h"
#include "FCParameterBase.h"

namespace FC 
{
class FCDATA_API FCParameterDouble : public FCParameterBase
{
public:
    FCParameterDouble();
    ~FCParameterDouble() = default;
    
    /**
		 * @brief 从ori中拷贝内容
		 * @param ori 要拷贝内容的源参数对象
		 * @param valueOnly 是否仅仅拷贝值
		 * @since 2.5.0
		 */
    void copy(FCParameterBase* ori, bool valueOnly = false) override;
    /**
		 * @brief 设置参数的值
		 * @param ok 要设置为参数的值
		 * @since 2.5.0
		 */
    void setValue(double v);
    /**
		 * @brief 获取参数的值
		 * @return bool 参数的值
		 * @since 2.5.0
		 */
    double getValue();
    /**
		 * @brief 设置参数值的有效范围
		 * @param range 要作为有效范围的double类型二元数组
		 * @since 2.5.0
		 */
    void setRange(double* range);
    /**
		 * @brief 获取参数值的有效范围
		 * @param range 参数值的有效范围
		 * @since 2.5.0
		 */
    void getRange(double* range);
    /**
		 * @brief 设置精度（小数点后位数）
		 * @param a 要设置的小数位数
		 * @since 2.5.0
		 */
    void setAccuracy(int a);
    /**
		 * @brief 获取设置精度（小数点后位数）
		 * @return int 参数值的精度
		 * @since 2.5.0
		 */
    int getAccuracy();
    /**
		 * @brief 设置参数的量纲（单位）
		 * @param u 要作为参数量纲的字符串
		 * @since 2.5.0
		 */
    void setUnit(QString u);
    /**
		 * @brief 获取参数的量纲
		 * @return QString 参数的量纲
		 * @since 2.5.0
		 */
    QString getUnit();
    /**
		 * @brief 判断对象是否与参数p值相等
		 * @param p 要比较的参数对象
		 * @return bool 返回参数的比较结果（是否相等）
		 * @since 2.5.0
		 */
    bool isSameValueWith(FCParameterBase* p) override;
    /**
		 * @brief 将参数转换为字符串类型（QString）值
		 * @return QString 转换后得到的字符串值
		 * @since 2.5.0
		 */
    QString valueToString() override;
    /**
		 * @brief 将参数对象写入到工程文件
		 * @param doc 工程文件的QDomDocument对象
		 * @param parent 要追加该参数的父节点
		 * @since 2.5.0
		 */
    // void writeParameter(QDomDocument* doc, QDomElement* parent) override;
    /**
		 * @brief 从工程文件中对应节点读取参数
		 * @param e 工程文件中对应的节点对象
		 * @since 2.5.0
		 */
    // void readParameter(QDomElement* e) override;
    /**
		 * @brief 设置从字符串对象获取参数值（转换）
		 * @param v 要操作的字符串
		 * @attention 如果V是true（忽略大小写）之外的值，都将被转换为false
		 * @since 2.5.0
		 */
    void setValueFromString(QString v) override;
    
private:
    /**
		 * @brief 参数的值
		 * @since 2.5.0
		 */
    double _value{ 0.0 };
    /**
		 * @brief 参数的有效范围
		 * @since 2.5.0
		 */
    double _range[2];
    /**
		 * @brief 参数的精度（小数点后的位数）
		 * @since 2.5.0
		 */
    int _accuracy{ 4 };
    /**
		 * @brief 参数的量纲
		 * @since 2.5.0
		 */
    QString _unit{};
    
    
    
};
} // namespace FC



#endif // FCPARAMETERDOUBLE_H
