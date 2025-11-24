/**
 * @file FCGraphWindowBase.cpp
 * @brief 绘图窗口基类
 * @date 2025-11-22
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGraphWindowBase.h"

namespace FC 
{

FCGraphWindowBase::FCGraphWindowBase(int proID, GraphWindowType type, QWidget *parent)
{
    
}

FCGraphWindowBase::~FCGraphWindowBase()
{
    
}

/**
 * @brief 获取当前绘图窗口类型
 * @return 
 */
GraphWindowType FCGraphWindowBase::getGraphWindowType() const
{
    return mGraphWindowType;
}

/**
 * @brief 保存图片
 * @param fileName
 * @param width
 * @param heigh
 * @param showDlg
 */
void FCGraphWindowBase::saveImage(QString fileName, int width, int heigh, bool showDlg)
{

}

/**
 * @brief 获取工程id
 * @return 
 */
int FCGraphWindowBase::getID()
{
    return mProjectId;
}

/**
 * @brief 设置视角
 * @param view
 */
void FCGraphWindowBase::setView(QString view)
{
    if (view.toLower() == "fit")
        fitView();
    else if (view.toLower() == "xplus")
        setViewXPlus();
    else if (view.toLower() == "xminus")
        setViewXMiuns();
    else if (view.toLower() == "yplus")
        setViewYPlus();
    else if (view.toLower() == "yminus")
        setViewYMiuns();
    else if (view.toLower() == "zplus")
        setViewZPlus();
    else if (view.toLower() == "zminus")
        setViewZMiuns();
}

/**
 * @brief 设置视角
 * @param x1
 * @param x2
 * @param x3
 * @param y1
 * @param y2
 * @param y3
 * @param z1
 * @param z2
 * @param z3
 */
void FCGraphWindowBase::setViewValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3)
{
    
}

/**
 * @brief 设置颜色
 * @param color1
 * @param color2
 */
void FCGraphWindowBase::setBackGround(QColor color1, QColor color2)
{
    
}

/**
 * @brief 字符串形式获取窗口类型
 * @return 
 */
QString FCGraphWindowBase::getStringGraphWindowType()
{
    QString type;
    switch (mGraphWindowType)
    {
    case GraphWindowType::UnDefined:
        break;
    case GraphWindowType::PreWindows:
        type = "PreWindow";
        break;
    case GraphWindowType::RealTime:
        type = "RealTime";
        break;
    case GraphWindowType::Post2D:
        type = "Post2D";
        break;
    case GraphWindowType::Post3D:
        type = "Post3D";
        break;
    default:
        break;
    }
    return type;
}

void FCGraphWindowBase::fitView()
{
    
}

void FCGraphWindowBase::setViewXPlus()
{
    
}

void FCGraphWindowBase::setViewXMiuns()
{
    
}

void FCGraphWindowBase::setViewYPlus()
{
    
}

void FCGraphWindowBase::setViewYMiuns()
{
    
}

void FCGraphWindowBase::setViewZPlus()
{
    
}

void FCGraphWindowBase::setViewZMiuns()
{
    
}

void FCGraphWindowBase::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "base press event";
    QWidget::keyPressEvent(e);
}

void FCGraphWindowBase::keyReleaseEvent(QKeyEvent *e)
{
    qDebug() << "base release event";
    QWidget::keyReleaseEvent(e);
}

void FCGraphWindowBase::setDisplay(QString m)
{
    
}

void FCGraphWindowBase::setSelectModel(int mode)
{
    Q_UNUSED(mode)
}

void FCGraphWindowBase::updateGraphOption()
{
    
}

} // namespace FC
