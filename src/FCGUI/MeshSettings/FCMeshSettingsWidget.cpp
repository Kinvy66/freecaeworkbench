#include "FCMeshSettingsWidget.h"
#include "ui_FCMeshSettingsWidget.h"
#include "FCUniqueIDGenerater.h"
#include "FCMeshModule.h"
#include <QDebug>
#include "FCMeshData.h"
#include "FCMeshKernal.h"
#include "FCGmshSettingData.h"

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
}

FCMeshSettingsWidget::FCMeshSettingsWidget(const IdType editSetID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCMeshettingsWidget)
{
    ui->setupUi(this);
    mIsEdit = true;
    mEidtSetID = editSetID;
    init();
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
    para->setElementOrder(1);
    para->setMethod(1);
    para->setMinSize(0.0);
    para->setMaxSize(100.0);
    para->setSizeFactor(1.0);
    para->setMethod(1);
    para->setElementType(QString("tri"));
    
    IdType id = meshModule->createMesh(name, para);
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
        qDebug() << "name: " << mesh->getName();
        FCGmshSettingData* para =  dynamic_cast<FCGmshSettingData *>(mesh->getGmshSetting());
        if (para == nullptr) {
            return;
        }
        ui->doubleSpinBoxMinSize->setValue(para->getMinSize());
        // todo 其他参数填充

    }
}

/**
 * @brief 保存参数
 */
void FCMeshSettingsWidget::saveParameter()
{
    FCMeshKernal* mesh = FCMeshData::getInstance()->getMeshKernalByID(mEidtSetID);
    FCGmshSettingData* para =  dynamic_cast<FCGmshSettingData *>(mesh->getGmshSetting());
    para->setMinSize(ui->doubleSpinBoxMinSize->text().toDouble());    
}

void FCMeshSettingsWidget::on_pushButtonGenerateMesh_clicked()
{
    qDebug() << " mesh id: " << mEidtSetID;
    FCMeshModule* meshModule = new FCMeshModule();
    connect(meshModule, &FCMeshModule::meshGenerated,
            this, &FCMeshSettingsWidget::meshGenerated);
    connect(meshModule, &FCMeshModule::meshGenerated,
            this, &FCMeshSettingsWidget::onMeshGenerated);
    
    meshModule->generateMesh(mEidtSetID);
}

void FCMeshSettingsWidget::on_pushButtonSavePara_clicked()
{
    saveParameter();
}

} // namespace FC

