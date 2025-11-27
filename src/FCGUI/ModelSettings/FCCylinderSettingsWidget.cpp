/**
 * @file FCCylinderSettingsWidget.cpp
 * @brief 圆柱体参数设置页面
 * @date 2025-11-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCCylinderSettingsWidget.h"
#include "ui_FCCylinderSettingsWidget.h"
#include "FCGeometrySet.h"
#include "FCGeometryCreateBoxCylinder.h"

namespace FC 
{
FCCylinderSettingsWidget::FCCylinderSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCCylinderSettingsWidget)
{
    ui->setupUi(this);
}

FCCylinderSettingsWidget::~FCCylinderSettingsWidget()
{
    delete ui;
}

void FCCylinderSettingsWidget::on_pushButton_build_clicked()
{
    double corner[3] = {0.0};
    
    double r = ui->doubleSpinBox_radius->value();
    double l = ui->doubleSpinBox_length->value();
    
    double dir[3] = {0.0};
    if (ui->radioButton_X) {
        dir[0] = 1.0;
    }
    else if (ui->radioButton_Y) {
        dir[1] = 1.0;
    }
    else if (ui->radioButton_Z) {
        dir[2] = 1.0;
    }
    else
    {
        dir[0] = ui->doubleSpinBoxX->value();
        dir[1] = ui->doubleSpinBoxY->value();
        dir[2] = ui->doubleSpinBoxZ->value();
    }
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateBoxCylinder* c = new FCGeometryCreateBoxCylinder(this);
    connect(c, &FCGeometryCreateBoxCylinder::showSet,
            this, &FCCylinderSettingsWidget::modelCreated);
    
    c->setName(name);
    c->setLocation(corner);
    c->setRadius(r);
    c->setLength(l);
    c->setAxis(dir);
    
    c->execute();    
}


} // namespace FC

