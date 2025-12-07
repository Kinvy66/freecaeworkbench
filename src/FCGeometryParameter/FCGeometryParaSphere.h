/**
 * @file FCGeometryParaSphere.h
 * @brief 球体参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPARASPHERE_H
#define FCGEOMETRYPARASPHERE_H
#include "FCGeometryParaAPI.h"
#include "FCGeometryModelParaBase.h"
#include <QDomDocument>

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryParaSphere : public FCGeometryModelParaBase
{
public:
    FCGeometryParaSphere();
    ~FCGeometryParaSphere() = default;
    
    void setName(QString name);
    QString getName();
    
    void setLocation(double *loc);
    void getLocation(double *loc);
    
    bool getRadius(double *r);
    void setRadius(double newRadius);
    
private:
    double mLocation[3];
    double mRadius;
};

} // namespace FC



#endif // FCGEOMETRYPARASPHERE_H
