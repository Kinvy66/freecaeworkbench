/**
 * @file FCBoxSettingsWidget.h
 * @brief 立方体参数设置窗口
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCBOXSETTINGSWIDGET_H
#define FCBOXSETTINGSWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"


namespace Ui {
class FCBoxSettingsWidget;
}

namespace FC 
{
class FCGeometrySet;
class FCGeometryCreateBox;
class FCGUI_API FCBoxSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCBoxSettingsWidget(QWidget *parent = nullptr);
    FCBoxSettingsWidget(const IdType editSetID, QWidget *parent = nullptr);
    ~FCBoxSettingsWidget();
    bool create();
    
private:
    bool getPara(double* p);
    bool getCoordinate(double *coor);
    void init();
    
signals:
    void modelCreated(FCGeometrySet* set, bool r);
    void updateGeoTree(const IdType id, const QString& name);
    void removeActor(const IdType id);
    
private slots:
    void on_pushButton_build_clicked();
    
    
private:
    Ui::FCBoxSettingsWidget *ui;
    FCGeometryCreateBox* mCreateBox;
    bool mIsEdit;
    
    IdType mEidtSetID;
    
};
} // namespace FC



#endif // FCBOXSETTINGSWIDGET_H
