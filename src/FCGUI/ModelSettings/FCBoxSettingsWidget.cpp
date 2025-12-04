/**
 * @file FCBoxSettingsWidget.cpp
 * @brief 立方体参数设置窗口
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCBoxSettingsWidget.h"
#include "ui_FCBoxSettingsWidget.h"
#include "FCGeometryCreateBox.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaBox.h"

namespace FC 
{
FCBoxSettingsWidget::FCBoxSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCBoxSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = false;
    mEidtSetID = 0;
    init();
}

FCBoxSettingsWidget::FCBoxSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCBoxSettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
}

FCBoxSettingsWidget::~FCBoxSettingsWidget()
{
    delete ui;
}

bool FCBoxSettingsWidget::create()
{
    double corner[3] = {0.0};
    double para[3] = {0.0};
    
    bool ok = false;
    ok = getPara(para);
    ok= getCoordinate(corner);
    
    QString name  = ui->lineEdit_name->text();
    
    FCGeometryCreateBox* creator = new FCGeometryCreateBox(this);
        
    connect(creator, &FCGeometryCreateBox::showSet,
            this, &FCBoxSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateBox::updateGeoTree,
            this, &FCBoxSettingsWidget::updateGeoTree);
    
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setGeoPara(para);
        
    creator->execute();
    
    return true;
}

/**
 * @brief 获取设置的参数
 * @param p [out] 存放参数的数组地址
 * @return 
 */
bool FCBoxSettingsWidget::getPara(double *p)
{
    bool ok = false;
    
    QString text = ui->lineEdit_length->text();
    p[0] = text.toDouble(&ok);
    if (!ok) return false;
    
    text = ui->lineEdit_width->text();
    p[1] = text.toDouble(&ok);
    if (!ok) return false;
    
    text = ui->lineEdit_height->text();
    p[2] = text.toDouble(&ok);
    if (!ok) return false;
    
    return true;
}

/**
 * @brief 获取坐标
 * @param coor
 * @return 
 */
bool FCBoxSettingsWidget::getCoordinate(double *coor)
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

/**
 * @brief 初始化，设置默认名称和参数
 * @todo 默认参数设置到
 */
void FCBoxSettingsWidget::init()
{
    // mCreateBox = new FCGeometryCreateBox(this);
    
    if (!mIsEdit) {     // 新建几何模型
        int id = FCGeometrySet::getMaxID() + 1;
        ui->lineEdit_name->setText(QString("Cube_%1").arg(id));
    } else {   // 编辑现有的几何模型
        FCGeometrySet* eidtSet= FCGeometryData::getInstance()->getGeometrySetByID(mEidtSetID);
        if (eidtSet == nullptr){
            return;
        }
        ui->lineEdit_name->setText(eidtSet->getName());
        FCGeometryModelParaBase *pb = eidtSet->getParameter();
        FCGeometryParaBox *p = dynamic_cast<FCGeometryParaBox *>(pb);
        
        if (p == nullptr)
            return;
        double loc[3] = {0.0}, para[3] = {0.0};
        p->getLocation(loc);
        p->getGeoPara(para);
        // _pw->setCoordinate(loc);
        ui->lineEdit_locationX->setText(QString::number(loc[0]));
        ui->lineEdit_locationY->setText(QString::number(loc[1]));
        ui->lineEdit_locationZ->setText(QString::number(loc[2]));

        ui->lineEdit_length->setText(QString::number(para[0]));
        ui->lineEdit_width->setText(QString::number(para[1]));
        ui->lineEdit_height->setText(QString::number(para[2]));
    }
}

/**
 * @brief 构建立方体
 */
void FCBoxSettingsWidget::on_pushButton_build_clicked()
{
    qDebug() << "current id: " << mEidtSetID;
    
    double corner[3] = {0.0};
    double para[3] = {0.0};
    
    bool ok = false;
    ok = getPara(para);
    ok= getCoordinate(corner);
    
    QString name  = ui->lineEdit_name->text();
    
    FCGeometryCreateBox* creator = new FCGeometryCreateBox(this);
    
    connect(creator, &FCGeometryCreateBox::showSet,
            this, &FCBoxSettingsWidget::modelCreated);
    
    connect(creator, &FCGeometryCreateBox::updateGeoTree,
            this, &FCBoxSettingsWidget::updateGeoTree);
    connect(creator, &FCGeometryCreateBox::updateDisplayGeometryActor,
            this, &FCBoxSettingsWidget::updateGeometryActor);
    
    creator->setName(name);
    creator->setLocation(corner);
    creator->setGeoPara(para);
    
    creator->setEditData(mEidtSetID);
    
    creator->execute(); 
    // this->create();
}



} // namespace FC

