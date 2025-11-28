/**
 * @file FCZipArchiveTask_ArchiveFile.cpp
 * @brief 把文件压缩到压缩包的任务
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCZipArchiveTask_ArchiveFile.h"
#include "FCZipArchive.h"
#include <QDebug>
#include <QFileInfo>

namespace FC 
{
FCZipArchiveTask_ArchiveFile::FCZipArchiveTask_ArchiveFile() : FCAbstractArchiveTask()
{
}

FCZipArchiveTask_ArchiveFile::FCZipArchiveTask_ArchiveFile(const QString& archivePath,
                                                           const QString& tempFilePath)
    : FCAbstractArchiveTask()
{
    setTempFilePath(tempFilePath);
    setArchivePath(archivePath);
}

FCZipArchiveTask_ArchiveFile::FCZipArchiveTask_ArchiveFile(const QString& archivePath)
    : FCAbstractArchiveTask()
{
    setArchivePath(archivePath);
}

FCZipArchiveTask_ArchiveFile::~FCZipArchiveTask_ArchiveFile()
{
}

QString FCZipArchiveTask_ArchiveFile::getTempFilePath() const
{
    return mTempFilePath;
}

void FCZipArchiveTask_ArchiveFile::setTempFilePath(const QString& v)
{
    mTempFilePath = v;
}

QString FCZipArchiveTask_ArchiveFile::getArchivePath() const
{
    return archivePath;
}

void FCZipArchiveTask_ArchiveFile::setArchivePath(const QString& v)
{
    archivePath = v;
}

bool FCZipArchiveTask_ArchiveFile::exec(FCAbstractArchive* archive, Mode mode)
{
    if (!archive) {
        return false;
    }
    FCZipArchive* zip = static_cast< FCZipArchive* >(archive);
    if (mode == FCAbstractArchiveTask::WriteMode) {
        // 写模式
        if (!zip->isOpened()) {
            if (!zip->create()) {
                qDebug() << QString("create archive error:%1").arg(zip->getBaseFilePath());
                return false;
            }
        }
        if (!zip->writeFileToZip(getArchivePath(), getTempFilePath())) {
            qDebug() << QString("Unable to write the file from %1 to %2")
                            .arg(getTempFilePath(), getArchivePath());  // cn:无法把文件从%1写入到%2
            return false;
        }
    } else {
        // 读取数据模式
        if (!zip->isOpened()) {
            if (!zip->open()) {
                qDebug() << QString("open archive error:%1").arg(zip->getBaseFilePath());
                return false;
            }
        }
        // 先生成一个临时目录
        QFileInfo fi(getArchivePath());
        QString tempFilePath = mTempDir.filePath(fi.fileName());
        if (!zip->readToFile(getArchivePath(), tempFilePath)) {
            qDebug() << QString("Unable to write the file from %1 to %2.")
                            .arg(getArchivePath(), tempFilePath);
            return false;
        }
        setTempFilePath(tempFilePath);
    }
    return true;
}

} // namespace FC
