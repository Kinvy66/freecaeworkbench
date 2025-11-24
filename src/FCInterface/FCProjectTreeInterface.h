/**
 * @file FCProjectTreeInterface.h
 * @brief 工程树接口
 * @date 2025-11-13
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPROJECTTREEINTERFACE_H
#define FCPROJECTTREEINTERFACE_H
#include "FCInterfaceAPI.h"
#include "FCBaseInterface.h"

namespace FC 
{

class FCCoreInterface;
class FCUIInterface;
class FCINTERFACE_API FCProjectTreeInterface : public FCBaseInterface
{
    Q_OBJECT
    
    FC_DECLARE_PRIVATE(FCProjectTreeInterface)
    
public:
    FCProjectTreeInterface(FCUIInterface* u);
    ~FCProjectTreeInterface();
    // 添加树节点
    void appendItem();
    
    // 设置树的根
    void setRoot();
    
};
} // namespace FC



#endif // FCPROJECTTREEINTERFACE_H
