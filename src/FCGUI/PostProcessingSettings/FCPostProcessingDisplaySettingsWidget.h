/**
 * @file FCPostProcessingDisplaySettingsWidget.h
 * @brief 后处理显示属性设置窗口
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGDISPLAYSETTINGSWIDGET_H
#define FCPOSTPROCESSINGDISPLAYSETTINGSWIDGET_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCPostProcessingDisplaySettingsWidget;
}

namespace FC 
{
class FCGraphViewWindow;
class FCExpandableSection;
class FCPostProcessingDisplayPage;
class FCPostProcessingTransformPage;
class FCPostProcessingCoordinatesPage;
class FCPostProcessingDisplaySettingsWidget : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
    
public:
    explicit FCPostProcessingDisplaySettingsWidget(FCGraphViewWindow* viewWindow, QWidget *parent = nullptr);
    ~FCPostProcessingDisplaySettingsWidget();
    
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
    void onApplyClicked();
    void onDisplayPropertyChanged(IdType postID);
    void onTransformPropertyChanged(IdType postID);
    void onCoordinatesPropertyChanged(IdType postID);
        
private:
    void init();
    void initConnections();
    void setupExpandableSections();
    
private:
    Ui::FCPostProcessingDisplaySettingsWidget *ui;
    FCGraphViewWindow* mViewWindow;
    IdType mCurrentPostID{0};
    
    // 三个页面
    FCPostProcessingDisplayPage* mDisplayPage{nullptr};
    FCPostProcessingTransformPage* mTransformPage{nullptr};
    FCPostProcessingCoordinatesPage* mCoordinatesPage{nullptr};
    
    // 抽屉式控件
    FCExpandableSection* mExpandableDisplay{nullptr};
    FCExpandableSection* mExpandableTransform{nullptr};
    FCExpandableSection* mExpandableCoordinates{nullptr};
};

} // namespace FC

#endif // FCPOSTPROCESSINGDISPLAYSETTINGSWIDGET_H


