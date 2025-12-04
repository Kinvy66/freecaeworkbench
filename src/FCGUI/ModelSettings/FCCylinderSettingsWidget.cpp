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
#include "FCGeometryParaCylinder.h"

namespace FC 
{
FCCylinderSettingsWidget::FCCylinderSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCCylinderSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = false;
    mEidtSetID = 0;
    init();
}

FCCylinderSettingsWidget::FCCylinderSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCCylinderSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
}

FCCylinderSettingsWidget::~FCCylinderSettingsWidget()
{
    delete ui;
}

bool FCCylinderSettingsWidget::create()
{
    double corner[3] = {0.0};
    double dir[3] = {0.0};
    double r, l;
    
    bool ok = false;
    ok = getRadius(&r);
    ok = getLength(&l);
    ok = getAxis(dir);
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateCylinder* creator = new FCGeometryCreateCylinder(this);
    
    connect(creator, &FCGeometryCreateCylinder::showSet,
            this, &FCCylinderSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateCylinder::updateGeoTree,
            this, &FCCylinderSettingsWidget::updateGeoTree);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setLength(l);
    creator->setRadius(r);
    creator->setAxis(dir);
    
    creator->execute();
    
    return true;
}

bool FCCylinderSettingsWidget::getRadius(double *p)
{
    bool ok = false;
    
    QString text = ui->doubleSpinBox_radius->text();
    p[0] = text.toDouble(&ok);
    if (!ok) return false;
    return true;
    
}

bool FCCylinderSettingsWidget::getLength(double *p)
{
    bool ok = false;
    
    QString text = ui->doubleSpinBox_length->text();
    p[0] = text.toDouble(&ok);
    if (!ok) return false;
    return true;
    
}

bool FCCylinderSettingsWidget::getCoordinate(double *coor)
{
    bool ok = false;
    
    QString text = ui->lineEdit_locationX->text();
    coor[0] = text.toDouble(&ok);
    if (!ok)
        return false;
    
    text = ui->lineEdit_locationY->text();
    coor[1] = text.toDouble(&ok);
    if (!ok)
        return false;
    
    text = ui->lineEdit_locationZ->text();
    coor[2] = text.toDouble(&ok);
    if (!ok)
        return false;
    
    return true;
}

bool FCCylinderSettingsWidget::getAxis(double *axis)
{
    if (ui->radioButton_X) {
        axis[0] = 1.0;
    }
    else if (ui->radioButton_Y) {
        axis[1] = 1.0;
    }
    else if (ui->radioButton_Z) {
        axis[2] = 1.0;
    }
    else
    {
        axis[0] = ui->doubleSpinBoxX->value();
        axis[1] = ui->doubleSpinBoxY->value();
        axis[2] = ui->doubleSpinBoxZ->value();
    }
    
    return true;
}

void FCCylinderSettingsWidget::init()
{
    if (!mIsEdit) {     // 新建几何模型
        int id = FCGeometrySet::getMaxID() + 1;
        ui->lineEdit_name->setText(QString("Cylinder_%1").arg(id));
    } else {   // 编辑现有的几何模型
        FCGeometrySet* eidtSet= FCGeometryData::getInstance()->getGeometrySetByID(mEidtSetID);
        if (eidtSet == nullptr){
            return;
        }
        ui->lineEdit_name->setText(eidtSet->getName());
        FCGeometryModelParaBase *pb = eidtSet->getParameter();
        FCGeometryParaCylinder *p = dynamic_cast<FCGeometryParaCylinder *>(pb);
        
        if (p == nullptr)
            return;
        double loc[3] = {0.0};
        double r,  l;
        p->getLocation(loc);
        p->getRadius(&r);
        p->getLength(&l);
        // _pw->setCoordinate(loc);
        ui->lineEdit_locationX->setText(QString::number(loc[0]));
        ui->lineEdit_locationY->setText(QString::number(loc[1]));
        ui->lineEdit_locationZ->setText(QString::number(loc[2]));
        
        ui->doubleSpinBox_length->setValue(l);
        ui->doubleSpinBox_radius->setValue(r);
        // todo: set axis
    }
}

void FCCylinderSettingsWidget::on_pushButton_build_clicked()
{
    double corner[3] = {0.0};
    double dir[3] = {0.0};
    double r, l;
    
    bool ok = false;
    ok = getRadius(&r);
    ok = getLength(&l);
    ok = getAxis(dir);
    ok = getCoordinate(corner);
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateCylinder* creator = new FCGeometryCreateCylinder(this);
    
    connect(creator, &FCGeometryCreateCylinder::showSet,
            this, &FCCylinderSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateCylinder::updateGeoTree,
            this, &FCCylinderSettingsWidget::updateGeoTree);
    connect(creator, &FCGeometryCreateCylinder::updateDisplayGeometryActor,
            this, &FCCylinderSettingsWidget::updateGeometryActor);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setLength(l);
    creator->setRadius(r);
    creator->setAxis(dir);
    
    creator->setEditData(mEidtSetID);
    
    creator->execute();
}


} // namespace FC

