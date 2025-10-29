/******************************************************************************
 * File     : FCRibbonAreaInterface.h
 * Brief    : 这个接口管理了AppRibbon区域的相关操作
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCRIBBONAREAINTERFACE_H
#define FCRIBBONAREAINTERFACE_H
#include "FCInterfaceAPI.h"
#include "FCGlobals.h"
#include "FCUIInterface.h"
#include "FCUIExtendInterface.h"
class SARibbonMainWindow;
class SARibbonBar;
class SARibbonCategory;
class SARibbonPanel;

namespace FC 
{
class FCINTERFACE_API FCRibbonAreaInterface : public FCUIExtendInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCRibbonAreaInterface)
public:
    FCRibbonAreaInterface(FCUIInterface* u);
    ~FCRibbonAreaInterface();
    
public:
    // 针对ribbon的操作
    SARibbonBar* ribbonBar() const;
    
    // 获取所有的标签
    QList< SARibbonCategory* > getCategorys() const;
    
    // 通过obj-name获取Category(O(n))
    SARibbonCategory* getCategoryByObjectName(const QString& objname) const;
    
    // 通过obj-name获取pannel(O(n))
    SARibbonPanel* getPannelByObjectName(const QString& objname) const;
};
} // namespace FC

#endif // FCRIBBONAREAINTERFACE_H
