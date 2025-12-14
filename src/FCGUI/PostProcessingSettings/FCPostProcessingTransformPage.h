/**
 * @file FCPostProcessingTransformPage.h
 * @brief 后处理坐标变换页面
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGTRANSFORMPAGE_H
#define FCPOSTPROCESSINGTRANSFORMPAGE_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCPostProcessingTransformPage;
}

namespace FC 
{
class FCGraphViewWindow;
class FCPostProcessingTransformPage : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
    
public:
    explicit FCPostProcessingTransformPage(FCGraphViewWindow* viewWindow, QWidget *parent = nullptr);
    ~FCPostProcessingTransformPage();
    
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
     * @brief 变换属性改变信号
     */
    void transformPropertyChanged(IdType postID);
    
private slots:
    void onTranslationChanged();
    void onScaleChanged();
    void onOrientationChanged();
    void onCenterPointChanged();
        
private:
    void init();
    void initConnections();
    void applySettings();
    void updateRenderWindow();
    
private:
    Ui::FCPostProcessingTransformPage *ui;
    FCGraphViewWindow* mViewWindow;
    IdType mCurrentPostID{0};
    
    // 变换属性
    double mTranslation[3]{0.0, 0.0, 0.0};
    double mScale[3]{1.0, 1.0, 1.0};
    double mOrientation[3]{0.0, 0.0, 0.0};
    double mCenterPoint[3]{1.0, 0.5, 3.0};
};

} // namespace FC

#endif // FCPOSTPROCESSINGTRANSFORMPAGE_H
