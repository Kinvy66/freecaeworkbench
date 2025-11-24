/**
 * @file FCUIExtendInterface.h
 * @brief FCAppUIInterface下面的扩展模块
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
