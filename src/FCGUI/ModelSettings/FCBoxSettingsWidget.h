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
class FCGUI_API FCBoxSettingsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FCBoxSettingsWidget(QWidget *parent = nullptr);
    ~FCBoxSettingsWidget();
    
private:
    bool getPara(double* p);
    
signals:
    void boxModelCreated(FCGeometrySet* set, bool r);
    
private slots:
    void on_pushButton_build_clicked();
    
    
private:
    Ui::FCBoxSettingsWidget *ui;
    
};
} // namespace FC



#endif // FCBOXSETTINGSWIDGET_H
