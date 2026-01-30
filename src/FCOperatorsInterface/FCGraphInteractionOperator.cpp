/**
 * @file FCGraphInteractionOperator.cpp
 * @brief 三维拾取操作器接口抽象类
 * @date 2026-01-30
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#include "FCGraphInteractionOperator.h"

namespace FC 
{
void FCGraphInteractionOperator::picked(FCGraph3DWindowVTK* graphWindow, vtkActor2D* actor)
{
    // 根据不同子类重写。
    Q_UNUSED(graphWindow);
    Q_UNUSED(actor);
}

void FCGraphInteractionOperator::picked(FCGraph3DWindowVTK* graphWindow, vtkActor* actor, int index, double* pickedWorldPos)
{
    // 根据不同子类重写。
    Q_UNUSED(graphWindow);
    Q_UNUSED(actor);
    Q_UNUSED(index);
    Q_UNUSED(pickedWorldPos);
}

void FCGraphInteractionOperator::picked(FCGraph3DWindowVTK* graphWindow, QList<vtkActor*> actors, vtkPlanes* cutPlane)
{
    // 根据不同子类重写。
    Q_UNUSED(graphWindow);
    Q_UNUSED(actors);
    Q_UNUSED(cutPlane);
}

void FCGraphInteractionOperator::clear(FCGraph3DWindowVTK* graphWindow)
{
    // 根据不同子类重写。
    Q_UNUSED(graphWindow);
}

void FCGraphInteractionOperator::setPickedColor(QColor color)
{
    // 根据不同子类重写。
    Q_UNUSED(color);
}

void FCGraphInteractionOperator::setActorStateByPickInfo(int pickObjType, int pickMethod, int dataObjId)
{
    // 根据不同子类重写。
    Q_UNUSED(pickObjType);
    Q_UNUSED(pickMethod);
    Q_UNUSED(dataObjId);
}
} // namespace FC
