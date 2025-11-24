/**
 * @file FCGeometryCreateBox.h
 * @brief 创建立方体
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYCREATEBOX_H
#define FCGEOMETRYCREATEBOX_H
#include "FCGeometryModelCreatorAPI.h"
#include "FCGeometryModelBase.h"

namespace FC 
{

class FCGeometrySet;

class FCGEOMETRYMODELCREATOR_API FCGeometryCreateBox : public FCGeometryModelBase
{
    Q_OBJECT
public:
    FCGeometryCreateBox(QObject* parent=nullptr);
    ~FCGeometryCreateBox() = default;
    
    void setName(QString name);
    void setLocation(double *loca);
    
    void setGeoPara(double *para);
    
    bool execute() override;
    void undo() override;
    void redo() override;
    void releaseResult() override;
    
    
private:
    /**
		 * @brief 名称
		 * @since 2.5.0
		 */
    QString mName{};
    /**
		 * @brief 位置
		 * @since 2.5.0
		 */
    double mLoaction[3];
    /**
		 * @brief 定形尺寸
		 * @since 2.5.0
		 */
    double mGeoPara[3];
    
    FCGeometrySet *mRes{};
    
};
} // namespace FC


#endif // FCGEOMETRYCREATEBOX_H
