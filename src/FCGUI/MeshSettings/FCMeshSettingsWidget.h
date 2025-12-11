#ifndef FCMESHSETTINGSWIDGET_H
#define FCMESHSETTINGSWIDGET_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCMeshettingsWidget;
}

namespace FC 
{
class FCGUI_API FCMeshSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCMeshSettingsWidget(QWidget *parent = nullptr);
    FCMeshSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    
    ~FCMeshSettingsWidget();
    

    
    void addMesh();
    
public slots:
    
    void onMeshGenerated(IdType meshID, bool r=true);
    
private:
    void init();
    void saveParameter();
    
signals:
    void updateMeshTree(const IdType id, const QString& name);
    void updateMeshActor(IdType meshID);
    void meshGenerated(IdType meshID, bool r=true);
    
    
private slots:
    void on_pushButtonGenerateMesh_clicked();
    
    void on_pushButtonSavePara_clicked();
    
private:
    Ui::FCMeshettingsWidget *ui;
    bool mIsEdit;
    IdType mEidtSetID;
};
} // namespace FC



#endif // FCMESHSETTINGSWIDGET_H
