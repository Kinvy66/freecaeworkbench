/**
 * @file FCHelixSettingsWidget.h
 * @brief 螺旋参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCHELIXSETTINGSWIDGET_H
#define FCHELIXSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class FCHelixSettingsWidget;
}

class FCHelixSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FCHelixSettingsWidget(QWidget *parent = nullptr);
    ~FCHelixSettingsWidget();

private:
    Ui::FCHelixSettingsWidget *ui;
};

#endif // FCHELIXSETTINGSWIDGET_H
