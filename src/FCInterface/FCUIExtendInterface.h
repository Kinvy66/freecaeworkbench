/******************************************************************************
 * File     : FCUIExtendInterface.h
 * Brief    : FCAppUIInterface下面的扩展模块
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCUIEXTENDINTERFACE_H
#define FCUIEXTENDINTERFACE_H
#include "FCInterfaceAPI.h"
#include "FCBaseInterface.h"

namespace FC 
{
class FCUIInterface;
class FCCoreInterface;
/**
 * @brief FCAppUIInterface下面的扩展模块
 *
 *
 */
class FCINTERFACE_API FCUIExtendInterface : public FCBaseInterface
{
    Q_OBJECT
public:
    FCUIExtendInterface(FCUIInterface* u);
    ~FCUIExtendInterface();
    //获取DAAppUIInterface
    FCUIInterface* ui() const;
    //发生语言变更时会调用此函数
    virtual void retranslateUi() = 0;
};
} // namespace FC

#endif // FCUIEXTENDINTERFACE_H
