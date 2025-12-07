/**
 * @file FCConeSettingsWidget.h
 * @brief 圆锥参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCCONESETTINGSWIDGET_H
#define FCCONESETTINGSWIDGET_H
#include <QWidget>
#include "FCGuiAPI.h"

namespace Ui {
class FCConeSettingsWidget;
}

namespace FC 
{

class FCGeometrySet;
class FCGeometryCreateCone;

class FCGUI_API FCConeSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCConeSettingsWidget(QWidget *parent = nullptr);
    FCConeSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    ~FCConeSettingsWidget();
    
    bool create();
    
private:
    bool getBottomRadius(double* r);
    bool getTopRadius(double* r);
    bool getHeight(double* h);
    bool getCoordinate(double *coor);
    void init();
    
signals:
    void modelCreated(const IdType id, bool r);
    void updateGeoTree(const IdType id, const QString& name);
    void updateGeometryActor(const IdType id);
    
    
private slots:
    void on_pushButton_build_clicked();
    
private:
    Ui::FCConeSettingsWidget *ui;
    
    bool mIsEdit;
    IdType mEidtSetID;
};
} // namespace FC



#endif // FCCONESETTINGSWIDGET_H
