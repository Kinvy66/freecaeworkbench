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

namespace Ui {
class FCSphereSettingsWidget;
}

class FCSphereSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FCSphereSettingsWidget(QWidget *parent = nullptr);
    ~FCSphereSettingsWidget();

private:
    Ui::FCSphereSettingsWidget *ui;
};

#endif // FCSPHERESETTINGSWIDGET_H
