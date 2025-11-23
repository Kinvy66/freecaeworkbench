/**
 * @file FCGeometryData.h
 * @brief 几何数据管理基类（单例）
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYDATA_H
#define FCGEOMETRYDATA_H

#include "FCDataBase.h"
#include "FCGeometryParaAPI.h"

class TopoDS_Shape;
class QDomDocument;
class QDomElement;
class QDomNodeList;
class gp_Ax3;
class vtkPolyData;

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryData : public FCDataBase
{
public:
    /**
     * @brief 获取单例指针
     * @return 返回单例指针
     */
    static FCGeometryData* getInstance();
    
private:
    FCGeometryData() = default;
    ~FCGeometryData();
    
private:
    static FCGeometryData* mInstance;
    
    
};
} // namespace FC



#endif // FCGEOMETRYDATA_H
