/**
 * @file FCAbstractArchive.cpp
 * @brief 持久化的基类
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCAbstractArchive.h"
#include "FCAbstractArchiveTask.h"
#include <deque>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDebug>

namespace FC 
{
//===============================================================
// FCAbstractArchive::PrivateData
//===============================================================
class FCAbstractArchive::PrivateData
{
    FC_DECLARE_PUBLIC(FCAbstractArchive)
public:
    PrivateData(FCAbstractArchive* p);
    std::shared_ptr< FC::FCAbstractArchiveTask > takeTask();
    
public:
    QString mBaseFilePath;
    std::deque< std::shared_ptr< FC::FCAbstractArchiveTask > > mTaskQueue;
};

FCAbstractArchive::PrivateData::PrivateData(FCAbstractArchive* p) : q_ptr(p)
{
}

std::shared_ptr< FC::FCAbstractArchiveTask > FCAbstractArchive::PrivateData::takeTask()
{
    std::shared_ptr< FC::FCAbstractArchiveTask > t = mTaskQueue.front();
    mTaskQueue.pop_front();
    return t;
}

//===============================================================
// FCAbstractArchive
//===============================================================
FCAbstractArchive::FCAbstractArchive(QObject* par) : QObject(par), FC_PIMPL_CONSTRUCT
{
}

FCAbstractArchive::~FCAbstractArchive()
{
}

bool FCAbstractArchive::setBaseFilePath(const QString& path)
{
    d_ptr->mBaseFilePath = path;
    return true;
}

QString FCAbstractArchive::getBaseFilePath() const
{
    return d_ptr->mBaseFilePath;
}

void FCAbstractArchive::appendTask(const std::shared_ptr< FC::FCAbstractArchiveTask >& task)
{
    d_ptr->mTaskQueue.emplace_back(task);
}

int FCAbstractArchive::getTaskCount() const
{
    return static_cast< int >(d_ptr->mTaskQueue.size());
}

bool FCAbstractArchive::isTaskQueueEmpty() const
{
    return d_ptr->mTaskQueue.empty();
}

/**
 * @brief 从顶部提取一个任务
 * @return
 */
std::shared_ptr< FC::FCAbstractArchiveTask > FCAbstractArchive::takeTask()
{
    return d_ptr->takeTask();
}

/**
 * @brief 转换为临时路径
 * @return
 */
QString FCAbstractArchive::toTemporaryPath(const QString& path)
{
    QFileInfo fileInfo(path);
    
    // 获取原始文件的目录和文件名
    QDir dir = fileInfo.absoluteDir();
    
    // 构造临时文件名：.~原文件名
    QString tempFileName = QString(".~%1").arg(fileInfo.fileName());
    
    // 拼接完整临时路径
    QString tempPath = dir.filePath(tempFileName);
    
    return tempPath;
}

/**
 * @brief 替换文件
 * @param file 要被替换的文件路径,此函数执行完成后，这个文件将消失
 * @param beReplaceFile 用于替换的文件路径,这个路径文件可以不存在
 * @return 成功返回 true，失败返回 false
 */
bool FCAbstractArchive::replaceFile(const QString& file, const QString& beReplaceFile)
{
    // 检查文件是否存在
    if (!QFile::exists(file)) {
        qDebug() << "file does not exist:" << file;
        return false;
    }
    
    // 确保两个文件不是同一个文件
    if (QFileInfo(file).canonicalFilePath() == QFileInfo(beReplaceFile).canonicalFilePath()) {
        qDebug() << "The two files are the same. No replacement needed.";
        return true;  // 如果是同一个文件，直接返回成功
    }
    
    //! 将 beReplaceFile 重命名为 file,如果beReplaceFile已经存在，QFile::copy(file, beReplaceFile)这个函数会返回false，
    //! 因此，beReplaceFile如果存在，先要删除beReplaceFile
    if (QFile::exists(beReplaceFile)) {
        if (!QFile::remove(beReplaceFile)) {
            qDebug() << QString("Failed to remove %1 file").arg(beReplaceFile);
            return false;
        }
    }
    if (!QFile::copy(file, beReplaceFile)) {
        qDebug() << "Failed to copy replacement file to target location:" << file << "->" << beReplaceFile;
        return false;
    }
    // 删除目标文件（file）
    if (!QFile::remove(file)) {
        qDebug() << "Failed to remove the original file:" << file;
        // 虽然删除临时文件失败，但也返回true
        return true;
    }
    return true;
}

} // namespace FC

