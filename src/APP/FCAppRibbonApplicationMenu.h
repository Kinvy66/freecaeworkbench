/******************************************************************************
 * File     : FCAppRibbonApplicationMenu.cpp
 * Brief    : ribbon application button 弹出的菜单
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
