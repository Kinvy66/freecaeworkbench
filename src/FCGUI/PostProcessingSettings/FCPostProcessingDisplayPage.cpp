/**
 * @file FCPostProcessingDisplayPage.cpp
 * @brief 后处理显示页面
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingDisplayPage.h"
#include "ui_FCPostProcessingDisplayPage.h"
#include "FCGraphViewWindow.h"
#include "FCPostProcessingViewProvider.h"
#include "FCPostProcessingViewObject.h"
#include "FCPostProcessingData.h"
#include "FCPostProcessingKernal.h"
#include "FCGraph3DWindow.h"
#include <QColorDialog>
#include <QDebug>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>

namespace FC 
{

FCPostProcessingDisplayPage::FCPostProcessingDisplayPage(FCGraphViewWindow* viewWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCPostProcessingDisplayPage)
    , mViewWindow(viewWindow)
{
    ui->setupUi(this);
    init();
    initConnections();
}

FCPostProcessingDisplayPage::~FCPostProcessingDisplayPage()
{
    delete ui;
}

void FCPostProcessingDisplayPage::setPostProcessingID(IdType postID)
{
    mCurrentPostID = postID;
    updateUIFromPostProcessing(postID);
}

void FCPostProcessingDisplayPage::updateUIFromPostProcessing(IdType postID)
{
    mCurrentPostID = postID;
    
    if (!mViewWindow || postID == 0) {
        return;
    }
    
    // 获取ViewProvider
    FCPostProcessingViewProvider* provider = mViewWindow->getPostProcessingViewProvider();
    if (!provider) return;
    
    // 获取ViewObject
    FCPostProcessingViewObject* viewObj = provider->getViewObject(postID);
    if (!viewObj) {
        return;
    }
    
    // 显示形式
    mDisplayForm = viewObj->getDisplayForm();
    ui->comboBoxDisplayForm->setCurrentIndex(mDisplayForm);
    
    // 透明度
    mTransparency = viewObj->getTransparency();
    ui->sliderTransparency->setValue(static_cast<int>(mTransparency * 100));
    ui->labelTransparencyValue->setText(QString::number(mTransparency));
    
    // 点大小
    mPointSize = viewObj->getPointSize();
    ui->spinBoxPointSize->setValue(mPointSize);
    
    // 线宽
    mLineWidth = viewObj->getLineWidth();
    ui->spinBoxLineWidth->setValue(mLineWidth);
    
    // 着色方式
    mShadingMethod = viewObj->getShadingMethod();
    ui->comboBoxShadingMethod->setCurrentIndex(mShadingMethod);
    
    // 光照属性
    viewObj->getLightingProperties(mSpecularCoefficient, mSpecularIntensity,
                                    mAmbientCoefficient, mDiffuseCoefficient);
    ui->sliderSpecularCoefficient->setValue(static_cast<int>(mSpecularCoefficient * 100));
    ui->labelSpecularCoefficientValue->setText(QString::number(mSpecularCoefficient));
    ui->sliderSpecularIntensity->setValue(static_cast<int>(mSpecularIntensity));
    ui->labelSpecularIntensityValue->setText(QString::number(static_cast<int>(mSpecularIntensity)));
    ui->sliderAmbientCoefficient->setValue(static_cast<int>(mAmbientCoefficient * 100));
    ui->labelAmbientCoefficientValue->setText(QString::number(mAmbientCoefficient));
    ui->sliderDiffuseCoefficient->setValue(static_cast<int>(mDiffuseCoefficient * 100));
    ui->labelDiffuseCoefficientValue->setText(QString::number(mDiffuseCoefficient));
    
    // 边界颜色
    double r, g, b;
    viewObj->getBoundaryColor(r, g, b);
    mBoundaryColor = QColor::fromRgbF(r, g, b);
    updateBoundaryColorDisplay();
    
    // 边界显示
    mBoundaryVisibility = viewObj->getBoundaryVisibility();
    ui->checkBoxBoundaryVisibility->setChecked(mBoundaryVisibility);
    
    // 检查图例显示状态，如果未显示则默认显示
    FCGraph3DWindow* graph3D = dynamic_cast<FCGraph3DWindow*>(mViewWindow);
    if (graph3D) {
        mShowLegend = graph3D->isScalarBarVisible();
        // 如果图例未显示，默认显示图例
        if (!mShowLegend) {
            mShowLegend = true;
            updateRenderWindow();
        }
    }
}

void FCPostProcessingDisplayPage::init()
{
    // 初始化显示形式下拉框
    ui->comboBoxDisplayForm->addItem(tr("面"));
    ui->comboBoxDisplayForm->addItem(tr("线框"));
    ui->comboBoxDisplayForm->addItem(tr("点"));
    
    // 初始化颜色列下拉框
    ui->comboBoxColorColumn->addItem(tr("scalars"));
    ui->comboBoxColorColumn->addItem(tr("X"));
    ui->comboBoxColorColumn->addItem(tr("Y"));
    ui->comboBoxColorColumn->addItem(tr("Z"));
    
    // 初始化着色方式下拉框
    ui->comboBoxShadingMethod->addItem(tr("平面着色"));
    ui->comboBoxShadingMethod->addItem(tr("Gouraud着色"));
    ui->comboBoxShadingMethod->addItem(tr("Phong着色"));
    
    // 初始化透明度滑块
    ui->sliderTransparency->setRange(0, 100);
    ui->sliderTransparency->setValue(100);
    ui->labelTransparencyValue->setText("1");
    
    // 初始化点大小和线宽
    ui->spinBoxPointSize->setRange(1, 100);
    ui->spinBoxPointSize->setValue(2);
    ui->spinBoxLineWidth->setRange(1, 100);
    ui->spinBoxLineWidth->setValue(1);
    
    // 初始化反射光系数滑块
    ui->sliderSpecularCoefficient->setRange(0, 100);
    ui->sliderSpecularCoefficient->setValue(0);
    ui->labelSpecularCoefficientValue->setText("0");
    
    // 初始化反射光强度滑块
    ui->sliderSpecularIntensity->setRange(0, 100);
    ui->sliderSpecularIntensity->setValue(100);
    ui->labelSpecularIntensityValue->setText("100");
    
    // 初始化环境光系数滑块
    ui->sliderAmbientCoefficient->setRange(0, 100);
    ui->sliderAmbientCoefficient->setValue(0);
    ui->labelAmbientCoefficientValue->setText("0");
    
    // 初始化漫反射光系数滑块
    ui->sliderDiffuseCoefficient->setRange(0, 100);
    ui->sliderDiffuseCoefficient->setValue(100);
    ui->labelDiffuseCoefficientValue->setText("1");
    
    // 初始化边界颜色显示
    updateBoundaryColorDisplay();
}

void FCPostProcessingDisplayPage::initConnections()
{
    // 显示形式
    connect(ui->comboBoxDisplayForm, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FCPostProcessingDisplayPage::onDisplayFormChanged);
    
    // 颜色列
    connect(ui->comboBoxColorColumn, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FCPostProcessingDisplayPage::onColorColumnChanged);
    
    // 显示图例
    connect(ui->pushButtonShowLegend, &QPushButton::clicked,
            this, &FCPostProcessingDisplayPage::onShowLegendClicked);
    
    // 编辑颜色
    connect(ui->pushButtonEditColor, &QPushButton::clicked,
            this, &FCPostProcessingDisplayPage::onEditColorClicked);
    
    // 透明度
    connect(ui->sliderTransparency, &QSlider::valueChanged,
            this, &FCPostProcessingDisplayPage::onTransparencyChanged);
    
    // 点大小
    connect(ui->spinBoxPointSize, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FCPostProcessingDisplayPage::onPointSizeChanged);
    
    // 线宽
    connect(ui->spinBoxLineWidth, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FCPostProcessingDisplayPage::onLineWidthChanged);
    
    // 着色方式
    connect(ui->comboBoxShadingMethod, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FCPostProcessingDisplayPage::onShadingMethodChanged);
    
    // 反射光系数
    connect(ui->sliderSpecularCoefficient, &QSlider::valueChanged,
            this, &FCPostProcessingDisplayPage::onSpecularCoefficientChanged);
    
    // 反射光颜色
    connect(ui->pushButtonSpecularColor, &QPushButton::clicked,
            this, &FCPostProcessingDisplayPage::onSpecularColorClicked);
    
    // 反射光强度
    connect(ui->sliderSpecularIntensity, &QSlider::valueChanged,
            this, &FCPostProcessingDisplayPage::onSpecularIntensityChanged);
    
    // 环境光系数
    connect(ui->sliderAmbientCoefficient, &QSlider::valueChanged,
            this, &FCPostProcessingDisplayPage::onAmbientCoefficientChanged);
    
    // 漫反射光系数
    connect(ui->sliderDiffuseCoefficient, &QSlider::valueChanged,
            this, &FCPostProcessingDisplayPage::onDiffuseCoefficientChanged);
    
    // 边界颜色
    connect(ui->pushButtonBoundaryColor, &QPushButton::clicked,
            this, &FCPostProcessingDisplayPage::onBoundaryColorClicked);
    
    // 边界显示
    connect(ui->checkBoxBoundaryVisibility, &QCheckBox::toggled,
            this, &FCPostProcessingDisplayPage::onBoundaryVisibilityChanged);
}

void FCPostProcessingDisplayPage::onDisplayFormChanged(int index)
{
    mDisplayForm = index;
    applySettings();
}

void FCPostProcessingDisplayPage::onColorColumnChanged(int index)
{
    QStringList columns = {"scalars", "X", "Y", "Z"};
    if (index >= 0 && index < columns.size()) {
        mColorColumn = columns[index];
    }
    applySettings();
}

void FCPostProcessingDisplayPage::onShowLegendClicked()
{
    mShowLegend = !mShowLegend;
    updateRenderWindow();
}

void FCPostProcessingDisplayPage::onEditColorClicked()
{
    QColorDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QColor color = dialog.selectedColor();
        applySettings();
    }
}

void FCPostProcessingDisplayPage::onTransparencyChanged(int value)
{
    mTransparency = value / 100.0;
    ui->labelTransparencyValue->setText(QString::number(mTransparency));
    applySettings();
}

void FCPostProcessingDisplayPage::onPointSizeChanged(int value)
{
    mPointSize = value;
    applySettings();
}

void FCPostProcessingDisplayPage::onLineWidthChanged(int value)
{
    mLineWidth = value;
    applySettings();
}

void FCPostProcessingDisplayPage::onShadingMethodChanged(int index)
{
    mShadingMethod = index;
    applySettings();
}

void FCPostProcessingDisplayPage::onSpecularCoefficientChanged(int value)
{
    mSpecularCoefficient = value / 100.0;
    ui->labelSpecularCoefficientValue->setText(QString::number(mSpecularCoefficient));
    applySettings();
}

void FCPostProcessingDisplayPage::onSpecularColorClicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(mSpecularColor);
    if (dialog.exec() == QDialog::Accepted) {
        mSpecularColor = dialog.selectedColor();
        applySettings();
    }
}

void FCPostProcessingDisplayPage::onSpecularIntensityChanged(int value)
{
    mSpecularIntensity = value;
    ui->labelSpecularIntensityValue->setText(QString::number(value));
    applySettings();
}

void FCPostProcessingDisplayPage::onAmbientCoefficientChanged(int value)
{
    mAmbientCoefficient = value / 100.0;
    ui->labelAmbientCoefficientValue->setText(QString::number(mAmbientCoefficient));
    applySettings();
}

void FCPostProcessingDisplayPage::onDiffuseCoefficientChanged(int value)
{
    mDiffuseCoefficient = value / 100.0;
    ui->labelDiffuseCoefficientValue->setText(QString::number(mDiffuseCoefficient));
    applySettings();
}

void FCPostProcessingDisplayPage::onBoundaryColorClicked()
{
    QColorDialog dialog(this);
    dialog.setCurrentColor(mBoundaryColor);
    if (dialog.exec() == QDialog::Accepted) {
        mBoundaryColor = dialog.selectedColor();
        updateBoundaryColorDisplay();
        applySettings();
    }
}

void FCPostProcessingDisplayPage::onBoundaryVisibilityChanged(bool checked)
{
    mBoundaryVisibility = checked;
    applySettings();
}

void FCPostProcessingDisplayPage::applySettings()
{
    if (!mViewWindow || mCurrentPostID == 0) {
        return;
    }
    
    // 获取ViewProvider
    FCPostProcessingViewProvider* provider = mViewWindow->getPostProcessingViewProvider();
    if (!provider) return;
    
    // 获取ViewObject
    FCPostProcessingViewObject* viewObj = provider->getViewObject(mCurrentPostID);
    if (!viewObj) return;
    
    // 应用显示属性设置
    viewObj->setDisplayForm(mDisplayForm);
    viewObj->setTransparency(mTransparency);
    viewObj->setPointSize(mPointSize);
    viewObj->setLineWidth(mLineWidth);
    viewObj->setShadingMethod(mShadingMethod);
    viewObj->setLightingProperties(mSpecularCoefficient, mSpecularIntensity,
                                    mAmbientCoefficient, mDiffuseCoefficient);
    viewObj->setBoundaryColor(mBoundaryColor.redF(), mBoundaryColor.greenF(), mBoundaryColor.blueF());
    viewObj->setBoundaryVisibility(mBoundaryVisibility);
    
    // 更新渲染窗口的图例显示
    updateRenderWindow();
    
    emit displayPropertyChanged(mCurrentPostID);
}

void FCPostProcessingDisplayPage::updateRenderWindow()
{
    if (!mViewWindow) return;
    
    FCGraph3DWindow* graph3D = dynamic_cast<FCGraph3DWindow*>(mViewWindow);
    if (!graph3D) return;
    
    // 更新图例显示
    if (mShowLegend && mCurrentPostID != 0) {
        // 获取ViewObject的LookupTable并更新标量条
        FCPostProcessingViewProvider* provider = mViewWindow->getPostProcessingViewProvider();
        if (provider) {
            FCPostProcessingViewObject* viewObj = provider->getViewObject(mCurrentPostID);
            if (viewObj) {
                vtkLookupTable* lut = viewObj->getLookupTable();
                if (lut) {
                    graph3D->updateScalarBar(lut, mColorColumn);
                }
            }
        }
    } else {
        // 隐藏标量条
        graph3D->showScalarBar(false);
    }
    
    // 重新渲染
    mViewWindow->reRender();
}

void FCPostProcessingDisplayPage::updateBoundaryColorDisplay()
{
    QString style = QString("background-color: rgb(%1, %2, %3);")
                    .arg(mBoundaryColor.red())
                    .arg(mBoundaryColor.green())
                    .arg(mBoundaryColor.blue());
    ui->labelBoundaryColor->setStyleSheet(style);
}

} // namespace FC
