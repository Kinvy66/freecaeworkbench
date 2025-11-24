/**
 * @file FCStatusBar.h
 * @brief 状态栏
 * @date 2025-11-14
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
