/**
 * @file FCAppRibbonApplicationMenu.h
 * @brief ribbon application button 弹出的菜单
 * @date 2025-10-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCAPPRIBBONAPPLICATIONMENU_H
#define FCAPPRIBBONAPPLICATIONMENU_H

#include "SARibbonMenu.h"

namespace FC 
{
class FCAppRibbonApplicationMenu : public SARibbonMenu
{
public:
    FCAppRibbonApplicationMenu(QWidget* parent = Q_NULLPTR);
};
} // namespace FC


#endif // FCAPPRIBBONAPPLICATIONMENU_H
