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

namespace Ui {
class FCTorusSettingsWidget;
}

class FCTorusSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FCTorusSettingsWidget(QWidget *parent = nullptr);
    ~FCTorusSettingsWidget();

private:
    Ui::FCTorusSettingsWidget *ui;
};

#endif // FCTORUSSETTINGSWIDGET_H
