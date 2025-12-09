#include "FCMeshettingsWidget.h"
#include "ui_FCMeshettingsWidget.h"

FCMeshettingsWidget::FCMeshettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCMeshettingsWidget)
{
    ui->setupUi(this);
}

FCMeshettingsWidget::~FCMeshettingsWidget()
{
    delete ui;
}
