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
#include "FCRibbonAreaInterface.h"
#include "SARibbonMainWindow.h"
#include "SARibbonCategory.h"
#include "SARibbonBar.h"
#include "SARibbonMainWindow.h"
#include "SARibbonPanel.h"

namespace FC 
{
class FCRibbonAreaInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCRibbonAreaInterface)
public:
    PrivateData(FCRibbonAreaInterface* p);
    
public:
    FCUIInterface* mUiInterface { nullptr };  // 不调用父类的parent，这样是为了不进行qobject_cast，加快效率
};

//===================================================
// FCAppRibbonAreaInterfacePrivate
//===================================================
FCRibbonAreaInterface::PrivateData::PrivateData(FCRibbonAreaInterface* p) : q_ptr(p)
{
}

/**
 * @brief 构造函数，必须在主窗口之后构造
 * @note 此接口的生命周期跟随SARibbonMainWindow，FCAppRibbonAreaInterface将作为SARibbonMainWindow的子对象
 * @param mainwindow
 */
FCRibbonAreaInterface::FCRibbonAreaInterface(FCUIInterface* u)
    : FCUIExtendInterface(u), FC_PIMPL_CONSTRUCT
{
    d_ptr->mUiInterface = u;
}

FCRibbonAreaInterface::~FCRibbonAreaInterface()
{
}

/**
 * @brief 获取ribbonbar
 * @return
 */
SARibbonBar* FCRibbonAreaInterface::ribbonBar() const
{
    return (d_ptr->mUiInterface->mainWindow()->ribbonBar());
}

/**
 * @brief 获取所有标签
 * @return
 */
QList< SARibbonCategory* > FCRibbonAreaInterface::getCategorys() const
{
    return (d_ptr->mUiInterface->mainWindow()->ribbonBar()->categoryPages());
}

/**
 * @brief 通过obj-name获取Category
 * @note 运行复杂度为O(n)
 * @param objname
 * @return 如果没找到，会返回nullptr
 */
SARibbonCategory* FCRibbonAreaInterface::getCategoryByObjectName(const QString& objname) const
{
    QList< SARibbonCategory* > categorys = getCategorys();
    for (SARibbonCategory* c : qAsConst(categorys)) {
        if (c) {
            if (c->objectName() == objname) {
                return c;
            }
        }
    }
    return nullptr;
}

/**
 * @brief 通过obj-name获取pannel(O(n))
 * @note 运行复杂度为O(n)
 * @param objname
 * @return 如果没找到，会返回nullptr
 */
SARibbonPanel* FCRibbonAreaInterface::getPannelByObjectName(const QString& objname) const
{
    QList< SARibbonCategory* > categorys = getCategorys();
    for (SARibbonCategory* category : qAsConst(categorys)) {
        QList< SARibbonPanel* > pannels = category->panelList();
        for (SARibbonPanel* pannel : qAsConst(pannels)) {
            if (pannel) {
                if (pannel->objectName() == objname) {
                    return pannel;
                }
            }
        }
    }
    return nullptr;
}

} // namespace FC
