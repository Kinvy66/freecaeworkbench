/**
 * @file FCAbstractArchiveTask.cpp
 * @brief 针对@sa FCZipArchiveThreadWrapper 的任务
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */

#include "FCAbstractArchiveTask.h"
#include <QMetaType>

namespace FC 
{

FCAbstractArchiveTask::FCAbstractArchiveTask()
{
    
}

FCAbstractArchiveTask::~FCAbstractArchiveTask()
{
    
}

int FCAbstractArchiveTask::getCode() const
{
    return mCode;
}

void FCAbstractArchiveTask::setCode(int code)
{
    mCode = code;
}

QString FCAbstractArchiveTask::getName() const
{
    return mName;
}

void FCAbstractArchiveTask::setName(const QString &name)
{
    mName = name;
}

QString FCAbstractArchiveTask::getDescribe() const
{
    return mDescribe;
}

void FCAbstractArchiveTask::setDescribe(const QString &describe)
{
    mDescribe = describe;    
}

} // namespace FC

FC_AUTO_REGISTER_META_TYPE(FC::FCAbstractArchiveTask::Mode)
FC_AUTO_REGISTER_META_TYPE(std::shared_ptr< FC::FCAbstractArchiveTask >)
