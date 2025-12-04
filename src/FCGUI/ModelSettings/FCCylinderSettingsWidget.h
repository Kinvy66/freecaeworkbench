/**
 * @file FCCylinderSettingsWidget.h
 * @brief 圆柱体参数设置页面
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCCYLINDERSETTINGSWIDGET_H
#define FCCYLINDERSETTINGSWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"

namespace Ui {
class FCCylinderSettingsWidget;
}

namespace FC 
{

class FCGeometrySet;

class FCGUI_API FCCylinderSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    explicit FCCylinderSettingsWidget(QWidget *parent = nullptr);
    FCCylinderSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    
    ~FCCylinderSettingsWidget();
    bool create();
        
private:
    bool getRadius(double* p);
    bool getLength(double* p);
    bool getCoordinate(double *coor);
    bool getAxis(double *axis);
    void init();
    
signals:
    void modelCreated(const IdType id, bool r);
    void updateGeoTree(const IdType id, const QString& name);
    void updateGeometryActor(const IdType id);
    
private slots:
    void on_pushButton_build_clicked();
    
private:
    Ui::FCCylinderSettingsWidget *ui;
    bool mIsEdit;
    IdType mEidtSetID;
};
} // namespace FC



#endif // FCCYLINDERSETTINGSWIDGET_H
