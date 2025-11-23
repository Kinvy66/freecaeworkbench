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

namespace FC 
{
FCBoxSettingsWidget::FCBoxSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCBoxSettingsWidget)
{
    ui->setupUi(this);
}

FCBoxSettingsWidget::~FCBoxSettingsWidget()
{
    delete ui;
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
 * @brief 构建立方体
 */
void FCBoxSettingsWidget::on_pushButton_build_clicked()
{
    double corner[3] = {0.0};
    double para[3] = {0.0};
    
    bool ok = false;
    ok = getPara(para);
    
    QString name  = ui->lineEdit_name->text();
    
    FCGeometryCreateBox* c = new FCGeometryCreateBox();
    
    c->setName(name);
    c->setLocation(corner);
    c->setGeoPara(para);
    
    c->execute();

}


} // namespace FC

