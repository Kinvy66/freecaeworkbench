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
    FCMeshModule(QObject *parent = nullptr);
    
signals:
};
} // namespace FC



#endif // FCMESHMODULE_H
