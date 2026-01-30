/**
 * @file FCGraphEventOperator.cpp
 * @brief 三维可视对象数据操作器接口类
 * @date 2026-01-30
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#include "FCGraphEventOperator.h"

namespace FC 
{
void FCGraphEventOperator::updateGraph(int dataObjId, bool forceUpdate)
{
    // 根据不同子类重写。
    Q_UNUSED(dataObjId);
    Q_UNUSED(forceUpdate);
}

void FCGraphEventOperator::updateGraphByType(int type, GraphOperParam param)
{
    // 根据不同子类重写。
    Q_UNUSED(type);
    Q_UNUSED(param);
}

// Exchange::FITKFluidVTKGraphObject3D* FCGraphEventOperator::getModelGraphObjectByDataId(int dataObjId)
// {
//     // 根据不同子类重写。
//     Q_UNUSED(dataObjId);
//     return nullptr;
// }

void FCGraphEventOperator::setEnableModelTransparent(bool flag)
{
    // 根据不同子类重写。
    Q_UNUSED(flag);
}

void FCGraphEventOperator::setEnableMeshTransparent(bool flag)
{
    // 根据不同子类重写。
    Q_UNUSED(flag);
}

void FCGraphEventOperator::setModelVisible(int dataObjId, bool visibility)
{
    // 根据不同子类重写。
    Q_UNUSED(dataObjId);
    Q_UNUSED(visibility);
}

void FCGraphEventOperator::setMeshVisible(int dataObjId, bool visibility)
{
    // 根据不同子类重写。
    Q_UNUSED(dataObjId);
    Q_UNUSED(visibility);
}

void FCGraphEventOperator::highlight(int dataObjId, QVariant info, QColor color)
{
    // 根据不同子类重写。
    Q_UNUSED(dataObjId);
    Q_UNUSED(info);
    Q_UNUSED(color);
}

void FCGraphEventOperator::advHighlight(int dataObjId, QVector<int> & indice, QColor color)
{
    // 根据不同子类重写。
    Q_UNUSED(dataObjId);
    Q_UNUSED(indice);
    Q_UNUSED(color);
}

void FCGraphEventOperator::clearHighlight()
{
    // 根据不同子类重写。
}

void FCGraphEventOperator::reRender(bool fitView)
{
    // 根据不同子类重写。
    Q_UNUSED(fitView);
}
} // namespace FC
