#ifndef FCPROJECTINTERFACE_H
#define FCPROJECTINTERFACE_H
#include <QObject>
#include <QVersionNumber>
#include "FCInterfaceAPI.h"
#include "FCBaseInterface.h"

namespace FC 
{
class FCDockingAreaInterface;
class FCCoreInterface;
// class DAWorkFlowOperateWidget;
// class DADataManagerInterface;
/**
 * @brief 负责总体工程的接口
 *
 * 通过此接口可以获取当前工程的基本信息
 */
class FCINTERFACE_API FCProjectInterface : public FCBaseInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCProjectInterface)
public:
    FCProjectInterface(FCCoreInterface* c, QObject* par = nullptr);
    ~FCProjectInterface();
};

} // namespace FC


#endif // FCPROJECTINTERFACE_H
