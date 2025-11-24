/**
 * @file FCProjectTreeInterface.cpp
 * @brief 工程树接口
 * @date 2025-11-13
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCProjectTreeInterface.h"
#include "FCUIInterface.h"

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================
using namespace FC;


class FCProjectTreeInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCProjectTreeInterface)
public:
    PrivateData(FCProjectTreeInterface* p);
    // todo 添加其他需要隐藏的属性和方法
};

FCProjectTreeInterface::PrivateData::PrivateData(FCProjectTreeInterface *p)
    : q_ptr(p)
{
    
}

FCProjectTreeInterface::FCProjectTreeInterface(FCUIInterface *u)
    : FCBaseInterface(u->core(), u), FC_PIMPL_CONSTRUCT
{
    
}

FCProjectTreeInterface::~FCProjectTreeInterface()
{
    
}


