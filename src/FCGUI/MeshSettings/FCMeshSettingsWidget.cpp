/**
 * @file FCMeshSettingsWidget.cpp
 * @brief 网格参数设置页面
 * @date 2025-12-12
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshSettingsWidget.h"
#include "ui_FCMeshSettingsWidget.h"
#include "FCUniqueIDGenerater.h"
#include "FCMeshModule.h"
#include <QDebug>
#include "FCMeshData.h"
#include "FCMeshKernal.h"
#include "FCGmshSettingData.h"
#include "FCGeometryData.h"
#include "FCGraphViewWindow.h"

namespace FC 
{
FCMeshSettingsWidget::FCMeshSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCMeshettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = false;
    mEidtSetID = 0;
    init();
    initConnections();
}

FCMeshSettingsWidget::FCMeshSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCMeshettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
    initConnections();
}

FCMeshSettingsWidget::~FCMeshSettingsWidget()
{
    delete ui;
}

void FCMeshSettingsWidget::addMesh()
{
    FCMeshModule* meshModule = new FCMeshModule();
    // int meshIndex = FCMeshKernal::getMaxID();
    QString name = ui->lineEditName->text();
    FCGmshSettingData* para = new FCGmshSettingData();
    updateParameter(para);
    
    IdType id = meshModule->createMesh(name, para);
    
    FCMeshKernal* mesh = FCMeshData::getInstance()->getMeshKernalByID(id);
    
    ui->labelSeletedSurfcaseNumber->setText(QString::number(mesh->getBindedGeometry().size()));
    
    qDebug() << "Add Mesh:  " << name << ", Id: " << id; 
    
    emit updateMeshTree(id, name);
}

void FCMeshSettingsWidget::onMeshGenerated(IdType meshID, bool r)
{
    qDebug() << "onMeshGenerated id: " << meshID;
}

void FCMeshSettingsWidget::init()
{
    if(!mIsEdit) {
        int id = FCMeshKernal::getMaxID() + 1;
        ui->lineEditName->setText(QString("Mesh_%1").arg(id));
    } else {
        FCMeshKernal* mesh = FCMeshData::getInstance()->getMeshKernalByID(mEidtSetID);
        ui->lineEditName->setText(mesh->getName());
        FCGmshSettingData* para =  dynamic_cast<FCGmshSettingData *>(mesh->getGmshSetting());
        if (para == nullptr) {
            return;
        }
        // TODO
        QString eleType =  para->getElementType();
        if (eleType == "quad") {
            ui->radioButtonQuad->setChecked(true);
            ui->radioButtonTriangle->setChecked(false);
        } else {
            ui->radioButtonQuad->setChecked(false);
            ui->radioButtonTriangle->setChecked(true);
        }
        ui->labelSeletedSurfcaseNumber->setText(QString::number(mesh->getBindedGeometry().size()));
        ui->doubleSpinBoxSizeFac->setValue(para->getSizeFactor());
        ui->doubleSpinBoxMinSize->setValue(para->getMinSize());
        ui->doubleSpinBoxMaxSize->setValue(para->getMaxSize());
        ui->spinBoxSmoothing->setValue(para->getSmoothIteration());
    }
}

/**
 * @brief 保存参数
 */
void FCMeshSettingsWidget::saveParameter()
{
    FCMeshKernal* mesh = FCMeshData::getInstance()->getMeshKernalByID(mEidtSetID);
    FCGmshSettingData* para =  dynamic_cast<FCGmshSettingData *>(mesh->getGmshSetting());
    updateParameter(para);     
}

/**
 * @brief 更新ui的设置参数到para
 * @param para
 * @note 参数配置参考 https://gmsh.info/doc/texinfo/gmsh.html#Gmsh-options
 */
void FCMeshSettingsWidget::updateParameter(FCGmshSettingData *para)
{
    bool isAll = false;
    QString eleType = "Tri";
    const int orderindex = ui->comboBoxOrder->currentIndex() + 1;
    if (ui->checkBoxSelectAll->isChecked()) {
        isAll = true;
    }
    if (ui->checkBoxSelectVisible->isChecked()) {
        isAll = false;
    }
    if (ui->radioButtonTriangle->isChecked()) {
        eleType = "Tri";
    }
    if (ui->radioButtonQuad->isChecked()) {
        eleType = "Quad";
    }
    const int methodIndex = ui->comboBoxMethod->currentIndex();
    const double factor = ui->doubleSpinBoxSizeFac->value();
    const double minsize = ui->doubleSpinBoxMinSize->value();
    const double maxsize = ui->doubleSpinBoxMaxSize->value();
    const int smooth = ui->spinBoxSmoothing->value();
    int method = 6;  // Frontal-Delaunay
    
    switch (methodIndex) {
    case 0:
        method = 1;
        break;
    case 1:
        method = 2;        
        break;
    case 2:
        method = 3;        
        break;
    case 3:
        method = 5;
        break;
    case 4:
        method = 6;
        break;
    case 5:
        method = 7;
        break;
    case 6:
        method = 8;
        break;
    case 7:
        method = 9;
        break;
    case 8:
        method = 11;
        break;
    default:
        break;
    }
    
    para->setElementOrder(orderindex);
    para->setElementType(eleType);
    para->setSizeFactor(factor);
    para->setMinSize(minsize);
    para->setMaxSize(maxsize);
    para->setSmoothIteration(smooth);
    para->setMethod(method);
}

