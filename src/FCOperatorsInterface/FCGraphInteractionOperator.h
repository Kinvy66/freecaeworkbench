/**
 * @file FCGraphInteractionOperator.h
 * @brief 三维拾取操作器接口抽象类
 * @date 2026-01-30
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef FCGRAPHINTERACTIONOPERATOR_H
#define FCGRAPHINTERACTIONOPERATOR_H

#include "FCOperatorsInterfaceAPI.h"
#include "FCAbstractOperator.h"

#include <QColor>

class vtkActor2D;
class vtkActor;
class vtkPlanes;

namespace FC 
{

class FCGraph3DWindowVTK;

class FCOPERATORSINTERFACE_API FCGraphInteractionOperator
    : public FCAbstractOperator
{
    Q_OBJECT
public:
    explicit FCGraphInteractionOperator() = default;
    virtual ~FCGraphInteractionOperator() = default;
    
    
    
    /**
         * @brief   拾取单个节点或单元接口。[虚函数]
         * @param   graphWindow：可视化窗口
         * @param   actor：演员
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-16
         */
    virtual void picked(FCGraph3DWindowVTK* graphWindow, vtkActor2D* actor);
    
    /**
         * @brief   拾取单个节点或单元接口。[虚函数]
         * @param   graphWindow：可视化窗口
         * @param   actor：演员
         * @param   index：索引
         * @param   pickedWorldPos：拾取的世界坐标
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-04-17
         */
    virtual void picked(FCGraph3DWindowVTK* graphWindow, vtkActor* actor, int index, double* pickedWorldPos);
    
    /**
         * @brief   框选拾取多个节点或单元接口。[虚函数]
         * @param   graphWindow：可视化窗口
         * @param   actors：被框选到的演员列表
         * @param   cutPlane：框选时的裁切平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-04-19
         */
    virtual void picked(FCGraph3DWindowVTK* graphWindow, QList<vtkActor*> actors, vtkPlanes* cutPlane);
    
    /**
         * @brief   清除拾取高亮渲染。[虚函数]
         * @param   graphWindow：可视化窗口[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-04-17
         */
    virtual void clear(FCGraph3DWindowVTK* graphWindow = nullptr);
    
    /**
         * @brief   设置拾取颜色。[虚函数]
         * @param   color：颜色
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-23
         */
    virtual void setPickedColor(QColor color);
    
    /**
         * @brief   根据当前拾取对象类型与拾取方法隐藏或显示部分演员，并设置其可拾取状态（特征边、参考点、坐标轴等）。[虚函数]
         * @param   pickObjType：拾取对象类型
         * @param   pickMethod：拾取方法
         * @param   dataObjId：生效数据ID（-1则对所有数据生效）[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-04-30
         */
    virtual void setActorStateByPickInfo(int pickObjType, int pickMethod, int dataObjId = -1);
    
};
} // namespace FC



#endif // FCGRAPHINTERACTIONOPERATOR_H
