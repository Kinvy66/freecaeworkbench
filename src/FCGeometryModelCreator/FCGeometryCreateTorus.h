/**
 * @file FCGeometryCreateTorus.h
 * @brief 创建环面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYCREATETORUS_H
#define FCGEOMETRYCREATETORUS_H
#include "FCGeometryModelCreatorAPI.h"
#include "FCGeometryModelBase.h"

namespace FC 
{
class FCGeometrySet;
class FCGEOMETRYMODELCREATOR_API FCGeometryCreateTorus : public FCGeometryModelBase
{
    Q_OBJECT
public:
    FCGeometryCreateTorus(QObject* parent=nullptr);
    ~FCGeometryCreateTorus() = default;
    
    bool execute() override;
    void undo() override;
    void redo() override;
    void releaseResult() override;
    void setVisible(bool r);
    
    void setName(QString name);
    void setLocation(double *loca);
    void setMajorRadius(double r);
    void setMinorRadius(double r);
    void setAngle(double angle);
    
    
private:
    QString mName{};    
    double mLocation[3];
    double mMajorRadius;    ///< 大半径
    double mMinorRadius;    ///< 小半径
    double mAngle;          ///< 旋转角度
    FCGeometrySet* mResult{};
    
};
} // namespace FC


#endif // FCGEOMETRYCREATETORUS_H
