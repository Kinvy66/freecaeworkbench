/**
 * @file FCTorusSettingsWidget.cpp
 * @brief 环面参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCTorusSettingsWidget.h"
#include "ui_FCTorusSettingsWidget.h"
#include "FCGeometryCreateTorus.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaTorus.h"

namespace FC 
{
FCTorusSettingsWidget::FCTorusSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCTorusSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = false;
    mEidtSetID = 0;
    init();
}

FCTorusSettingsWidget::FCTorusSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCTorusSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
}

FCTorusSettingsWidget::~FCTorusSettingsWidget()
{
    delete ui;
}

bool FCTorusSettingsWidget::create()
{
    double corner[3] = {0.0};
    double majorR, minorR, angle;
    
    bool ok = false;
    ok = getMajorRadius(&majorR);
    ok = getMinorRadius(&minorR);
    ok = getAngle(&angle);
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateTorus* creator = new FCGeometryCreateTorus(this);
    
    connect(creator, &FCGeometryCreateTorus::showSet,
            this, &FCTorusSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateTorus::updateGeoTree,
            this, &FCTorusSettingsWidget::updateGeoTree);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setMajorRadius(majorR);
    creator->setMinorRadius(minorR);
    creator->setAngle(angle);
    
    creator->execute();
    
    return true;
}

bool FCTorusSettingsWidget::getMajorRadius(double *r)
{
    bool ok = false;
    
    QString text = ui->lineEdit_majorRadius->text();
    *r = text.toDouble(&ok);
    if (!ok) return false;
    return true;
}

bool FCTorusSettingsWidget::getMinorRadius(double *r)
{
    bool ok = false;
    
    QString text = ui->lineEdit_minorRadius->text();
    *r = text.toDouble(&ok);
    if (!ok) return false;
    return true;
}

bool FCTorusSettingsWidget::getAngle(double *angle)
{
    bool ok = false;
    
    QString text = ui->lineEdit_angle->text();
    *angle = text.toDouble(&ok);
    if (!ok) return false;
    return true;
    
}

bool FCTorusSettingsWidget::getCoordinate(double *coor)
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

void FCTorusSettingsWidget::init()
{
    if (!mIsEdit) {     // 新建几何模型
        int id = FCGeometrySet::getMaxID() + 1;
        ui->lineEdit_name->setText(QString("Torus_%1").arg(id));
    } else {   // 编辑现有的几何模型
        FCGeometrySet* eidtSet= FCGeometryData::getInstance()->getGeometrySetByID(mEidtSetID);
        if (eidtSet == nullptr){
            return;
        }
        ui->lineEdit_name->setText(eidtSet->getName());
        FCGeometryModelParaBase *pb = eidtSet->getParameter();
        FCGeometryParaTorus *p = dynamic_cast<FCGeometryParaTorus *>(pb);
        
        if (p == nullptr)
            return;
        double loc[3] = {0.0};
        double majorR, minorR, angle;
        p->getLocation(loc);
        p->getMajorRadius(&majorR);
        p->getMinorRadius(&minorR);
        p->getAngle(&angle);
        
        // _pw->setCoordinate(loc);
        ui->lineEdit_locationX->setText(QString::number(loc[0]));
        ui->lineEdit_locationY->setText(QString::number(loc[1]));
        ui->lineEdit_locationZ->setText(QString::number(loc[2]));
        
        ui->lineEdit_majorRadius->setText(QString::number(majorR));
        ui->lineEdit_minorRadius->setText(QString::number(minorR));
        ui->lineEdit_angle->setText(QString::number(angle));
    }
}

void FCTorusSettingsWidget::on_pushButton_build_clicked()
{
    double corner[3] = {0.0};
    double majorR, minorR, angle;
    
    bool ok = false;
    ok = getMajorRadius(&majorR);
    ok = getMinorRadius(&minorR);
    ok = getAngle(&angle);
    ok= getCoordinate(corner);
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateTorus* creator = new FCGeometryCreateTorus(this);
    
    connect(creator, &FCGeometryCreateTorus::showSet,
            this, &FCTorusSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateTorus::updateGeoTree,
            this, &FCTorusSettingsWidget::updateGeoTree);
    
    connect(creator, &FCGeometryCreateTorus::updateDisplayGeometryActor,
            this, &FCTorusSettingsWidget::updateGeometryActor);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setMajorRadius(majorR);
    creator->setMinorRadius(minorR);
    creator->setAngle(angle);
    
    creator->setEditData(mEidtSetID);
    
    creator->execute();
    
}


} // namespace FC
