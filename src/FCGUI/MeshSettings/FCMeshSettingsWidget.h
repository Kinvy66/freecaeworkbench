/**
 * @file FCMeshSettingsWidget.h
 * @brief 网格参数设置页面
 * @date 2025-12-12
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHSETTINGSWIDGET_H
#define FCMESHSETTINGSWIDGET_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCMeshettingsWidget;
}

namespace FC 
{
class FCGmshSettingData;
class FCGraphViewWindow;
class FCGUI_API FCMeshSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCMeshSettingsWidget(QWidget *parent = nullptr);
    FCMeshSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    
    /**
     * @brief 设置图形视图窗口（用于控制几何可见性）
     */
    void setGraphViewWindow(FCGraphViewWindow* viewWindow);
    
    ~FCMeshSettingsWidget();
    

    
    void addMesh();
    
public slots:
    
    void onMeshGenerated(IdType meshID, bool r=true);
    
private:
    void init();
    void saveParameter();
    void updateParameter(FCGmshSettingData* para);
    
signals:
    void updateMeshTree(const IdType id, const QString& name);
    void updateMeshActor(IdType meshID);
    void meshGenerated(IdType meshID, bool r=true);
    
    
private slots:
    void on_pushButtonGenerateMesh_clicked();
    
    void on_pushButtonSavePara_clicked();
    
    void on_checkBoxSelectAll_clicked();
    
    void on_checkBoxSelectVisible_clicked();
    
    void on_pushButtonSelcet_clicked();
    
    void on_checkBoxGeometryVisible_toggled(bool checked);
    
private:
    void initConnections();
    
private:
    Ui::FCMeshettingsWidget *ui;
    bool mIsEdit;
    IdType mEidtSetID;
    FCGraphViewWindow* mGraphViewWindow{nullptr};
};
} // namespace FC



#endif // FCMESHSETTINGSWIDGET_H
