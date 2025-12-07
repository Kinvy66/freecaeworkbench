/**
 * @file FCTorusSettingsWidget.h
 * @brief 环面参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCTORUSSETTINGSWIDGET_H
#define FCTORUSSETTINGSWIDGET_H
#include <QWidget>
#include "FCGuiAPI.h"
namespace Ui {
class FCTorusSettingsWidget;
}

namespace FC 
{
class FCGUI_API FCTorusSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCTorusSettingsWidget(QWidget *parent = nullptr);
    FCTorusSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    ~FCTorusSettingsWidget();
    
      bool create();
private:
    bool getMajorRadius(double* r);
    bool getMinorRadius(double* r);
    bool getAngle(double* angle) ;
    bool getCoordinate(double *coor);
    void init();
    
signals:
    void modelCreated(const IdType id, bool r);
    void updateGeoTree(const IdType id, const QString& name);
    void updateGeometryActor(const IdType id);
    
    
private slots:
    void on_pushButton_build_clicked();
    
private:
    Ui::FCTorusSettingsWidget *ui;
    
    bool mIsEdit;
    IdType mEidtSetID;
};

} // namespace FC

#endif // FCTORUSSETTINGSWIDGET_H
