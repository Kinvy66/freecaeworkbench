/**
 * @file FCParaWidgetInterfaceOperator.h
 * @brief 参数窗口相关的widget
 * @date 2026-01-30
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef FCPARAWIDGETINTERFACEOPERATOR_H
#define FCPARAWIDGETINTERFACEOPERATOR_H

#include "FCAbstractOperator.h"
#include "FCOperatorsInterfaceAPI.h"

namespace FC 
{
class FCOPERATORSINTERFACE_API FCParaWidgetInterfaceOperator : public FCAbstractOperator
{
    Q_OBJECT
public:
    FCParaWidgetInterfaceOperator();
    
    virtual ~FCParaWidgetInterfaceOperator();
    
    virtual void eventProcess(int index, QVariant value = QVariant());
};
} // namespace FC


#endif // FCPARAWIDGETINTERFACEOPERATOR_H
