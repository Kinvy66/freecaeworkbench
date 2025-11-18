/******************************************************************************
 * File     : FCStatusBar.h
 * Brief    : 状态栏
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-14
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCSTATUSBAR_H
#define FCSTATUSBAR_H

#include <QStatusBar>

namespace FC 
{
class FCStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    FCStatusBar(QWidget* par = nullptr);
};
} // namespace FC



#endif // FCSTATUSBAR_H
