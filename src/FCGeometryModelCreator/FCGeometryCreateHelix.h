/**
 * @file FCGeometryCreateHelix.h
 * @brief 创建螺旋
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYCREATEHELIX_H
#define FCGEOMETRYCREATEHELIX_H

#include "FCGeometryModelCreatorAPI.h"
#include "FCGeometryModelBase.h"

namespace FC 
{
class  FCGEOMETRYMODELCREATOR_API FCGeometryCreateHelix : public FCGeometryModelBase
{
    Q_OBJECT
public:
    FCGeometryCreateHelix(QObject* parent=nullptr);
    ~FCGeometryCreateHelix() = default;
    
    bool execute() override;
    void undo() override;
    void redo() override;
    void releaseResult() override;
    
    void setName(QString name);
    void setLocation(double* loc);
    void setNumberOfTurns(int n);
    void setMajorRadius(double r);
    void setMinorRadius(double r);
    void setRadialPitch(double r);
    void setAxialPitch(double r);
    void setChirality(int c);
    
    
private:  
    QString mName{};
    double mLocation[3];
    int mNumberOfTurns;     ///< 匝数
    double mMajorRadius;    ///< 大半径
    double mMinorRadius;    ///< 小半径
    double mRadialPitch;    ///< 径向距
    double mAxialPitch;     ///< 轴向距
    int mChirality;   ///< 旋转方向
    FCGeometrySet* mResult{};
    
};
} // namespace FC



#endif // FCGEOMETRYCREATEHELIX_H
