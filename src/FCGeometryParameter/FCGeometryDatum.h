/**
 * @file FCGeometryDatum.h
 * @brief 基准（参考）形状类
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYDATUM_H
#define FCGEOMETRYDATUM_H

#include "FCGeometrySet.h"


namespace FC 
{

enum DatumType
{
    DatumNone,		///< 无定义，用于默认参数
    DatumPoint,		///< 基准点
    DatumAxis,		///< 基准轴
    DatumPlane,		///< 基准平面
};

class FCGEOMETRYPARA_API FCGeometryDatum : public FCGeometrySet
{
public:
    FCGeometryDatum();
    ~FCGeometryDatum();
    
    /**
     * @brief 设置基准类型
     * @param t 基准类型
     */
    void setDatumType(DatumType t);
    
    /**
     * @brief 获取基准类型
     * @return DatumType 返回基准类型
     */
    DatumType getDatumType();
    
    // todo
    // virtual QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* ele, bool isDisp /* = false */) override;
    // virtual void readDataFromProjectFile(QDomElement* e, bool isDiso /* = false */);
    
    /**
     * @brief 将基准类型转换为字符串
     * @param t 要转换的基准类型
     * @return QString 返回转换后的字符串
     */
    static QString datumTypeToString(DatumType t);
    
    /**
     * @brief 将字符串转换为基准类型
     * @param s 要转换的字符串
     * @return DatumType 返回转换后的基准类型
     * @attention 如果传入的字符串非法，则返回DatumNone
     */
    static DatumType datumTypeFromString(QString s);
    
private:
    DatumType mType{ DatumNone };
};

} // namespace FC


#endif // FCGEOMETRYDATUM_H
