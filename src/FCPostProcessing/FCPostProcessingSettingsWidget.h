/**
 * @file FCPostProcessingSettingsWidget.h
 * @brief 后处理显示设置窗口
 * @date 2025-12-15
 * @version V0.0.1
 * @details 参考COMSOL的后处理显示设置
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGSETTINGSWIDGET_H
#define FCPOSTPROCESSINGSETTINGSWIDGET_H

#include "FCPostProcessingAPI.h"
#include <QWidget>
#include <QColor>

class QComboBox;
class QPushButton;
class QDoubleSpinBox;
class QCheckBox;
class QGroupBox;

namespace FC 
{

class FCPostProcessingKernal;

class FCPOSTPROCESSING_API FCPostProcessingSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType = uint64_t;
    
public:
    explicit FCPostProcessingSettingsWidget(QWidget* parent = nullptr);
    ~FCPostProcessingSettingsWidget();
    
    /**
     * @brief 设置当前后处理ID
     * @param id 后处理ID
     */
    void setPostProcessingID(IdType id);
    
    /**
     * @brief 更新界面显示
     */
    void updateInterface();
    
private slots:
    /**
     * @brief 颜色映射类型改变
     */
    void onColorMapTypeChanged(int index);
    
    /**
     * @brief 最小颜色改变
     */
    void onMinColorChanged();
    
    /**
     * @brief 最大颜色改变
     */
    void onMaxColorChanged();
    
    /**
     * @brief 标量场选择改变
     */
    void onScalarFieldChanged(int index);
    
    /**
     * @brief 显示模式改变
     */
    void onDisplayModeChanged(int index);
    
    /**
     * @brief 应用设置
     */
    void onApplySettings();
    
private:
    /**
     * @brief 初始化界面
     */
    void initUI();
    
    /**
     * @brief 更新颜色按钮显示
     */
    void updateColorButtons();
    
private:
    IdType mCurrentPostProcessingID{0};
    FCPostProcessingKernal* mCurrentKernal{nullptr};
    
    // UI控件
    QComboBox* mColorMapTypeCombo{nullptr};
    QPushButton* mMinColorButton{nullptr};
    QPushButton* mMaxColorButton{nullptr};
    QComboBox* mScalarFieldCombo{nullptr};
    QComboBox* mDisplayModeCombo{nullptr};
    QDoubleSpinBox* mMinValueSpin{nullptr};
    QDoubleSpinBox* mMaxValueSpin{nullptr};
    QCheckBox* mAutoRangeCheck{nullptr};
    QCheckBox* mShowEdgesCheck{nullptr};
    QCheckBox* mShowNodesCheck{nullptr};
    QGroupBox* mColorMapGroup{nullptr};
    QGroupBox* mDisplayGroup{nullptr};
    
    QColor mMinColor{QColor(0, 0, 255)};  // 蓝色
    QColor mMaxColor{QColor(255, 0, 0)};  // 红色
};

} // namespace FC

#endif // FCPOSTPROCESSINGSETTINGSWIDGET_H

