#include "FCMeshSettingsWidget.h"
#include "ui_FCMeshSettingsWidget.h"
#include "FCUniqueIDGenerater.h"
#include "FCMeshModule.h"
#include <QDebug>


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
    IdType id = FCUniqueIDGenerater::id_uint64();
    
    emit updateMeshTree(id, QString("Mesh"));
}

void FCMeshSettingsWidget::init()
{
    
}

void FCMeshSettingsWidget::on_pushButtonGenerateMesh_clicked()
{
    qDebug() << "current mesh id: " << mEidtSetID;
    FCMeshModule::getInstance()->exec();
}


} // namespace FC

