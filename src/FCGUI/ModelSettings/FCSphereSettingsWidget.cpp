/**
 * @file FCSphereSettingsWidget.cpp
 * @brief 球体参数设置页面
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCSphereSettingsWidget.h"
#include "ui_FCSphereSettingsWidget.h"
#include "FCGeometryCreateSphere.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaSphere.h"

namespace FC 
{
FCSphereSettingsWidget::FCSphereSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCSphereSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = false;
    mEidtSetID = 0;
    init();
}

FCSphereSettingsWidget::FCSphereSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCSphereSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
}

FCSphereSettingsWidget::~FCSphereSettingsWidget()
{
    delete ui;
}

bool FCSphereSettingsWidget::create()
{
    double corner[3] = {0.0};
    double r;
    
    bool ok = false;
    ok = getRadius(&r);
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateSphere* creator = new FCGeometryCreateSphere(this);
    
    connect(creator, &FCGeometryCreateSphere::showSet,
            this, &FCSphereSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateSphere::updateGeoTree,
            this, &FCSphereSettingsWidget::updateGeoTree);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setRadius(r);
    
    creator->execute();
    
    return true;
}

bool FCSphereSettingsWidget::getRadius(double *r)
{
    bool ok = false;
    
    QString text = ui->lineEdit_radius->text();
    *r = text.toDouble(&ok);
    if (!ok) return false;
    return true;
}

bool FCSphereSettingsWidget::getCoordinate(double *coor)
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

void FCSphereSettingsWidget::init()
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
        FCGeometryParaSphere *p = dynamic_cast<FCGeometryParaSphere *>(pb);
        
        if (p == nullptr)
            return;
        double loc[3] = {0.0};
        double r;
        p->getLocation(loc);
        p->getRadius(&r);
        
        // _pw->setCoordinate(loc);
        ui->lineEdit_locationX->setText(QString::number(loc[0]));
        ui->lineEdit_locationY->setText(QString::number(loc[1]));
        ui->lineEdit_locationZ->setText(QString::number(loc[2]));
        
        ui->lineEdit_radius->setText(QString::number(r));
    }
}

void FCSphereSettingsWidget::on_pushButton_build_clicked()
{
    double corner[3] = {0.0};
    double r;
    
    bool ok = false;
    ok = getRadius(&r);
    ok= getCoordinate(corner);
    
    
    QString name = ui->lineEdit_name->text();
    
    FCGeometryCreateSphere* creator = new FCGeometryCreateSphere(this);
    
    connect(creator, &FCGeometryCreateSphere::showSet,
            this, &FCSphereSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateSphere::updateGeoTree,
            this, &FCSphereSettingsWidget::updateGeoTree);
    connect(creator, &FCGeometryCreateSphere::updateDisplayGeometryActor,
            this, &FCSphereSettingsWidget::updateGeometryActor);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setRadius(r);
    creator->setEditData(mEidtSetID);
    
    creator->execute();
    
}


} // namespace FC

