/**
 * @file FCSettingParametersWidget.h
 * @brief 模型参数设置窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCSETTINGPARAMETERSWIDGET_H
#define FCSETTINGPARAMETERSWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"

class QVBoxLayout;

namespace FC 
{
class FCGeometrySet;

class FCGraphicOperateWidget;

class FCGUI_API FCSettingParametersWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCSettingParametersWidget(QWidget* parent = nullptr);
    ~FCSettingParametersWidget();
    
    /**
     * @brief 设置图形操作窗口（用于获取GraphViewWindow）
     */
    void setGraphicOperateWidget(FCGraphicOperateWidget* widget);
    
    void createBox();
    void createCylinder();
    void createCone();
    void createSphere();
    void createTorus();
    
    void addMesh();
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
    
public slots:
    void updateCurrentGeoSettingWidget(const IdType id, const QString& name);
    void updateCurrentMeshSettingWidget(const IdType id, const QString& name);
    void updateCurrentPostProcessingSettingWidget(const IdType id, const QString& name);
    void updateCurrentSettingWidget(const IdType id, const QString& name);
    
    // void onMeshGenerated(IdType meshID, bool r=true);
    
    
private:
    void setCurrentWidget(QWidget* w);
    
signals:
    // void modelCreated(const IdType id, bool r);
    void geometryModelCreated(const IdType id, bool r);
    void updateGeoTree(const IdType id, const QString& name);
    void updateGeometryAcotr(const IdType id);
   
    
    void updateMeshTree(const IdType id, const QString& name);
    void updateMeshAcotr(const IdType meshID);
    void meshGenerated(IdType meshID, bool r=true);
    
private:
    
    QVBoxLayout* mLayout = nullptr;
    QWidget* mCurrentWidget = nullptr;
    FCGraphicOperateWidget* mGraphicOperateWidget = nullptr;
};
} // namespace FC



#endif // FCSETTINGPARAMETERSWIDGET_H
