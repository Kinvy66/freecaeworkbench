/**
 * @file FCPostProcessingSettingsWidget.cpp
 * @brief 后处理显示设置窗口
 * @date 2025-12-15
 * @version V0.0.1
 * @details 参考COMSOL的后处理显示设置
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingSettingsWidget.h"
#include "FCPostProcessingKernal.h"
#include "FCPostProcessingData.h"
#include <QComboBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <QDebug>

namespace FC 
{

FCPostProcessingSettingsWidget::FCPostProcessingSettingsWidget(QWidget* parent)
    : QWidget(parent)
{
    initUI();
}

FCPostProcessingSettingsWidget::~FCPostProcessingSettingsWidget()
{
}

void FCPostProcessingSettingsWidget::initUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    
    // 标量场选择
    QGroupBox* scalarGroup = new QGroupBox(tr("标量场"), this);
    QVBoxLayout* scalarLayout = new QVBoxLayout(scalarGroup);
    
    mScalarFieldCombo = new QComboBox(this);
    mScalarFieldCombo->addItem(tr("节点标量场"));
    mScalarFieldCombo->addItem(tr("单元标量场"));
    scalarLayout->addWidget(mScalarFieldCombo);
    connect(mScalarFieldCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FCPostProcessingSettingsWidget::onScalarFieldChanged);
    
    mainLayout->addWidget(scalarGroup);
    
    // 显示模式
    mDisplayGroup = new QGroupBox(tr("显示模式"), this);
    QVBoxLayout* displayLayout = new QVBoxLayout(mDisplayGroup);
    
    mDisplayModeCombo = new QComboBox(this);
    mDisplayModeCombo->addItem(tr("表面"));
    mDisplayModeCombo->addItem(tr("线框"));
    mDisplayModeCombo->addItem(tr("表面+边"));
    mDisplayModeCombo->addItem(tr("节点"));
    displayLayout->addWidget(mDisplayModeCombo);
    connect(mDisplayModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FCPostProcessingSettingsWidget::onDisplayModeChanged);
    
    mShowEdgesCheck = new QCheckBox(tr("显示边"), this);
    displayLayout->addWidget(mShowEdgesCheck);
    
    mShowNodesCheck = new QCheckBox(tr("显示节点"), this);
    displayLayout->addWidget(mShowNodesCheck);
    
    mainLayout->addWidget(mDisplayGroup);
    
    // 颜色映射
    mColorMapGroup = new QGroupBox(tr("颜色映射"), this);
    QVBoxLayout* colorLayout = new QVBoxLayout(mColorMapGroup);
    
    QLabel* colorMapTypeLabel = new QLabel(tr("颜色映射类型:"), this);
    colorLayout->addWidget(colorMapTypeLabel);
    
    mColorMapTypeCombo = new QComboBox(this);
    mColorMapTypeCombo->addItem(tr("彩虹色"));
    mColorMapTypeCombo->addItem(tr("自定义"));
    mColorMapTypeCombo->addItem(tr("灰度"));
    colorLayout->addWidget(mColorMapTypeCombo);
    connect(mColorMapTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FCPostProcessingSettingsWidget::onColorMapTypeChanged);
    
    // 颜色选择
    QHBoxLayout* colorButtonLayout = new QHBoxLayout();
    QLabel* minColorLabel = new QLabel(tr("最小值颜色:"), this);
    colorButtonLayout->addWidget(minColorLabel);
    
    mMinColorButton = new QPushButton(this);
    mMinColorButton->setFixedSize(50, 30);
    mMinColorButton->setStyleSheet(QString("background-color: %1").arg(mMinColor.name()));
    connect(mMinColorButton, &QPushButton::clicked, this, &FCPostProcessingSettingsWidget::onMinColorChanged);
    colorButtonLayout->addWidget(mMinColorButton);
    
    colorButtonLayout->addStretch();
    
    QLabel* maxColorLabel = new QLabel(tr("最大值颜色:"), this);
    colorButtonLayout->addWidget(maxColorLabel);
    
    mMaxColorButton = new QPushButton(this);
    mMaxColorButton->setFixedSize(50, 30);
    mMaxColorButton->setStyleSheet(QString("background-color: %1").arg(mMaxColor.name()));
    connect(mMaxColorButton, &QPushButton::clicked, this, &FCPostProcessingSettingsWidget::onMaxColorChanged);
    colorButtonLayout->addWidget(mMaxColorButton);
    
    colorLayout->addLayout(colorButtonLayout);
    
    // 数值范围
    QHBoxLayout* rangeLayout = new QHBoxLayout();
    mAutoRangeCheck = new QCheckBox(tr("自动范围"), this);
    mAutoRangeCheck->setChecked(true);
    rangeLayout->addWidget(mAutoRangeCheck);
    colorLayout->addLayout(rangeLayout);
    
    QHBoxLayout* minMaxLayout = new QHBoxLayout();
    QLabel* minLabel = new QLabel(tr("最小值:"), this);
    minMaxLayout->addWidget(minLabel);
    mMinValueSpin = new QDoubleSpinBox(this);
    mMinValueSpin->setRange(-1e10, 1e10);
    mMinValueSpin->setDecimals(3);
    mMinValueSpin->setEnabled(false);
    minMaxLayout->addWidget(mMinValueSpin);
    
    QLabel* maxLabel = new QLabel(tr("最大值:"), this);
    minMaxLayout->addWidget(maxLabel);
    mMaxValueSpin = new QDoubleSpinBox(this);
    mMaxValueSpin->setRange(-1e10, 1e10);
    mMaxValueSpin->setDecimals(3);
    mMaxValueSpin->setEnabled(false);
    minMaxLayout->addWidget(mMaxValueSpin);
    
    colorLayout->addLayout(minMaxLayout);
    
    connect(mAutoRangeCheck, &QCheckBox::toggled, this, [this](bool checked) {
        mMinValueSpin->setEnabled(!checked);
        mMaxValueSpin->setEnabled(!checked);
    });
    
    mainLayout->addWidget(mColorMapGroup);
    
    // 应用按钮
    QPushButton* applyButton = new QPushButton(tr("应用"), this);
    connect(applyButton, &QPushButton::clicked, this, &FCPostProcessingSettingsWidget::onApplySettings);
    mainLayout->addWidget(applyButton);
    
    mainLayout->addStretch();
}

void FCPostProcessingSettingsWidget::setPostProcessingID(IdType id)
{
    mCurrentPostProcessingID = id;
    mCurrentKernal = FCPostProcessingData::getInstance()->getPostProcessingKernalByID(id);
    updateInterface();
}

void FCPostProcessingSettingsWidget::updateInterface()
{
    if (!mCurrentKernal) {
        return;
    }
    
    // 更新颜色映射
    auto colorMap = mCurrentKernal->getColorMap();
    if (colorMap.first) {
        mColorMapTypeCombo->setCurrentIndex(1); // 自定义
        mMinColor = colorMap.second.first;
        mMaxColor = colorMap.second.second;
    } else {
        mColorMapTypeCombo->setCurrentIndex(0); // 彩虹色
    }
    updateColorButtons();
    
    // 更新标量场名称
    QString scalarFieldName = mCurrentKernal->getScalarFieldName();
    // 这里可以根据实际数据更新下拉框
}

void FCPostProcessingSettingsWidget::updateColorButtons()
{
    if (mMinColorButton) {
        mMinColorButton->setStyleSheet(QString("background-color: %1").arg(mMinColor.name()));
    }
    if (mMaxColorButton) {
        mMaxColorButton->setStyleSheet(QString("background-color: %1").arg(mMaxColor.name()));
    }
}

void FCPostProcessingSettingsWidget::onColorMapTypeChanged(int index)
{
    // 根据颜色映射类型启用/禁用颜色按钮
    bool enableCustom = (index == 1); // 自定义
    if (mMinColorButton) mMinColorButton->setEnabled(enableCustom);
    if (mMaxColorButton) mMaxColorButton->setEnabled(enableCustom);
}

void FCPostProcessingSettingsWidget::onMinColorChanged()
{
    QColor color = QColorDialog::getColor(mMinColor, this, tr("选择最小值颜色"));
    if (color.isValid()) {
        mMinColor = color;
        updateColorButtons();
    }
}

void FCPostProcessingSettingsWidget::onMaxColorChanged()
{
    QColor color = QColorDialog::getColor(mMaxColor, this, tr("选择最大值颜色"));
    if (color.isValid()) {
        mMaxColor = color;
        updateColorButtons();
    }
}

void FCPostProcessingSettingsWidget::onScalarFieldChanged(int index)
{
    Q_UNUSED(index);
    // 更新标量场显示
}

void FCPostProcessingSettingsWidget::onDisplayModeChanged(int index)
{
    Q_UNUSED(index);
    // 更新显示模式
}

void FCPostProcessingSettingsWidget::onApplySettings()
{
    if (!mCurrentKernal) {
        return;
    }
    
    // 应用颜色映射设置
    int colorMapType = mColorMapTypeCombo->currentIndex();
    if (colorMapType == 1) { // 自定义
        mCurrentKernal->setColorMap(true, mMinColor, mMaxColor);
    } else {
        // 使用默认颜色映射
        mCurrentKernal->setColorMap(false, QColor(), QColor());
    }
    
    // 应用标量场设置
    QString scalarFieldName = mScalarFieldCombo->currentText();
    mCurrentKernal->setScalarFieldName(scalarFieldName);
    
    qDebug() << "PostProcessing settings applied for ID:" << mCurrentPostProcessingID;
}

} // namespace FC

