/**
 * @file FCModelBuilderWidget.h
 * @brief 模型构建窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMODELBUILDERWIDGET_H
#define FCMODELBUILDERWIDGET_H
#include "FCGuiAPI.h"
#include <QWidget>
#include <QList>

namespace FC 
{
class FCTree;
class FCTreeItem;
class FCProjectTree;

class FCGUI_API FCModelBuilderWidget : public QWidget
{
    Q_OBJECT
public:
    FCModelBuilderWidget(QWidget* parent = nullptr);
    ~FCModelBuilderWidget();
    
signals:
    
private:
    // 构建空白工程的树形结构
    void buildBlankProject();
    
private:
    
    FCProjectTree* mProjectTree;
};

} // namespace FC

#endif // FCMODELBUILDERWIDGET_H
