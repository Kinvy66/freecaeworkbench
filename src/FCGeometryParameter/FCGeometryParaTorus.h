/**
 * @file FCGeometryParaTorus.h
 * @brief 环面参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPARATORUS_H
#define FCGEOMETRYPARATORUS_H
#include "FCGeometryParaAPI.h"
#include "FCGeometryModelParaBase.h"
#include <QDomDocument>

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryParaTorus : public FCGeometryModelParaBase
{
public:
    FCGeometryParaTorus();
    ~FCGeometryParaTorus() = default;
    void setName(QString name);
    QString getName();
    void setLocation(double *loc);
    void getLocation(double *loc);
    
    double majorRadius() const;
    void setMajorRadius(double newMajorRadius);
    
    double minorRadius() const;
    void setMinorRadius(double newMinorRadius);
    
private:
    double mLocation[3];
    double mMajorRadius;    ///< 大半径
    double mMinorRadius;    ///< 小半径
    
};
} // namespace FC



#endif // FCGEOMETRYPARATORUS_H
