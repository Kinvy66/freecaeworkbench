/**
 * @file FCGeometryModelParaBase.h
 * @brief 几何模型操作参数基类
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYMODELPARABASE_H
#define FCGEOMETRYMODELPARABASE_H
#include <QObject>
#include "FCGeometryParaAPI.h"

namespace FC 
{
class FCGeometryData;

/**
 * @brief 操作参数类型枚举值
 */
enum GeometryParaType
{
    GeometryParaNone = 0,			///< 无意义，用于默认参数
    GeometryParaCreateBox,			///< 创建长方体（包括立方体）的操作参数
    GeometryParaCreateCylinder,		///< 创建圆柱的操作参数
    GeometryParaCreateCone,			///< 创建锥体的操作参数
    GeometryParaCreateFillet,		///< 创建倒圆角的操作参数
    GeometryParaCreateSphere,		///< 创建球体的操作参数
    GeometryParaCreatePoint,		///< 创建点的操作参数
    GeometryParaCreateLine,			///< 创建线段的操作参数
    GeometryParaCreateFace,			///< 创建面的操作参数
    GeometryParaMakeChamfer,		///< 创建倒角的操作参数
    GeometryParaMakeVariableFillet,	///< 创建可变圆角的操作参数
    GeometryParaMakeBoolOperation,	///< 创建布尔运算（操作）的操作参数
    GeometryParaMakeMirrorFeature,	///< 创建镜像特征的操作参数
    GeometryParaMakeRotateFeature,	///< 创建旋转特征的操作参数
    GeometryParaMakeMoveFeature,	///< 创建移动的操作参数
    GeometryParaMakeMatrix,			///< 
    GeometryParaMakeExtrusion,		///< 创建拉伸特征的操作参数
    GeometryParaMakeLoft,			///< 
    GeometryParaMakeSweep,			///< 创建扫略特征的操作参数
    GeometryParaMakeRevol,			///< 创建旋转特征的操作参数
    GeometryParaSplitter,			///< 创建移除曲面的操作参数
    GeometryParaFillHole,			///< 创建填补孔洞的操作参数
    GeometryParaRemoveSurface,		///< 创建移除曲面的操作参数
    GeometryParaFillGap,			///< 
};

class FCGEOMETRYPARA_API FCGeometryModelParaBase : public QObject
{
    Q_OBJECT
public:
    FCGeometryModelParaBase();
    ~FCGeometryModelParaBase() = default;
    
    GeometryParaType getParaType();
    static FCGeometryModelParaBase* createParaByString(QString s);
    
protected:
    /**
     * @brief 将操作类型转换为字符串
     * @return QString 转换后的操作类型字符串
     */
    QString typeToString();
    
protected:
    GeometryParaType mType{GeometryParaNone};
    FCGeometryData* mGeoData{};
};


} // namespace FC


#endif // FCGEOMETRYMODELPARABASE_H
