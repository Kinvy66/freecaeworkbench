/**
 * @file FCActionOperator.cpp
 * @brief action点击事件处理基类
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#include "FCActionOperator.h"

namespace FC 
{

FCActionOperator::~FCActionOperator()
{
    
}

bool FCActionOperator::actionTriggered()
{
    return true;
}

bool FCActionOperator::execGUI()
{
    return true;
}

bool FCActionOperator::execProfession()
{
    return true;
}

void FCActionOperator::preArgs()
{
    
}

} // namespace FC
