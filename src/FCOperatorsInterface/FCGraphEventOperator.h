/**
 * @file FCGraphEventOperator.h
 * @brief 三维可视对象数据操作器接口类
 * @date 2026-01-30
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef FCGRAPHEVENTOPERATOR_H
#define FCGRAPHEVENTOPERATOR_H

#include "FCAbstractOperator.h"
#include "FCOperatorsInterfaceAPI.h"

#include <QColor>
#include <QVariant>

namespace FC 
{

enum HighlightLevel
{
    // 取消高亮。
    DisHighlight = 0,
    
    // 高亮。
    Highlight,
    
    // 高级高亮
    AdvHighlight
};

/**
 * @brief   可视化对象操作执行参数结构体。
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-07-26
 */
struct GraphOperParam
{
    // 操作的数据ID。（不存在则传入-1）
    int DataId = -1;
    
    // 隐藏与显示。
    bool Visibility = true;
    
    // 强制刷新。
    bool ForceUpdate = false;
    
    // 高亮级别。
    HighlightLevel HighlightMode = DisHighlight;
    
    // 高级高亮索引或ID列表。（高级高亮等功能使用）
    QVector<int> AdvHighlightIndice;
    
    // 高亮颜色。（缺省）
    QColor HighlightColor;
};

class FCOPERATORSINTERFACE_API FCGraphEventOperator : public FCAbstractOperator
{
    Q_OBJECT
public:
    explicit FCGraphEventOperator() = default;
    virtual ~FCGraphEventOperator() = default;
    
    // 前处理渲染与窗口功能。
    //@{
    /**
         * @brief   根据提供的数据对象ID更新对应可视化对象。（没有则创建）[虚函数]
         * @param   dataObjId：数据对象ID
         * @param   forceUpdate：是否强制刷新[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-06-12
         */
    virtual void updateGraph(int dataObjId, bool forceUpdate = false);
    
    /**
         * @brief   根据提供的数据类型创建可视化对象并执行相关逻辑。（没有则创建）[虚函数]
         *          （此接口用于非数据类可视化对象预览。）
         * @param   type：数据类型
         * @param   param：可视化对象执行操作参数（默认只进行可视化）[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-26
         */
    virtual void updateGraphByType(int type, GraphOperParam param = GraphOperParam());
    
    /**
         * @brief   根据数据对象ID获取模型可视化对象。（没有则不创建）[虚函数]
         * @param   dataObjId：数据对象ID
         * @return  可视化对象
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-23
         */
    // virtual Exchange::FITKFluidVTKGraphObject3D* getModelGraphObjectByDataId(int dataObjId);
    
    /**
         * @brief   将现有模型全部开启或关闭半透明显示。[虚函数]
         * @param   flag：是否开启
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
    virtual void setEnableModelTransparent(bool flag);
    
    /**
         * @brief   将现有（边界）网格全部开启或关闭半透明显示。[虚函数]
         * @param   flag：是否开启
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-02
         */
    virtual void setEnableMeshTransparent(bool flag);
    
    /**
         * @brief   隐藏或显示模型。[虚函数]
         * @param   dataObjId：数据对象ID
         * @param   visibility：是否可见
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-02
         */
    virtual void setModelVisible(int dataObjId, bool visibility);
    
    /**
         * @brief   隐藏或显示（边界）网格。[虚函数]
         * @param   dataObjId：数据对象ID
         * @param   visibility：是否可见
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-02
         */
    virtual void setMeshVisible(int dataObjId, bool visibility);
    //@}
    
    // 高亮功能接口。
    //@{
    /**
         * @brief   高亮可视化对象。[虚函数]
         * @param   dataObjId：数据对象ID
         * @param   info：附加信息[缺省]
         * @param   color：高亮颜色[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
    virtual void highlight(int dataObjId, QVariant info = QVariant(), QColor color = QColor());
    
    /**
         * @brief   根据附加信息高级高亮指定的数据。[虚函数]
         * @param   dataObjId：数据对象ID
         * @param   indice：附加信息（索引或数据ID）[引用]
         * @param   color：高亮颜色[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
    virtual void advHighlight(int dataObjId, QVector<int> & indice, QColor color = QColor());
    
    /**
         * @brief   取消全部高亮、高级高亮数据的高亮效果。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
    virtual void clearHighlight();
    //@}
    
    // 渲染专用接口。
    //@{
    /**
         * @brief   刷新渲染窗口。[虚函数]
         * @param   fitView：是否重置相机
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-24
         */
    virtual void reRender(bool fitView = false);
    //@}
    
    // 工具方法。
    //@{
    
    //@}
    
};
} // namespace FC


#endif // FCGRAPHEVENTOPERATOR_H
