/**
 * @file FCExpandableSection.h
 * @brief 可展开/折叠的抽屉式控件
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCEXPANDABLESECTION_H
#define FCEXPANDABLESECTION_H
#include "FCUtilsAPI.h"
#include <QWidget>


class QToolButton;
class QPropertyAnimation;
class QParallelAnimationGroup;
class QVBoxLayout;

namespace FC 
{

/**
 * @brief 可展开/折叠的抽屉式控件
 * 
 * 用于创建可展开和折叠的内容区域，带有动画效果
 */
class FCUTILS_API FCExpandableSection : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param title 标题文本
     * @param parent 父控件
     */
    explicit FCExpandableSection(const QString &title, QWidget *parent = nullptr);
    
    /**
     * @brief 设置内容控件
     * @param w 要显示的内容控件
     */
    void setContentWidget(QWidget *w);
    
    /**
     * @brief 设置是否展开
     * @param expanded true表示展开，false表示折叠
     */
    void setExpanded(bool expanded);
    
    /**
     * @brief 获取是否展开
     * @return true表示展开，false表示折叠
     */
    bool isExpanded() const;
    
signals:
    /**
     * @brief 展开/折叠状态改变时发出的信号
     * @param expanded 是否展开
     */
    void toggled(bool expanded);
    
private slots:
    void toggle(bool expanded);
    
private:
    QToolButton* mHeaderButton;
    QWidget* mContentArea;
    QPropertyAnimation* mContentAnimation;
    QParallelAnimationGroup* mAnimationGroup;
    QVBoxLayout* mMainLayout;
};

} // namespace FC

#endif // FCEXPANDABLESECTION_H


