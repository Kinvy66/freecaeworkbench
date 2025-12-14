/**
 * @file FCPostProcessingCoordinatesPage.h
 * @brief 后处理三维坐标页面
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGCOORDINATESPAGE_H
#define FCPOSTPROCESSINGCOORDINATESPAGE_H
#include "FCGuiAPI.h"
#include <QWidget>

namespace Ui {
class FCPostProcessingCoordinatesPage;
}

namespace FC 
{
class FCGraphViewWindow;
class FCPostProcessingCoordinatesPage : public QWidget
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
    
public:
    explicit FCPostProcessingCoordinatesPage(FCGraphViewWindow* viewWindow, QWidget *parent = nullptr);
    ~FCPostProcessingCoordinatesPage();
    
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
     * @brief 坐标属性改变信号
     */
    void coordinatesPropertyChanged(IdType postID);
    
private slots:
    void onShowCoordinatesToggled(bool checked);
        
private:
    void init();
    void initConnections();
    void applySettings();
    void updateRenderWindow();
    
private:
    Ui::FCPostProcessingCoordinatesPage *ui;
    FCGraphViewWindow* mViewWindow;
    IdType mCurrentPostID{0};
    
    // 坐标属性
    bool mShowCoordinates{false};
};

} // namespace FC

#endif // FCPOSTPROCESSINGCOORDINATESPAGE_H
