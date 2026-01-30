/**
 * @file FCTreeEventOperator.h
 * @brief 树形菜单点击事件接口
 * @date 2026-01-30
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef FCTREEEVENTOPERATOR_H
#define FCTREEEVENTOPERATOR_H
#include "FCAbstractOperator.h"
#include "FCOperatorsInterfaceAPI.h"
namespace FC 
{
class  FCOPERATORSINTERFACE_API FCTreeEventOperator : public FCAbstractOperator
{
public:
    explicit FCTreeEventOperator();
    virtual ~FCTreeEventOperator();
    virtual void updateTree();
    
    virtual void moveProcessToStep(int step, void *addInfo = nullptr);
protected:
    /**
         * @brief  主窗口
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-03-27
         */
    // GUI::MainWindow* _mainWindow{};
    
};
} // namespace FC



#endif // FCTREEEVENTOPERATOR_H
