/**
 * @file FCPostProcessingDisplaySettingsWidget.cpp
 * @brief 后处理显示属性设置窗口
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingDisplaySettingsWidget.h"
#include "ui_FCPostProcessingDisplaySettingsWidget.h"
#include "FCPostProcessingDisplayPage.h"
#include "FCPostProcessingTransformPage.h"
#include "FCPostProcessingCoordinatesPage.h"
#include "FCGraphViewWindow.h"
#include "FCExpandableSection.h"
#include <QScrollArea>
#include <QVBoxLayout>

namespace FC 
{

FCPostProcessingDisplaySettingsWidget::FCPostProcessingDisplaySettingsWidget(FCGraphViewWindow* viewWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FCPostProcessingDisplaySettingsWidget)
    , mViewWindow(viewWindow)
{
    ui->setupUi(this);
    
    // 创建三个页面
    mDisplayPage = new FCPostProcessingDisplayPage(viewWindow, this);
    mTransformPage = new FCPostProcessingTransformPage(viewWindow, this);
    mCoordinatesPage = new FCPostProcessingCoordinatesPage(viewWindow, this);
    
    // 创建抽屉式布局
    setupExpandableSections();
    
    init();
    initConnections();
}

FCPostProcessingDisplaySettingsWidget::~FCPostProcessingDisplaySettingsWidget()
{
    delete ui;
}

void FCPostProcessingDisplaySettingsWidget::setPostProcessingID(IdType postID)
{
    mCurrentPostID = postID;
    updateUIFromPostProcessing(postID);
}

void FCPostProcessingDisplaySettingsWidget::updateUIFromPostProcessing(IdType postID)
{
    mCurrentPostID = postID;
    
    // 更新三个页面的ID
    if (mDisplayPage) {
        mDisplayPage->setPostProcessingID(postID);
    }
    if (mTransformPage) {
        mTransformPage->setPostProcessingID(postID);
    }
    if (mCoordinatesPage) {
        mCoordinatesPage->setPostProcessingID(postID);
    }
}

void FCPostProcessingDisplaySettingsWidget::setupExpandableSections()
{
    // 获取滚动区域的布局（UI文件中已创建）
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!mainLayout) {
        qWarning() << "FCPostProcessingDisplaySettingsWidget: Could not find layout in scrollAreaWidgetContents";
        return;
    }
    
    // 创建"显示"抽屉
    mExpandableDisplay = new FCExpandableSection(tr("显示"), this);
    mExpandableDisplay->setContentWidget(mDisplayPage);
    mainLayout->addWidget(mExpandableDisplay);
    
    // 创建"坐标变换"抽屉
    mExpandableTransform = new FCExpandableSection(tr("坐标变换"), this);
    mExpandableTransform->setContentWidget(mTransformPage);
    mainLayout->addWidget(mExpandableTransform);
    
    // 创建"三维坐标"抽屉
    mExpandableCoordinates = new FCExpandableSection(tr("三维坐标"), this);
    mExpandableCoordinates->setContentWidget(mCoordinatesPage);
    mainLayout->addWidget(mExpandableCoordinates);
    
    // 添加弹性空间
    mainLayout->addStretch();
    
    // 默认展开"显示"抽屉
    mExpandableDisplay->setExpanded(true);
}

void FCPostProcessingDisplaySettingsWidget::init()
{
    // 初始化工作由各个页面类完成
}

void FCPostProcessingDisplaySettingsWidget::initConnections()
{
    // 连接三个页面的信号到主Widget的信号
    if (mDisplayPage) {
        connect(mDisplayPage, &FCPostProcessingDisplayPage::displayPropertyChanged,
                this, &FCPostProcessingDisplaySettingsWidget::onDisplayPropertyChanged);
    }
    
    if (mTransformPage) {
        connect(mTransformPage, &FCPostProcessingTransformPage::transformPropertyChanged,
                this, &FCPostProcessingDisplaySettingsWidget::onTransformPropertyChanged);
    }
    
    if (mCoordinatesPage) {
        connect(mCoordinatesPage, &FCPostProcessingCoordinatesPage::coordinatesPropertyChanged,
                this, &FCPostProcessingDisplaySettingsWidget::onCoordinatesPropertyChanged);
    }
    
    // 应用按钮
    // connect(ui->pushButtonApply, &QPushButton::clicked,
    //         this, &FCPostProcessingDisplaySettingsWidget::onApplyClicked);
}

void FCPostProcessingDisplaySettingsWidget::onDisplayPropertyChanged(IdType postID)
{
    // 转发信号
    emit displayPropertyChanged(postID);
}

void FCPostProcessingDisplaySettingsWidget::onTransformPropertyChanged(IdType postID)
{
    // 转发信号
    emit displayPropertyChanged(postID);
}

void FCPostProcessingDisplaySettingsWidget::onCoordinatesPropertyChanged(IdType postID)
{
    // 转发信号
    emit displayPropertyChanged(postID);
}

void FCPostProcessingDisplaySettingsWidget::onApplyClicked()
{
    // 应用按钮的功能由各个页面类自己处理
    // 这里只需要发出信号通知外部
    emit displayPropertyChanged(mCurrentPostID);
}

} // namespace FC

