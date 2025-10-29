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
    // DADockingAreaInterface* mDockingArea { nullptr };
    // DAWorkFlowOperateWidget* mWorkFlowOperateWidget { nullptr };
    // DADataManagerInterface* mDataManagerInterface { nullptr };
    // QFileInfo mProjectFileInfo;  ///< 记录工程文件信息
    
    // static QString s_suffix;  ///< 工程文件后缀
};

/**
 * @brief 工程文件默认后缀
 */
// QString FCProjectInterface::PrivateData::s_suffix = QString("asproj");

FCProjectInterface::PrivateData::PrivateData(FCProjectInterface* p) : q_ptr(p)
{
}

bool FCProjectInterface::PrivateData::isHaveProjectFilePath() const
{
    // return mProjectFileInfo.isFile();
    return true;
}

//===================================================
// DAProjectInterface
//===================================================
FCProjectInterface::FCProjectInterface(FCCoreInterface* c, QObject* par)
    : FCBaseInterface(c, par), FC_PIMPL_CONSTRUCT
{
}

FCProjectInterface::~FCProjectInterface()
{
}
} // namespace FC


