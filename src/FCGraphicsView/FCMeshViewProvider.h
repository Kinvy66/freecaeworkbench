/**
 * @file FCMeshViewProvider.h
 * @brief 网格可视化管理器
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHVIEWPROVIDER_H
#define FCMESHVIEWPROVIDER_H
#include "FCGraphicsViewGlobal.h"
#include <QObject>
#include <QHash>
#include <QMultiHash>

class vtkActor;
class vtkDataSet;

namespace FC 
{
class FCGRAPHICSVIEW_API FCMeshViewProvider : public QObject
{
    Q_OBJECT
public:
    explicit FCMeshViewProvider(QObject *parent = nullptr);
    
signals:
};
} // namespace FC



#endif // FCMESHVIEWPROVIDER_H
