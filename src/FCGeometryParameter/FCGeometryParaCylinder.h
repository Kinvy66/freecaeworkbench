/**
 * @file FCGeometryParaCylinder.h
 * @brief 圆柱体参数
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPARACYLINDER_H
#define FCGEOMETRYPARACYLINDER_H

#include "FCGeometryParaAPI.h"
#include "FCGeometryModelParaBase.h"

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryParaCylinder : public FCGeometryModelParaBase
{
public:
    FCGeometryParaCylinder();
    ~FCGeometryParaCylinder() = default;
    
    void setName(QString name);
    QString getName();
    
    void setLocation(double* loc);
    void getLocation(double* loc);
    
    void setRadius(double* r);
    void getRadius(double* r);
    
    void setLength(double* l);
    void getLength(double* l);
    
    void setDirection(double* dir);
    void getDirection(double* dir);
    ///数据写入工程文件
    // QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* parent) override;
    ///从工程文件读入数据
    // virtual void readDataFromProjectFile(QDomElement* e) override;
    
private:
    // QString mName{};
    double mLocation[3];
    double mRadius;
    double mLength;
    double mDirection[3];
    
};
} // namespace FC


#endif // FCGEOMETRYPARACYLINDER_H
