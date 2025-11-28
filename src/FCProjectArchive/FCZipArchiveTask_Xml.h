/**
 * @file FCZipArchiveTask_Xml.h
 * @brief 保存/加载xml文件的任务
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCZIPARCHIVETASK_XML_H
#define FCZIPARCHIVETASK_XML_H
#include "FCProjectArchiveAPI.h"
#include <QDomDocument>
#include <QObject>
#include <QString>
#include "FCAbstractArchiveTask.h"

namespace FC 
{
class FCPROJECTARCHIVE_API FCZipArchiveTask_Xml : public FCAbstractArchiveTask
{
public:
    FCZipArchiveTask_Xml();
    // 加载构造
    FCZipArchiveTask_Xml(const QString& path);
    // 保存构造
    FCZipArchiveTask_Xml(const QString& path, const QDomDocument& doc);
    ~FCZipArchiveTask_Xml();
    // xml文档
    QDomDocument getDomDocument() const;
    void setDomDocument(const QDomDocument& domDocument);
    // 路径
    QString getPath() const;
    void setPath(const QString& path);
    // 错误信息
    QString getLastErrorString() const;
    void setLastErrorString(const QString& lastErrorString);
    //
    virtual bool exec(FCAbstractArchive* archive, FCAbstractArchiveTask::Mode mode) override;
    
private:
    QString mPath;
    QDomDocument mDomDocument;
    QString mLastErrorString;
};
} // namespace FC



#endif // FCZIPARCHIVETASK_XML_H
