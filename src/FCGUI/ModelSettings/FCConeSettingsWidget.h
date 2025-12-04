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

namespace Ui {
class FCConeSettingsWidget;
}

class FCConeSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FCConeSettingsWidget(QWidget *parent = nullptr);
    ~FCConeSettingsWidget();

private:
    Ui::FCConeSettingsWidget *ui;
};

#endif // FCCONESETTINGSWIDGET_H
