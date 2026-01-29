/**
 * @file FCActionEventHandler.cpp
 * @brief action点击事件处理
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#include "FCActionEventHandler.h"
#include "FCActionOperator.h"
#include "FCOperatorRepo.h"

namespace FC 
{

void FCActionEventHandler::execOperator()
{
    QObject* obj = this->sender();
    if (obj == nullptr) return;
    QString objName = obj->objectName();
    
    FCActionOperator* actOper = this->getOperator(obj);
    if (actOper != nullptr) actOper->setEmitter(obj);
    
    if (actOper == nullptr)
    {
        //错误提示
        QString error = QString("%1 Operator create failed !").arg(objName);
        // TODO 
        // AppFrame::FITKMessageError(error);
    }
    else
        actOper->actionTriggered();
}

FCActionOperator *FCActionEventHandler::getOperator(QObject *object)
{
    FCActionOperator* oper = nullptr;
    auto  travelObj = object;
    //递归查找
    while (travelObj != nullptr)
    {
        QString objName = travelObj->objectName();
        //根据名称从仓库查找
        oper = FCOperatorRepo::getInstance()
                   ->getOperatorT<FCActionOperator>(objName);
        
        if (oper != nullptr) return oper;
        
        travelObj = travelObj->parent();
    }
    
    return oper;
}

} // namespace FC
