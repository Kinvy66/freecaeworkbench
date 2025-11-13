/******************************************************************************
 * File     : FCProjectTreeInterface.cpp
 * Brief    : 工程树接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
