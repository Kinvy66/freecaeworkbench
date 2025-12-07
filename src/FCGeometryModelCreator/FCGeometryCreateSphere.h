/**
 * @file FCGeometryCreateSphere.h
 * @brief 创建球体
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYCREATESPHERE_H
#define FCGEOMETRYCREATESPHERE_H
#include "FCGeometryModelCreatorAPI.h"
#include "FCGeometryModelBase.h"

namespace FC 
{
class FCGeometrySet;
class FCGEOMETRYMODELCREATOR_API FCGeometryCreateSphere : public FCGeometryModelBase
{
    Q_OBJECT
public:
    FCGeometryCreateSphere(QObject* parent=nullptr);
    ~FCGeometryCreateSphere() = default;
    
    bool execute() override;
    void undo() override;
    void redo() override;
    void releaseResult() override;
    
    void setName(QString name);
    void setLocation(double* loc);
    void setRadius(double r);
    
private:
    QString mName{};    
    double mLocation[3];
    double mRadius;
    FCGeometrySet* mResult{};
};

} // namespace FC


#endif // FCGEOMETRYCREATESPHERE_H
