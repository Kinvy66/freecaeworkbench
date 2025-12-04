/**
 * @file FCGeometryCreateCylinder.h
 * @brief 创建圆柱体
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYCREATEBOXCYLINDER_H
#define FCGEOMETRYCREATEBOXCYLINDER_H

#include "FCGeometryModelCreatorAPI.h"
#include "FCGeometryModelBase.h"

namespace FC 
{
class FCGeometrySet;

class FCGEOMETRYMODELCREATOR_API FCGeometryCreateCylinder : public FCGeometryModelBase
{
    Q_OBJECT
public:
    FCGeometryCreateCylinder(QObject* parent=nullptr);
    ~FCGeometryCreateCylinder() = default;
    
    
    bool execute() override;
    void undo() override;
    void redo() override;
    void releaseResult() override;
    
    void setName(QString name);
    void setLocation(double* loc);
    void setAxis(double* axis);
    void setRadius(double r);
    void setLength(double l);
    
private:
    QString mName{};
    double mLocation[3];
    double mAxis[3];
    double mRadius{ 0.0 };
    double mLength{ 0.0 };
    
    FCGeometrySet* mResult{};
    
};
} // namespace FC


#endif // FCGEOMETRYCREATEBOXCYLINDER_H
