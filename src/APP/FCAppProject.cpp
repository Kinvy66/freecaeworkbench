/******************************************************************************
 * File     : FCAppProject.h
 * Brief    : 负责整个工程管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-31
 * Version  : V0.0.1
 * Detail   :工程文件是一个压缩包，因此打开工程文件时，会在临时目录把这个压缩包解压
 *           在保存文件时，把临时文件对应的压缩包进行压缩并移动到指定位置
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppProject.h"
#include <memory>
// Qt
#include <QBuffer>
#include <QDomDocument>
#include <QFile>
#include <QScopedPointer>
#include <QVariant>
#include <QPen>
#include <QElapsedTimer>
#include <QSet>
#include <QSysInfo>


const QString c_workflowxml_save_filename = QStringLiteral("workflow.xml");
const QString c_chartsxml_save_filename   = QStringLiteral("charts.xml");
const QString c_chartitem_save_folder     = QStringLiteral("chart-data");

#ifndef DAAPPPROJECT_TASK_LOAD_ID_BEGIN
#define DAAPPPROJECT_TASK_LOAD_ID_BEGIN 0x234
#endif


/**
 *@def 加载任务id - 工作流的ui
 */
#ifndef DAAPPPROJECT_TASK_LOAD_ID_WORKFLOW
#define DAAPPPROJECT_TASK_LOAD_ID_WORKFLOW (DAAPPPROJECT_TASK_LOAD_ID_BEGIN + 1)
#endif

/**
 *@def 加载任务id - datamanager
 */
#ifndef DAAPPPROJECT_TASK_LOAD_ID_DATAMANAGER
#define DAAPPPROJECT_TASK_LOAD_ID_DATAMANAGER (DAAPPPROJECT_TASK_LOAD_ID_BEGIN + 2)
#endif

/**
 *@def 加载任务id - chartItemManager
 */
#ifndef DAAPPPROJECT_TASK_LOAD_ID_CHARTITEMMANAGER
#define DAAPPPROJECT_TASK_LOAD_ID_CHARTITEMMANAGER (DAAPPPROJECT_TASK_LOAD_ID_BEGIN + 3)
#endif

/**
 *@def 加载任务id - charts_xml
 */
#ifndef DAAPPPROJECT_TASK_LOAD_ID_CHARTS_INFO
#define DAAPPPROJECT_TASK_LOAD_ID_CHARTS_INFO (DAAPPPROJECT_TASK_LOAD_ID_BEGIN + 4)
#endif

namespace FC 
{

FCAppProject::FCAppProject(FCCoreInterface *c, QObject *p)
    : FCProjectInterface(c, p)
{
    // todo
}

FCAppProject::~FCAppProject()
{
    
}

} // namespace FC
