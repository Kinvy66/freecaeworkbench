/**
 * @file FCConeSettingsWidget.cpp
 * @brief 圆锥参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCConeSettingsWidget.h"
#include "ui_FCConeSettingsWidget.h"
#include "FCGeometryCreateCone.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaCone.h"

namespace FC 
{

FCConeSettingsWidget::FCConeSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCConeSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = false;
    mEidtSetID = 0;
    init();
}

FCConeSettingsWidget::FCConeSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCConeSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
}

FCConeSettingsWidget::~FCConeSettingsWidget()
{
    delete ui;
}

bool FCConeSettingsWidget::create()
{
    double corner[3] = {0.0};
    double bottomR, topR, heigth;
    
    bool ok = false;
    ok = getBottomRadius(&bottomR);
    ok = getTopRadius(&topR);
    ok = getHeight(&heigth);
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateCone* creator = new FCGeometryCreateCone(this);
    
    connect(creator, &FCGeometryCreateCone::showSet,
            this, &FCConeSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateCone::updateGeoTree,
            this, &FCConeSettingsWidget::updateGeoTree);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setBottomRadius(bottomR);
    creator->setTopRadius(topR);
    creator->setHeigth(heigth);
    
    creator->execute();
    
    return true;
}

bool FCConeSettingsWidget::getBottomRadius(double *r)
{
    bool ok = false;
    
    QString text = ui->lineEdit_bottomR->text();
    *r = text.toDouble(&ok);
    if (!ok) return false;
    return true;
}

bool FCConeSettingsWidget::getTopRadius(double *r)
{
    bool ok = false;
    
    QString text = ui->lineEdit_topR->text();
    *r = text.toDouble(&ok);
    if (!ok) return false;
    return true;
}

bool FCConeSettingsWidget::getHeight(double *h)
{
    bool ok = false;
    
    QString text = ui->lineEdit_height->text();
    *h = text.toDouble(&ok);
    if (!ok) return false;
    return true;
}

bool FCConeSettingsWidget::getCoordinate(double *coor)
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

void FCConeSettingsWidget::init()
{
    if (!mIsEdit) {     // 新建几何模型
        int id = FCGeometrySet::getMaxID() + 1;
        ui->lineEdit_name->setText(QString("Cone_%1").arg(id));
    } else {   // 编辑现有的几何模型
        FCGeometrySet* eidtSet= FCGeometryData::getInstance()->getGeometrySetByID(mEidtSetID);
        if (eidtSet == nullptr){
            return;
        }
        ui->lineEdit_name->setText(eidtSet->getName());
        FCGeometryModelParaBase *pb = eidtSet->getParameter();
        FCGeometryParaCone *p = dynamic_cast<FCGeometryParaCone *>(pb);
        
        if (p == nullptr)
            return;
        double loc[3] = {0.0};
        double bottomR, topR, heigth;
        p->getLocation(loc);
        p->getBottomRadius(&bottomR);
        p->getTopRadius(&topR);
        p->getHeigth(&heigth);
        
        // _pw->setCoordinate(loc);
        ui->lineEdit_locationX->setText(QString::number(loc[0]));
        ui->lineEdit_locationY->setText(QString::number(loc[1]));
        ui->lineEdit_locationZ->setText(QString::number(loc[2]));
        
        ui->lineEdit_bottomR->setText(QString::number(bottomR));
        ui->lineEdit_topR->setText(QString::number(topR));
        ui->lineEdit_height->setText(QString::number(heigth));
    }
}

void FCConeSettingsWidget::on_pushButton_build_clicked()
{
    double corner[3] = {0.0};
    double bottomR, topR, heigth;
    
    bool ok = false;
    ok = getBottomRadius(&bottomR);
    ok = getTopRadius(&topR);
    ok = getHeight(&heigth);
    ok= getCoordinate(corner);
    
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateCone* creator = new FCGeometryCreateCone(this);
    
    connect(creator, &FCGeometryCreateCone::showSet,
            this, &FCConeSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateCone::updateGeoTree,
            this, &FCConeSettingsWidget::updateGeoTree);
    
    connect(creator, &FCGeometryCreateCone::updateDisplayGeometryActor,
            this, &FCConeSettingsWidget::updateGeometryActor);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setBottomRadius(bottomR);
    creator->setTopRadius(topR);
    creator->setHeigth(heigth);
    creator->setEditData(mEidtSetID);
    
    creator->execute();
}


} // namespace FC
