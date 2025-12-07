/**
 * @file FCGeometryCreateCone.h
 * @brief 创建圆锥
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYCREATECONE_H
#define FCGEOMETRYCREATECONE_H
#include "FCGeometryModelCreatorAPI.h"
#include "FCGeometryModelBase.h"

namespace FC 
{
class FCGeometrySet;
class FCGEOMETRYMODELCREATOR_API FCGeometryCreateCone : public FCGeometryModelBase
{
    Q_OBJECT
public:
    FCGeometryCreateCone(QObject* parent=nullptr);
    ~FCGeometryCreateCone() = default;
    
    bool execute() override;
    void undo() override;
    void redo() override;
    void releaseResult() override;
    void setVisible(bool r);
    
    void setName(QString name);
    void setLocation(double* loc);
    void setAxis(double* axis);
    void setBottomRadius(double r);
    void setTopRadius(double r);
    void setHeigth(double h);
    
private:
    QString mName{};
    double mLocation[3];
    double mAxis[3];    
    double mHeigth;
    double mBottomRadius;
    double mTopRadius;
    
    FCGeometrySet* mResult{};
    
    
};
} // namespace FC


#endif // FCGEOMETRYCREATECONE_H
