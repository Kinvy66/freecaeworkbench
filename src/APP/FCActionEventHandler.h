/**
 * @file FCActionEventHandler.h
 * @brief action点击事件处理
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef FCACTIONEVENTHANDLER_H
#define FCACTIONEVENTHANDLER_H

#include <QObject>

namespace FC 
{

class FCActionOperator;

class FCActionEventHandler : public QObject
{
public:
    FCActionEventHandler() = default;
    ~FCActionEventHandler() = default;
    
public slots:
    
    /**
      * @brief 执行处理操作
      */
    void execOperator();
    
private:
    
    /**
     * @brief getOperator 获取执行对象
     * @param object 触发的对象
     * @return 
     */
    FCActionOperator* getOperator(QObject* object);
    
    
};
} // namespace FC



#endif // FCACTIONEVENTHANDLER_H
