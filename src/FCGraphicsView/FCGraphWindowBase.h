/**
 * @file FCGraphWindowBase.h
 * @brief 绘图窗口基类
 * @date 2025-11-22
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGRAPHWINDOWBASE_H
#define FCGRAPHWINDOWBASE_H

#include <QWidget>
#include "FCGraphicsViewGlobal.h"


namespace FC 
{
class FCGRAPHICSVIEW_API FCGraphWindowBase : public QWidget
{
    Q_OBJECT
public:
    FCGraphWindowBase(int proID, QWidget* parent=nullptr);
    virtual ~FCGraphWindowBase() = 0;
    
    //获取类型
    GraphWindowType getGraphWindowType() const;
    //保存图片
    virtual void saveImage(QString fileName, int width, int heigh, bool showDlg);
    //获取ID
    int getID();
    //设置视角
    virtual void setView(QString view);
    virtual void setViewValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3); //;liu
    // virtual void setViewPreValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3);//;liu
    //设置背景颜色
    virtual void setBackGround(QColor color1, QColor color2);
    //字符串形式获取窗口类型
    QString getStringGraphWindowType();
    
signals:
    void showGraphRange(double, double);
    
private:
    virtual void fitView();
    virtual void setViewXPlus();
    virtual void setViewXMiuns();
    virtual void setViewYPlus();
    virtual void setViewYMiuns();
    virtual void setViewZPlus();
    virtual void setViewZMiuns();
    
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent *e) override;
    
private slots:
    virtual void setDisplay(QString m);
    // virtual void setGeometryDisplay(QString m);
    virtual void setSelectModel(int mode);
    virtual void updateGraphOption();
    
protected:
    int mProjectId{-1};
    GraphWindowType mGraphWindowType{GraphWindowType::UnDefined};
};
} // namespace FC


#endif // FCGRAPHWINDOWBASE_H
