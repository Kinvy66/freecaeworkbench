/**
 * @file FCSphereSettingsWidget.h
 * @brief 球体参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCSPHERESETTINGSWIDGET_H
#define FCSPHERESETTINGSWIDGET_H
#include <QWidget>
#include "FCGuiAPI.h"

namespace Ui {
class FCSphereSettingsWidget;
}

namespace FC 
{
class FCGeometrySet;
class FCGeometryCreateCone;

class FCGUI_API FCSphereSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCSphereSettingsWidget(QWidget *parent = nullptr);
    FCSphereSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    ~FCSphereSettingsWidget();
    
    bool create();
    
private:
    bool getRadius(double* r);
    bool getCoordinate(double *coor);
    void init();
    
signals:
    void modelCreated(const IdType id, bool r);
    void updateGeoTree(const IdType id, const QString& name);
    void updateGeometryActor(const IdType id);
    
    
private slots:
    void on_pushButton_build_clicked();
    
private:
    Ui::FCSphereSettingsWidget *ui;
    
    bool mIsEdit;
    IdType mEidtSetID;
};

} // namespace FC

#endif // FCSPHERESETTINGSWIDGET_H
