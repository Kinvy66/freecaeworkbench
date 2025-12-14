/**
 * @file FCPostProcessingDisplayPage.h
 * @brief 后处理显示页面
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGDISPLAYPAGE_H
#define FCPOSTPROCESSINGDISPLAYPAGE_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCPostProcessingDisplayPage;
}

namespace FC 
{
class FCGraphViewWindow;
class FCPostProcessingDisplayPage : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
    
public:
    explicit FCPostProcessingDisplayPage(FCGraphViewWindow* viewWindow, QWidget *parent = nullptr);
    ~FCPostProcessingDisplayPage();
    
    /**
     * @brief 设置当前编辑的后处理ID
     */
    void setPostProcessingID(IdType postID);
    
    /**
     * @brief 更新UI显示当前后处理的属性
     */
    void updateUIFromPostProcessing(IdType postID);
    
signals:
    /**
     * @brief 显示属性改变信号
     */
    void displayPropertyChanged(IdType postID);
    
private slots:
    void onDisplayFormChanged(int index);
    void onColorColumnChanged(int index);
    void onShowLegendClicked();
    void onEditColorClicked();
    void onTransparencyChanged(int value);
    void onPointSizeChanged(int value);
    void onLineWidthChanged(int value);
    void onShadingMethodChanged(int index);
    void onSpecularCoefficientChanged(int value);
    void onSpecularColorClicked();
    void onSpecularIntensityChanged(int value);
    void onAmbientCoefficientChanged(int value);
    void onDiffuseCoefficientChanged(int value);
    void onBoundaryColorClicked();
        
private:
    void init();
    void initConnections();
    void applySettings();
    void updateRenderWindow();
    void updateBoundaryColorDisplay();
    
private:
    Ui::FCPostProcessingDisplayPage *ui;
    FCGraphViewWindow* mViewWindow;
    IdType mCurrentPostID{0};
    
    // 显示属性
    int mDisplayForm{0};  // 0: 面, 1: 线框, 2: 点
    QString mColorColumn{"scalars"};
    bool mShowLegend{false};
    double mTransparency{1.0};
    int mPointSize{2};
    int mLineWidth{1};
    int mShadingMethod{0};  // 0: 平面着色, 1: Gouraud着色, 2: Phong着色
    double mSpecularCoefficient{0.0};
    QColor mSpecularColor{Qt::white};
    double mSpecularIntensity{100.0};
    double mAmbientCoefficient{0.0};
    double mDiffuseCoefficient{1.0};
    QColor mBoundaryColor{Qt::blue};
};

} // namespace FC

#endif // FCPOSTPROCESSINGDISPLAYPAGE_H
