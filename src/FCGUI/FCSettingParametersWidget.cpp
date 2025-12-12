/**
 * @file FCSettingParametersWidget.cpp
 * @brief 模型参数设置窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCSettingParametersWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>

#include "FCGeometryData.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaCylinder.h"
// parameters widget
#include "FCBoxSettingsWidget.h"
#include "FCCylinderSettingsWidget.h"
#include "FCConeSettingsWidget.h"
#include "FCSphereSettingsWidget.h"
#include "FCTorusSettingsWidget.h"

#include "FCMeshSettingsWidget.h"

namespace FC 
{

FCSettingParametersWidget::FCSettingParametersWidget(QWidget *parent)
 : QWidget(parent)
{
    // QLabel* lab = new QLabel(this);
    // lab->setText("Setting Docking");
    mLayout = new QVBoxLayout(this);
    // --- 添加背景色和边框 ---
    
    // 背景颜色不使用 QSS，避免子控件继承
    this->setAutoFillBackground(true);
    
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(250, 251, 254));
    this->setPalette(pal);
}

FCSettingParametersWidget::~FCSettingParametersWidget()
{
    
}

/**
 * @brief 创建立方体
 */
void FCSettingParametersWidget::createBox()
{
    FCBoxSettingsWidget* cubeSettingsWidget = new FCBoxSettingsWidget(this);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    connect(cubeSettingsWidget, &FCBoxSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    cubeSettingsWidget->create();
    
    // setCurrentWidget(cubeSettingsWidget);
}

/**
 * @brief 创建圆柱
 */
void FCSettingParametersWidget::createCylinder()
{
    FCCylinderSettingsWidget* cylinderSettingsWidget = new FCCylinderSettingsWidget(this);
    connect(cylinderSettingsWidget, &FCCylinderSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    
    connect(cylinderSettingsWidget, &FCCylinderSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    cylinderSettingsWidget->create();
    // setCurrentWidget(cylinderSettingsWidget);
}

/**
 * @brief 创建圆锥
 */
void FCSettingParametersWidget::createCone()
{
    FCConeSettingsWidget* settingsWidget = new FCConeSettingsWidget(this);
    connect(settingsWidget, &FCConeSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    
    connect(settingsWidget, &FCConeSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    settingsWidget->create();
}

/**
 * @brief 创建球体
 */
void FCSettingParametersWidget::createSphere()
{
    FCSphereSettingsWidget* settingsWidget = new FCSphereSettingsWidget(this);
    connect(settingsWidget, &FCSphereSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    
    connect(settingsWidget, &FCSphereSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    settingsWidget->create();
}

/**
 * @brief 创建圆环
 */
void FCSettingParametersWidget::createTorus()
{
    FCTorusSettingsWidget* settingsWidget = new FCTorusSettingsWidget(this);
    connect(settingsWidget, &FCTorusSettingsWidget::modelCreated,
            this, &FCSettingParametersWidget::geometryModelCreated);
    
    connect(settingsWidget, &FCTorusSettingsWidget::updateGeoTree,
            this, &FCSettingParametersWidget::updateGeoTree);
    
    settingsWidget->create();
}

/**
 * @brief 添加网格
 */
void FCSettingParametersWidget::addMesh()
{
    FCMeshSettingsWidget* settingsWidget = new FCMeshSettingsWidget(this);
    
    connect(settingsWidget, &FCMeshSettingsWidget::updateMeshTree,
            this, &FCSettingParametersWidget::updateMeshTree);
    connect(settingsWidget, &FCMeshSettingsWidget::meshGenerated,
            this, &FCSettingParametersWidget::meshGenerated);
    
    settingsWidget->addMesh();
    
    // setCurrentWidget(settingsWidget);
}

void FCSettingParametersWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    
    QPen pen(QColor(130, 135, 144));
   
    pen.setWidth(1);              // 设置边框粗细 = 2 像素
    p.setPen(pen);
    // 边框整体缩小 5px
    int margin = 2;
    QRect r = rect().adjusted(margin, margin, -margin-1, -margin-1);
    
    p.drawRect(r);
}

/**
 * @brief 显示当前选中的item的参数页面
 * @param id
 * @param name
 */
void FCSettingParametersWidget::updateCurrentGeoSettingWidget(const IdType id,
                                                           const QString& name)
{
    Q_UNUSED(name)
    QWidget *w= nullptr;
    FCGeometrySet* editSet = FCGeometryData::getInstance()->getGeometrySetByID(id);
    if (!editSet) {
        setCurrentWidget(w);        
        return;
    }
    GeometryParaType paraType =  editSet->getParameter()->getParaType();
    
    switch (paraType) {
    case GeometryParaCreateBox:
    {
        FCBoxSettingsWidget* settingsWidget = new FCBoxSettingsWidget(id, this);
        connect(settingsWidget, &FCBoxSettingsWidget::modelCreated,
                this, &FCSettingParametersWidget::geometryModelCreated);
        connect(settingsWidget, &FCBoxSettingsWidget::updateGeoTree,
                this, &FCSettingParametersWidget::updateGeoTree);
        
        connect(settingsWidget, &FCBoxSettingsWidget::updateGeometryActor, this,
                &FCSettingParametersWidget::updateGeometryAcotr);
        w = settingsWidget;
    }
        break;
    case GeometryParaCreateCylinder:
    {
        FCCylinderSettingsWidget* settingsWidget = new FCCylinderSettingsWidget(id, this);
        connect(settingsWidget, &FCCylinderSettingsWidget::modelCreated,
                this, &FCSettingParametersWidget::geometryModelCreated);
        connect(settingsWidget, &FCCylinderSettingsWidget::updateGeoTree,
                this, &FCSettingParametersWidget::updateGeoTree);
        connect(settingsWidget, &FCCylinderSettingsWidget::updateGeometryActor, this,
                &FCSettingParametersWidget::updateGeometryAcotr);
        w = settingsWidget;
    }
    break;
    case GeometryParaCreateCone:
    {
        FCConeSettingsWidget* settingsWidget = new FCConeSettingsWidget(id, this);
        connect(settingsWidget, &FCConeSettingsWidget::modelCreated,
                this, &FCSettingParametersWidget::geometryModelCreated);
        connect(settingsWidget, &FCConeSettingsWidget::updateGeoTree,
                this, &FCSettingParametersWidget::updateGeoTree);
        connect(settingsWidget, &FCConeSettingsWidget::updateGeometryActor, this,
                &FCSettingParametersWidget::updateGeometryAcotr);
        w = settingsWidget;
    }
    break;
    case GeometryParaCreateSphere:
    {
        FCSphereSettingsWidget* settingsWidget = new FCSphereSettingsWidget(id, this);
        connect(settingsWidget, &FCSphereSettingsWidget::modelCreated,
                this, &FCSettingParametersWidget::geometryModelCreated);
        connect(settingsWidget, &FCSphereSettingsWidget::updateGeoTree,
                this, &FCSettingParametersWidget::updateGeoTree);
        connect(settingsWidget, &FCSphereSettingsWidget::updateGeometryActor, this,
                &FCSettingParametersWidget::updateGeometryAcotr);
        w = settingsWidget;
    }
    break;
    case GeometryParaCreateTorus:
    {
        FCTorusSettingsWidget* settingsWidget = new FCTorusSettingsWidget(id, this);
        connect(settingsWidget, &FCTorusSettingsWidget::modelCreated,
                this, &FCSettingParametersWidget::geometryModelCreated);
        connect(settingsWidget, &FCTorusSettingsWidget::updateGeoTree,
                this, &FCSettingParametersWidget::updateGeoTree);
        connect(settingsWidget, &FCTorusSettingsWidget::updateGeometryActor, this,
                &FCSettingParametersWidget::updateGeometryAcotr);
        w = settingsWidget;
    }
    break;
    default:
        break;
    }
    setCurrentWidget(w);

    
    // qDebug() << "updateCurrentWidget id" << id;
}

void FCSettingParametersWidget::updateCurrentMeshSettingWidget(const IdType id, const QString &name)
{
    Q_UNUSED(name)
    FCMeshSettingsWidget* settingsWidget = new FCMeshSettingsWidget(id, this);
    
    connect(settingsWidget, &FCMeshSettingsWidget::updateMeshTree,
            this, &FCSettingParametersWidget::updateMeshTree);
    
    connect(settingsWidget, &FCMeshSettingsWidget::meshGenerated,
            this, &FCSettingParametersWidget::meshGenerated);
    // connect(settingsWidget, &FCMeshSettingsWidget::updateMeshActor,
    //         this, &FCSettingParametersWidget::updateMeshAcotr);
    
    
    setCurrentWidget(settingsWidget);
}

void FCSettingParametersWidget::updateCurrentSettingWidget(const IdType id, const QString &name)
{
    Q_UNUSED(name)
    
    if (id == 0) {
        setCurrentWidget(nullptr);   
    }
}

// void FCSettingParametersWidget::onMeshGenerated(IdType meshID, bool r)
// {
//     qDebug() << "mesh id: " << meshID;
// }

void FCSettingParametersWidget::setCurrentWidget(QWidget *w)
{
    // 移除旧的 widget
    if (mCurrentWidget) {
        mLayout->removeWidget(mCurrentWidget);
        mCurrentWidget->deleteLater();
        mCurrentWidget = nullptr;
    }
    
    // 接收到 nullptr，直接显示空白（不添加控件）
    if (!w) {
        return;
    }
    
    // 设置新的 widget
    mCurrentWidget = w;
    mLayout->addWidget(w);
}

} // namespace FC
