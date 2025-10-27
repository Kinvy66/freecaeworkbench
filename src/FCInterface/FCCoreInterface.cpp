/******************************************************************************
 * File     : FCCoreInterface.cpp
 * Brief    : APP 的核心接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
