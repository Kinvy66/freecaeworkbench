#ifndef FCGRAPHICSVIEWGLOBAL_H
#define FCGRAPHICSVIEWGLOBAL_H

#include <QtCore/QtGlobal>
#include "FCGlobals.h"

#if defined(FCGRAPHICSVIEW_BUILDLIB)
#define FCGRAPHICSVIEW_API Q_DECL_EXPORT
#else
#ifdef Q_CC_MSVC
#define FCGRAPHICSVIEW_API Q_DECL_IMPORT
#else
#define FCGRAPHICSVIEW_API Q_DECL_IMPORT
#endif
#endif

namespace FC 
{
/**
	 * @brief 绘图窗口类别
	 * @since 2.5.0
	 */
enum GraphWindowType
{
    UnDefined = -1, ///< 未定义
    PreWindows = 0, ///< 前处理窗口
    RealTime = 1,	///< 实时曲线窗口
    Post2D = 2,		///< 后处理二维窗口
    Post3D = 3,		///< 后处理三维窗口
};
/**
	 * @brief 选择模式
	 * @since 2.5.0
	 */
enum SelectModel
{
    None = -1,
    GeometryWinBody,
    GeometryWinSurface,
    GeometryWinCurve,
    GeometryWinPoint,
    GeometryBody,
    GeometrySurface,
    GeometryCurve,
    GeometryPoint,
    MeshNode,
    MeshCell,
    BoxMeshNode,
    BoxMeshCell,
    DrawSketch,
};

/**
	 * @brief 草绘类别
	 * @since 2.5.0
	 */
enum SketchType
{
    SketchNone,		///< 无
    SketchLine,		///< 线模
    SketchRect,		///< 矩形
    SketchCircle,	///< 圆
    SketchArc,		///< 弧线
    SketchPolyline, ///< 多段线
    SketchSpline,	///< 样条曲线
};

} // namespace FC



#endif // FCGRAPHICSVIEWGLOBAL_H
