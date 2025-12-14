/**
 * @file FCPostProcessingCoordinatesPage.cpp
 * @brief 后处理三维坐标页面
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingCoordinatesPage.h"
#include "ui_FCPostProcessingCoordinatesPage.h"
#include "FCGraphViewWindow.h"
#include "FCGraph3DWindow.h"

namespace FC 
{

FCPostProcessingCoordinatesPage::FCPostProcessingCoordinatesPage(FCGraphViewWindow* viewWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCPostProcessingCoordinatesPage)
    , mViewWindow(viewWindow)
{
    ui->setupUi(this);
    init();
    initConnections();
}

FCPostProcessingCoordinatesPage::~FCPostProcessingCoordinatesPage()
{
    delete ui;
}

void FCPostProcessingCoordinatesPage::setPostProcessingID(IdType postID)
{
    mCurrentPostID = postID;
    updateUIFromPostProcessing(postID);
}

void FCPostProcessingCoordinatesPage::updateUIFromPostProcessing(IdType postID)
{
    mCurrentPostID = postID;
    
    if (!mViewWindow || postID == 0) {
        return;
    }
    
    // 检查坐标显示状态
    FCGraph3DWindow* graph3D = dynamic_cast<FCGraph3DWindow*>(mViewWindow);
    if (graph3D) {
        mShowCoordinates = graph3D->isAxesVisible();
        ui->checkBoxShowCoordinates->setChecked(mShowCoordinates);
    }
}

void FCPostProcessingCoordinatesPage::init()
{
    // 初始化显示坐标复选框
    ui->checkBoxShowCoordinates->setChecked(false);
}

void FCPostProcessingCoordinatesPage::initConnections()
{
    // 显示坐标
    connect(ui->checkBoxShowCoordinates, &QCheckBox::toggled,
            this, &FCPostProcessingCoordinatesPage::onShowCoordinatesToggled);
}

void FCPostProcessingCoordinatesPage::onShowCoordinatesToggled(bool checked)
{
    mShowCoordinates = checked;
    applySettings();
}

void FCPostProcessingCoordinatesPage::applySettings()
{
    updateRenderWindow();
    emit coordinatesPropertyChanged(mCurrentPostID);
}

void FCPostProcessingCoordinatesPage::updateRenderWindow()
{
    if (!mViewWindow) return;
    
    FCGraph3DWindow* graph3D = dynamic_cast<FCGraph3DWindow*>(mViewWindow);
    if (!graph3D) return;
    
    // 更新坐标轴显示
    graph3D->showAxes(mShowCoordinates);
    
    // 重新渲染
    mViewWindow->reRender();
}

} // namespace FC
