/**
 * @file FCGeometryParaCone.h
 * @brief 圆锥参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPARACONE_H
#define FCGEOMETRYPARACONE_H
#include "FCGeometryParaAPI.h"
#include "FCGeometryModelParaBase.h"
#include <QDomDocument>

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryParaCone : public FCGeometryModelParaBase
{
public:
    FCGeometryParaCone();
    ~FCGeometryParaCone() = default;
    
    void setName(QString name);
    QString getName();
    void setLocation(double *loc);
    void getLocation(double *loc);
    void setHeigth(double para);
    bool getHeigth(double *para);
    void setBottomRadius(double para);
    bool getBottomRadius(double *para);
    void setTopRadius(double para);
    bool getTopRadius(double *para);
    
    QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent) override;
    virtual void readDataFromProjectFile(QDomElement *e) override;
    
private:
    
    double mLocation[3];
    double mHeigth;
    double mBottomRadius;
    double mTopRadius;    
};
} // namespace FC



#endif // FCGEOMETRYPARACONE_H