void FCMeshSettingsWidget::on_pushButtonGenerateMesh_clicked()
{
    qDebug() << " mesh id: " << mEidtSetID;
    FCMeshModule* meshModule = new FCMeshModule();
    connect(meshModule, &FCMeshModule::meshGenerated,
            this, &FCMeshSettingsWidget::meshGenerated);
    // connect(meshModule, &FCMeshModule::meshGenerated,
    //         this, &FCMeshSettingsWidget::onMeshGenerated);
    
    saveParameter();
    meshModule->generateMesh(mEidtSetID);
}

void FCMeshSettingsWidget::on_pushButtonSavePara_clicked()
{
    saveParameter();
}

void FCMeshSettingsWidget::on_checkBoxSelectAll_clicked()
{
    if(ui->checkBoxSelectAll->isChecked()) {
        ui->checkBoxSelectVisible->setChecked(false);
    }
}

void FCMeshSettingsWidget::on_checkBoxSelectVisible_clicked()
{
    if (ui->checkBoxSelectVisible->isChecked()) {
        ui->checkBoxSelectAll->setChecked(false);
    }
}

void FCMeshSettingsWidget::on_pushButtonSelcet_clicked()
{
    FCMeshKernal* mesh = FCMeshData::getInstance()->getMeshKernalByID(mEidtSetID);
    mesh->bindGeometry(FCGeometryData::getInstance()->getAllGeometrySetID());
    ui->labelSeletedSurfcaseNumber->setText(
        QString::number(mesh->getBindedGeometry().size()));
}

void FCMeshSettingsWidget::initConnections()
{
    // 连接几何可见性复选框
    connect(ui->checkBoxGeometryVisible, &QCheckBox::toggled,
            this, &FCMeshSettingsWidget::on_checkBoxGeometryVisible_toggled);
}

void FCMeshSettingsWidget::setGraphViewWindow(FCGraphViewWindow* viewWindow)
{
    mGraphViewWindow = viewWindow;
}

void FCMeshSettingsWidget::on_checkBoxGeometryVisible_toggled(bool checked)
{
    // 通过mGraphViewWindow控制几何可见性
    if (mGraphViewWindow) {
        mGraphViewWindow->setGeometryVisible(checked);
    } else {
        qWarning() << "FCMeshSettingsWidget: GraphViewWindow not set, cannot control geometry visibility";
    }
}

void FCMeshSettingsWidget::on_pushButtonReset_clicked()
{
    // 重置网格类型：三角形
    ui->radioButtonTriangle->setChecked(true);
    ui->radioButtonQuad->setChecked(false);
    
    // 重置阶次：一阶（index=0）
    ui->comboBoxOrder->setCurrentIndex(0);
    
    // 重置方法：MeshAdapt（index=0，对应method=1）
    ui->comboBoxMethod->setCurrentIndex(0);
    
    // 重置尺寸因子：1.0
    ui->doubleSpinBoxSizeFac->setValue(1.0);
    
    // 重置最小单元尺寸：0.0
    ui->doubleSpinBoxMinSize->setValue(0.0);
    
    // 重置最大单元尺寸：100.0
    ui->doubleSpinBoxMaxSize->setValue(100.0);
    
    // 重置光滑迭代次数：20
    ui->spinBoxSmoothing->setValue(20);
    
    // 重置选择选项：全选
    ui->checkBoxSelectAll->setChecked(true);
    ui->checkBoxSelectVisible->setChecked(false);
    
    // 如果是编辑模式，同时更新mesh的参数
    if (mIsEdit && mEidtSetID != 0) {
        FCMeshKernal* mesh = FCMeshData::getInstance()->getMeshKernalByID(mEidtSetID);
        if (mesh) {
            FCGmshSettingData* para = dynamic_cast<FCGmshSettingData*>(mesh->getGmshSetting());
            if (para) {
                // 创建默认参数对象并更新
                FCGmshSettingData defaultPara;
                defaultPara.setElementType("Tri");
                defaultPara.setElementOrder(1);
                defaultPara.setMethod(1);  // MeshAdapt
                defaultPara.setSizeFactor(1.0);
                defaultPara.setMinSize(0.0);
                defaultPara.setMaxSize(100.0);
                defaultPara.setSmoothIteration(20);
                defaultPara.setSelectAll(true);
                defaultPara.setSelectVisiable(false);
                
                // 复制默认参数到当前参数
                para->copy(&defaultPara);
            }
        }
    }
}


} // namespace FC

