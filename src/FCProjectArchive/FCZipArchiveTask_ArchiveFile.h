/**
 * @file FCZipArchiveTask_ArchiveFile.h
 * @brief 把文件压缩到压缩包的任务
 * @date 2025-11-28
 * @version V0.0.1
 * @details 执行 FCZipArchiveTask_ArchiveFile(const QString& tempFilePath, const QString& archivePath); 
 * 构造函数的时候为保存，会把tempFilePath文件保存到zip的archivePath文件中
 * 
 * 执行 FCZipArchiveTask_ArchiveFile(const QString& archivePath);
 * 进行读取操作，读取操作会把archivePath的内容，保存到一个临时路径中， 保存的临时路径通过@sa getTempFilePath 函数获取
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCZIPARCHIVETASK_ARCHIVEFILE_H
#define FCZIPARCHIVETASK_ARCHIVEFILE_H
#include "FCProjectArchiveAPI.h"
#include "FCAbstractArchiveTask.h"
#include <QTemporaryDir>

namespace FC 
{
class FCPROJECTARCHIVE_API FCZipArchiveTask_ArchiveFile : public FCAbstractArchiveTask
{
public:
    FCZipArchiveTask_ArchiveFile();
    // 保存
    FCZipArchiveTask_ArchiveFile(const QString& archivePath, const QString& tempFilePath);
    // 读取
    FCZipArchiveTask_ArchiveFile(const QString& archivePath);
    virtual ~FCZipArchiveTask_ArchiveFile();
    // 临时文件路径
    QString getTempFilePath() const;
    void setTempFilePath(const QString& v);
    // zip档案文件路径
    QString getArchivePath() const;
    void setArchivePath(const QString& v);
    //
    virtual bool exec(FCAbstractArchive* archive, FCAbstractArchiveTask::Mode mode) override;
    
private:
    QString mTempFilePath;
    QString archivePath;
    QTemporaryDir mTempDir;
};
} // namespace FC



#endif // FCZIPARCHIVETASK_ARCHIVEFILE_H
