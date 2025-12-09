/**
 * @file FCElementType.h
 * @brief 
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCELEMENTTYPE_H
#define FCELEMENTTYPE_H

#include <QString>
#include <vtkCellType.h>
#include "FCMeshModuleAPI.h"

namespace FC 
{
    QString FCMESHMODULE_API vtkCellTYpeToString(VTKCellType type);
    VTKCellType FCMESHMODULE_API  TypeStringToVTKCellType(QString stype);
    int FCMESHMODULE_API GetNodeCountByElementType(VTKCellType t);
} // namespace FC

#endif // FCELEMENTTYPE_H
