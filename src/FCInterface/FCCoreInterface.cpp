/**
 * @file FCCoreInterface.cpp
 * @brief APP的核心接口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 所有接口都可以通过此接口获取，这个接口是最关键的接口
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCCoreInterface.h"
#include "FCUIInterface.h"
#include <QPointer>
#include "FCProjectInterface.h"

namespace FC {

FCCoreInterface::FCCoreInterface(QObject *parent)
    : QObject(parent)
{
    
}

FCCoreInterface::~FCCoreInterface()
{
    
}

/**
 * @brief 是否为工程路径
 * @return 
 */
bool FCCoreInterface::isProjectDirty() const
{
    FCProjectInterface* pi = getProjectInterface();
    if (pi) {
        // return pi->isDirty();
    }
    return false;
}

void FCCoreInterface::setProjectDirty(bool on)
{
    FCProjectInterface* pi = getProjectInterface();
    if (pi) {
        // pi->setModified(on);
    }
}

/**
 * @brief 获取应用的临时路径
 * @return 
 */
QDir FCCoreInterface::getTempDir() const
{
    return QDir(mTempDir.path());
}

} // namespace FC
