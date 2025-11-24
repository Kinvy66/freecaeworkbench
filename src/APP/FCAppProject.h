/**
 * @file FCAppProject.h
 * @brief 负责整个工程管理
 * @date 2025-10-31
 * @version V0.0.1
 * @details 工程文件是一个压缩包，因此打开工程文件时，会在临时目录把这个压缩包解压
 * 在保存文件时，把临时文件对应的压缩包进行压缩并移动到指定位置
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCAPPPROJECT_H
#define FCAPPPROJECT_H

#include <QObject>
#include <QDomElement>
#include <QDomDocument>
#include <QTemporaryDir>
#include "FCProjectInterface.h"
#include "FCGlobals.h"
// #include "DAAbstractNodeLinkGraphicsItem.h"
#include <QThread>
// #include "DAXmlHelper.h"
// #include "DAZipArchiveThreadWrapper.h"
// #include "DAChartItemsManager.h"

namespace FC 
{
// class DAAbstractArchiveTask;
// class DAZipArchiveThreadWrapper;
// class DAWorkFlowOperateWidget;
// class DAWorkFlowGraphicsScene;
// class DADataOperateWidget;
// class DAChartOperateWidget;


class FCAppProject : public FCProjectInterface
{
    Q_OBJECT
public:
    FCAppProject(FCCoreInterface* c, QObject* p = nullptr);
    ~FCAppProject();
};


} // namespace FC



#endif // FCAPPPROJECT_H
