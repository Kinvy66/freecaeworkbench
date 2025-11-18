#include "FCProjectInterface.h"
#include <QFileInfo>
#include <QSysInfo>
// #include "FCWorkFlowOperateWidget.h"
// #include "FCStringUtil.h"
// #include "FCXmlHelper.h"
// #include "FCQtContainerUtil.hpp"
#include "FCDataManagerInterface.h"
#include "FCDockingAreaInterface.h"

namespace FC 
{
//===================================================
// DAProjectInterfacePrivate
//===================================================
class FCProjectInterface::PrivateData
{
    FC_DECLARE_PUBLIC(FCProjectInterface)
public:
    PrivateData(FCProjectInterface* p);
    // 存在路径
    bool isHaveProjectFilePath() const;
    
public:
    bool mIsDirty { false };  ///< 脏标识
    FCDockingAreaInterface* mDockingArea { nullptr };
    // DAWorkFlowOperateWidget* mWorkFlowOperateWidget { nullptr };
    FCDataManagerInterface* mDataManagerInterface { nullptr };
    QFileInfo mProjectFileInfo;  ///< 记录工程文件信息
    
    static QString s_suffix;  ///< 工程文件后缀
};

/**
 * @brief 工程文件默认后缀
 */
QString FCProjectInterface::PrivateData::s_suffix = QString("fcpro");

FCProjectInterface::PrivateData::PrivateData(FCProjectInterface* p) : q_ptr(p)
{
}

bool FCProjectInterface::PrivateData::isHaveProjectFilePath() const
{
    return mProjectFileInfo.isFile();
}

//===================================================
// FCProjectInterface
//===================================================
FCProjectInterface::FCProjectInterface(FCCoreInterface* c, QObject* par)
    : FCBaseInterface(c, par), FC_PIMPL_CONSTRUCT
{
}

FCProjectInterface::~FCProjectInterface()
{
}

bool FCProjectInterface::isEmpty() const
{
    return !(d_ptr->isHaveProjectFilePath());
}

FCDockingAreaInterface* FCProjectInterface::getDockingAreaInterface() const
{
    return d_ptr->mDockingArea;
}

void FCProjectInterface::setDockingAreaInterface(FCDockingAreaInterface* dock)
{
    d_ptr->mDockingArea = dock;
}

/**
 * @brief 设置数据管理接口
 * @param d
 */
void FCProjectInterface::setDataManagerInterface(FCDataManagerInterface* d)
{
    d_ptr->mDataManagerInterface = d;
}

/**
 * @brief 获取数据管理接口
 * @return
 */
FCDataManagerInterface* FCProjectInterface::getDataManagerInterface()
{
    return d_ptr->mDataManagerInterface;
}

/**
 * @brief 获取工程名
 *
 * 返回工程的文件名(不含后缀)
 * @return 如果没有设置工程，将返回空字符串
 */
QString FCProjectInterface::getProjectBaseName() const
{
    if (!d_ptr->isHaveProjectFilePath()) {
        return QString();
    }
    return (d_ptr->mProjectFileInfo.baseName());
}

/**
 * @brief 获取工程路径
 *
 * @sa setProjectPath
 * @return 如果没有设置工程，将返回空字符串
 */
QString FCProjectInterface::getProjectDir() const
{
    if (!d_ptr->isHaveProjectFilePath()) {
        return QString();
    }
    return d_ptr->mProjectFileInfo.absolutePath();
}

/**
 * @brief FCProjectInterface::getProjectFilePath
 * @note 注意这个工程路径是工程文件的路径，并不是工作区的路径，但设置工程路径会把工作区设置到当前目录下
 * @return
 */
QString FCProjectInterface::getProjectFilePath() const
{
    if (!d_ptr->isHaveProjectFilePath()) {
        return QString();
    }
    return d_ptr->mProjectFileInfo.absoluteFilePath();
}

/**
 * @brief 设置工程路径
 * @param projectPath
 * @note 注意这个工程路径是工程文件的路径，并不是工作区的路径，但设置工程路径会把工作区设置到当前目录下
 */
void FCProjectInterface::setProjectPath(const QString& projectPath)
{
    d_ptr->mProjectFileInfo.setFile(projectPath);
}

/**
 * @brief 获取工作区
 * @note 工程文件所在目录定义为工作区
 * @return 如果没有设置工程，将返回空字符串
 */
QString FCProjectInterface::getWorkingDirectory() const
{
    if (!d_ptr->isHaveProjectFilePath()) {
        return QString();
    }
    return d_ptr->mProjectFileInfo.absolutePath();
}
/**
 * @brief 工程是否脏
 * @return
 */
bool FCProjectInterface::isDirty() const
{
    return d_ptr->mIsDirty;
}

/**
 * @brief 清空工程
 */
void FCProjectInterface::clear()
{
    setModified(false);
    d_ptr->mProjectFileInfo = QFileInfo();
    Q_EMIT projectIsCleaned();
}

/**
 * @brief 工程文件的版本,版本组成有大版本.小版本.小小版本组成，例如1.0.0
 * @return
 */
QVersionNumber FCProjectInterface::getProjectVersion()
{
    static QVersionNumber s_version = QVersionNumber(1, 3, 0);
    return s_version;
}

/**
 * @brief 是否繁忙，正在保存文件过程中会为繁忙状态
 * @return
 */
bool FCProjectInterface::isBusy() const
{
    return false;
}

/**
 * @brief 获取工程文件的后缀
 * @return
 */
QString FCProjectInterface::getProjectFileSuffix()
{
    return FCProjectInterface::PrivateData::s_suffix;
}

/**
 * @brief 设置工程文件的后缀
 * @param f
 * @return
 */
void FCProjectInterface::setProjectFileSuffix(const QString& f)
{
    FCProjectInterface::PrivateData::s_suffix = f;
}

/**
 * @brief 设置为dirty
 * @param on
 */
void FCProjectInterface::setModified(bool on)
{
    if (on != d_ptr->mIsDirty) {
        d_ptr->mIsDirty = on;
        Q_EMIT dirtyStateChanged(on);
    }
}

} // namespace FC


