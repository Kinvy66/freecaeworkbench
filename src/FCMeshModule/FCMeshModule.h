/**
 * @file FCMeshModule.h
 * @brief 
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHMODULE_H
#define FCMESHMODULE_H

#include <QObject>
#include "FCMeshModuleAPI.h"

namespace FC 
{
class FCMESHMODULE_API FCMeshModule : public QObject
{
    Q_OBJECT
public:
    static FCMeshModule *getInstance();
    //执行
    void exec();
    //结束
    void finalize();
    
private:
    FCMeshModule(QObject *parent = nullptr);
    ~FCMeshModule() = default;
    
private:
    static FCMeshModule *_instance;
    
};
} // namespace FC



#endif // FCMESHMODULE_H
