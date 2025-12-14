/**
 * @file FCExpandableSection.cpp
 * @brief 可展开/折叠的抽屉式控件
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCExpandableSection.h"
#include <QToolButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStyle>

namespace FC 
{

FCExpandableSection::FCExpandableSection(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    mHeaderButton = new QToolButton(this);
    mHeaderButton->setText(title);
    mHeaderButton->setCheckable(true);
    mHeaderButton->setChecked(false);
    mHeaderButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mHeaderButton->setArrowType(Qt::RightArrow);
    mHeaderButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mHeaderButton->setStyleSheet(
        "QToolButton {"
        "   background-color: rgb(223, 233, 245);"
        "   border: none;"
        "   padding: 6px;"
        "}"
        "QToolButton:hover {"
        "   background-color: rgb(223, 233, 245);"
        "}"
        "QToolButton:pressed {"
        "   background-color: rgb(223, 233, 245);"
        "}"
        "QToolButton:checked {"
        "   background-color: rgb(223, 233, 245);"
        "}"
    );
    
    mContentArea = new QWidget(this);
    mContentArea->setStyleSheet("background: rgb(245, 245, 245);");
    mContentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mContentArea->setMaximumHeight(0);  // 折叠状态
    mContentArea->setMinimumHeight(0);
    mContentArea->hide();
    
    // 动画
    mAnimationGroup = new QParallelAnimationGroup(this);
    mContentAnimation = new QPropertyAnimation(mContentArea, "maximumHeight");
    mContentAnimation->setDuration(150);
    mAnimationGroup->addAnimation(mContentAnimation);
    
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);
    mMainLayout->setSpacing(0);
    mMainLayout->addWidget(mHeaderButton);
    mMainLayout->addWidget(mContentArea);
    
    connect(mHeaderButton, &QToolButton::toggled, this, &FCExpandableSection::toggle);
}

void FCExpandableSection::setContentWidget(QWidget *w)
{
    if (!w) return;
    
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(8, 4, 8, 8);
    layout->addWidget(w);
    layout->addStretch();
    mContentArea->setLayout(layout);
    
    int h = w->sizeHint().height() + 20;
    mContentAnimation->setStartValue(0);
    mContentAnimation->setEndValue(h);
}

void FCExpandableSection::setExpanded(bool expanded)
{
    mHeaderButton->setChecked(expanded);
}

bool FCExpandableSection::isExpanded() const
{
    return mHeaderButton->isChecked();
}

void FCExpandableSection::toggle(bool expanded)
{
    mHeaderButton->setArrowType(expanded ? Qt::DownArrow : Qt::RightArrow);
    
    if (!mContentArea->layout()) {
        return;
    }
    
    int contentHeight = mContentArea->layout()->sizeHint().height() + 10;
    
    mContentAnimation->setStartValue(mContentArea->maximumHeight());
    mContentAnimation->setEndValue(expanded ? contentHeight : 0);
    
    if (expanded) {
        mContentArea->show();
    }
    
    mAnimationGroup->start();
    
    emit toggled(expanded);
}

} // namespace FC

