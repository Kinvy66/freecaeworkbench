/**
 * @file FCRibbonAreaInterface.h
 * @brief 管理AppRibbon区域的相关操作
 * @date 2025-10-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
