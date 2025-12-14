/**
 * @file FCPostProcessingTransformPage.cpp
 * @brief 后处理坐标变换页面
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingTransformPage.h"
#include "ui_FCPostProcessingTransformPage.h"
#include "FCGraphViewWindow.h"
#include "FCPostProcessingViewProvider.h"
#include "FCPostProcessingViewObject.h"

namespace FC 
{

FCPostProcessingTransformPage::FCPostProcessingTransformPage(FCGraphViewWindow* viewWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCPostProcessingTransformPage)
    , mViewWindow(viewWindow)
{
    ui->setupUi(this);
    init();
    initConnections();
}

FCPostProcessingTransformPage::~FCPostProcessingTransformPage()
{
    delete ui;
}

void FCPostProcessingTransformPage::setPostProcessingID(IdType postID)
{
    mCurrentPostID = postID;
    updateUIFromPostProcessing(postID);
}

void FCPostProcessingTransformPage::updateUIFromPostProcessing(IdType postID)
{
    mCurrentPostID = postID;
    
    if (!mViewWindow || postID == 0) {
        return;
    }
    
    // TODO: 从ViewObject读取变换属性并更新UI
    // 目前使用默认值
}

void FCPostProcessingTransformPage::init()
{
    // 初始化坐标变换输入框
    ui->doubleSpinBoxTranslationX->setValue(0.0);
    ui->doubleSpinBoxTranslationY->setValue(0.0);
    ui->doubleSpinBoxTranslationZ->setValue(0.0);
    ui->doubleSpinBoxScaleX->setValue(1.0);
    ui->doubleSpinBoxScaleY->setValue(1.0);
    ui->doubleSpinBoxScaleZ->setValue(1.0);
    ui->doubleSpinBoxOrientationX->setValue(0.0);
    ui->doubleSpinBoxOrientationY->setValue(0.0);
    ui->doubleSpinBoxOrientationZ->setValue(0.0);
    ui->doubleSpinBoxCenterPointX->setValue(1.0);
    ui->doubleSpinBoxCenterPointY->setValue(0.5);
    ui->doubleSpinBoxCenterPointZ->setValue(3.0);
}

void FCPostProcessingTransformPage::initConnections()
{
    // 坐标变换
    connect(ui->doubleSpinBoxTranslationX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onTranslationChanged);
    connect(ui->doubleSpinBoxTranslationY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onTranslationChanged);
    connect(ui->doubleSpinBoxTranslationZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onTranslationChanged);
    
    connect(ui->doubleSpinBoxScaleX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onScaleChanged);
    connect(ui->doubleSpinBoxScaleY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onScaleChanged);
    connect(ui->doubleSpinBoxScaleZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onScaleChanged);
    
    connect(ui->doubleSpinBoxOrientationX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onOrientationChanged);
    connect(ui->doubleSpinBoxOrientationY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onOrientationChanged);
    connect(ui->doubleSpinBoxOrientationZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onOrientationChanged);
    
    connect(ui->doubleSpinBoxCenterPointX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onCenterPointChanged);
    connect(ui->doubleSpinBoxCenterPointY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onCenterPointChanged);
    connect(ui->doubleSpinBoxCenterPointZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &FCPostProcessingTransformPage::onCenterPointChanged);
}

void FCPostProcessingTransformPage::onTranslationChanged()
{
    mTranslation[0] = ui->doubleSpinBoxTranslationX->value();
    mTranslation[1] = ui->doubleSpinBoxTranslationY->value();
    mTranslation[2] = ui->doubleSpinBoxTranslationZ->value();
    applySettings();
}

void FCPostProcessingTransformPage::onScaleChanged()
{
    mScale[0] = ui->doubleSpinBoxScaleX->value();
    mScale[1] = ui->doubleSpinBoxScaleY->value();
    mScale[2] = ui->doubleSpinBoxScaleZ->value();
    applySettings();
}

void FCPostProcessingTransformPage::onOrientationChanged()
{
    mOrientation[0] = ui->doubleSpinBoxOrientationX->value();
    mOrientation[1] = ui->doubleSpinBoxOrientationY->value();
    mOrientation[2] = ui->doubleSpinBoxOrientationZ->value();
    applySettings();
}

void FCPostProcessingTransformPage::onCenterPointChanged()
{
    mCenterPoint[0] = ui->doubleSpinBoxCenterPointX->value();
    mCenterPoint[1] = ui->doubleSpinBoxCenterPointY->value();
    mCenterPoint[2] = ui->doubleSpinBoxCenterPointZ->value();
    applySettings();
}

void FCPostProcessingTransformPage::applySettings()
{
    if (!mViewWindow || mCurrentPostID == 0) {
        return;
    }
    
    // TODO: 应用变换设置到ViewObject
    // 获取ViewProvider
    FCPostProcessingViewProvider* provider = mViewWindow->getPostProcessingViewProvider();
    if (!provider) return;
    
    // 获取ViewObject
    FCPostProcessingViewObject* viewObj = provider->getViewObject(mCurrentPostID);
    if (!viewObj) return;
    
    // TODO: 应用变换属性
    // viewObj->setTransform(...);
    
    updateRenderWindow();
    emit transformPropertyChanged(mCurrentPostID);
}

void FCPostProcessingTransformPage::updateRenderWindow()
{
    if (!mViewWindow) return;
    mViewWindow->reRender();
}

} // namespace FC
