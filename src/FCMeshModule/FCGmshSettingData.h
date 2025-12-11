/**
 * @file FCGmshSettingData.h
 * @brief 网格参数
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGMSHSETTINGDATA_H
#define FCGMSHSETTINGDATA_H
#include "FCMeshModuleAPI.h"
#include <QList>
#include <QMultiHash>
#include <QString>
#include "FCDataBase.h"

namespace FC 
{
class FCMESHMODULE_API FCGmshSettingData : public FCDataBase
{
public:
    FCGmshSettingData();
    ~FCGmshSettingData();
    void copy(FCDataBase* data) override;
    
    //设置实体Hash
    void setSolidHash(QMultiHash<int, int> sh);
    //获取实体Hash
    QMultiHash<int, int> getSolidHash();
    //设置面剖分Hash
    void setSurfaceHash(QMultiHash<int, int> sh);
    //获取面剖分Hash
    QMultiHash<int, int> getSurfaceHash();
    //设置剖分类型
    void setElementType(QString type);
    //获取剖分类型
    QString getElementType();
    //设置剖分阶次
    void setElementOrder(int order);
    //获取剖分阶次
    int getElementOrder();
    //设置剖分方法
    void setMethod(int m);
    //获取剖分方法
    int getMethod();
    //设置尺寸因子
    void setSizeFactor(double sf);
    //获取尺寸因子
    double getSizeFactor();
    //设置最小尺寸
    void setMinSize(double min);
    //获取最小尺寸
    double getMinSize();
    //设置最大尺寸
    void setMaxSize(double max);
    //获取最大尺寸
    double getMaxSize();
    //设置网格清理
    void setGeoClean(bool c);
    //获取网格清理
    bool getGeoClean();
    //设置光滑度
    void setSmoothIteration(int smooth);
    //获取光滑度
    int getSmoothIteration();
    //设置网格连贯性
    void setGridCoplanar(bool gc);
    //获取网格连贯性 
    bool getGridCoplanar();
    //设置局部密度
    void setSizeAtPoints(QString ps);
    void setSizeFields(QString fs);
    // void setLocalDesities(QList<LocalDensity*> list);
    //获取局部密度
    // QList<LocalDensity*> getLocalDesities();
    //设置全选状态
    void setSelectAll(bool b);
    //获取全选状态
    bool getSelectAll();
    //设置选择可见项状态
    void setSelectVisiable(bool b);
    //获取选择可见项状态
    bool getSelectVisiable();
    //设置网格编号
    void setMeshID(int id);
    //获取网格编号
    int getMeshID();
    //设置指定单元类型
    void setCells(QList<int> cells);
    //获取指定单元类型
    QList<int> getCells();
    void setDimension(int dim);
    int getDimension();
    
private:
    void appendBoxField(QStringList list);
    void appendBallField(QStringList list);
    void appendCylinderField(QStringList list);
    void appendSolidsField(QStringList list);
    void appendFrustumField(QStringList list);
    
private:
    int mMeshID{ -1 };
    QMultiHash<int, int> mSolidHash{};
    QMultiHash<int, int> mSurfaceHash{};
    int mDimension{2};
    QString mElementType{};
    int mElementOrder{ -1 };
    int mMethod{ -1 };
    double mSizeFactor{ 0.0 };
    double mMinSize{ 0.0 };
    double mMaxSize{ 0.0 };
    bool mGeoclean{ false };
    int mSmoothIteration{ 0 };
    bool mGridCoplanar{ false };
    bool mSelectall{ true };
    bool mSelectvisible{ false };
    
    // QList<LocalDensity*> _locals{};
    QList<int> mCells{};
    
};
} // namespace FC



#endif // FCGMSHSETTINGDATA_H
