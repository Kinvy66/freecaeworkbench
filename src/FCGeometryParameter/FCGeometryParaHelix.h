/**
 * @file FCGeometryParaHelix.h
 * @brief 螺旋参数
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPARAHELIX_H
#define FCGEOMETRYPARAHELIX_H
#include "FCGeometryParaAPI.h"
#include "FCGeometryModelParaBase.h"
#include <QDomComment>

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryParaHelix : public FCGeometryModelParaBase
{
public:
    enum Chirality
    {
        RightHanded = 1,
        LeftHanded = -1
    };
public:
    FCGeometryParaHelix();
    ~FCGeometryParaHelix() = default;
    
    void setName(QString name);
    QString getName();
    
    void setLocation(double* loc);
    void getLocation(double* loc);
    
    int numberOfTurns() const;
    void setNumberOfTurns(int newNumberOfturns);
    
    double majorRadius() const;
    void setMajorRadius(double newMajorRadius);
    
    double minorRadius() const;
    void setMinorRadius(double newMinorRadius);
    
    double radialPitch() const;
    void setRadialPitch(double newRadialPitch);
    
    double axialPitch() const;
    void setAxialPitch(double newAxialPitch);
    
    Chirality chirality() const;
    void setChirality(Chirality newChirality);
    
private:
    // QString mName{};
    double mLocation[3];
    int mNumberOfTurns;     ///< 匝数
    double mMajorRadius;    ///< 大半径
    double mMinorRadius;    ///< 小半径
    double mRadialPitch;    ///< 径向距
    double mAxialPitch;     ///< 轴向距
    Chirality mChirality;   ///< 旋转方向
};
} // namespace FC



#endif // FCGEOMETRYPARAHELIX_H
