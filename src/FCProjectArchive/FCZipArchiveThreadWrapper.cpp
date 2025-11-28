/**
 * @file FCZipArchiveThreadWrapper.cpp
 * @brief FCZipArchive的多线程封装
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCZipArchiveThreadWrapper.h"
#include <QThread>
#include <QDebug>
#include "FCZipArchive.h"
// #include "FCZipArchiveTask_ByteArray.h"
#include "FCZipArchiveTask_Xml.h"
#include "FCZipArchiveTask_ArchiveFile.h"


namespace FC 
{
class FCZipArchiveThreadWrapper::PrivateData
{
    FC_DECLARE_PUBLIC(FCZipArchiveThreadWrapper)
public:
    PrivateData(FCZipArchiveThreadWrapper* p);
    
public:
    FCZipArchive* mArchive { nullptr };
    QThread* mThread { nullptr };
    bool mIsBusy { false };
};

FCZipArchiveThreadWrapper::PrivateData::PrivateData(FCZipArchiveThreadWrapper* p)
    : q_ptr(p)
{
}


//----------------------------------------------------
// FCZipArchiveThreadWrapper
//----------------------------------------------------
FCZipArchiveThreadWrapper::FCZipArchiveThreadWrapper(QObject* par)
    : QObject(par), FC_PIMPL_CONSTRUCT
{
    init();
}

FCZipArchiveThreadWrapper::~FCZipArchiveThreadWrapper()
{
    if (d_ptr->mThread) {
        // 退出时先把线程安全退出
        d_ptr->mThread->quit();
        d_ptr->mThread->wait();
    }
}

void FCZipArchiveThreadWrapper::init()
{
    //   创建线程
    QThread* thread       = new QThread();
    FCZipArchive* archive = new FCZipArchive();
    // 绑定
    archive->moveToThread(thread);
    // 任务执行完结束线程
    connect(archive, &FCAbstractArchive::taskFinished,
            this, &FCZipArchiveThreadWrapper::onTaskFinish);
    connect(archive, &FCAbstractArchive::taskProgress,
            this, &FCZipArchiveThreadWrapper::taskProgress);
    
    // 信号绑定触发saveall
    connect(this, &FCZipArchiveThreadWrapper::beginSave,
            archive, &FCAbstractArchive::saveAll);
    connect(this, &FCZipArchiveThreadWrapper::beginLoad,
            archive, &FCAbstractArchive::loadAll);
    
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::finished, archive, &FCAbstractArchive::deleteLater);
    thread->start();
    
    d_ptr->mArchive = archive;
    d_ptr->mThread  = thread;
}

bool FCZipArchiveThreadWrapper::isBusy() const
{
    return d_ptr->mIsBusy;
}

// std::shared_ptr< FCAbstractArchiveTask >
// FCZipArchiveThreadWrapper::appendByteSaveTask(const QString& zipRelatePath,
//                                               const QByteArray& data)
// {
//     if (isBusy()) {
//         return std::shared_ptr< FCAbstractArchiveTask >();
//     }
//     auto t = std::make_shared< FCZipArchiveTask_ByteArray >(zipRelatePath, data);
//     d_ptr->mArchive->appendTask(t);
//     return t;
// }

std::shared_ptr< FCAbstractArchiveTask >
FCZipArchiveThreadWrapper::appendXmlSaveTask(const QString& zipRelatePath,
                                            const QDomDocument& data)
{
    if (isBusy()) {
        return std::shared_ptr< FCAbstractArchiveTask >();
    }
    auto t = std::make_shared< FCZipArchiveTask_Xml >(zipRelatePath, data);
    d_ptr->mArchive->appendTask(t);
    return t;
}

std::shared_ptr< FCAbstractArchiveTask >
FCZipArchiveThreadWrapper::appendFileSaveTask(const QString& zipRelatePath,
                                              const QString& localFilePath)
{
    if (isBusy()) {
        return std::shared_ptr< FCAbstractArchiveTask >();
    }
    auto t = std::make_shared< FCZipArchiveTask_ArchiveFile >(zipRelatePath, localFilePath);
    d_ptr->mArchive->appendTask(t);
    return t;
}


// std::shared_ptr< FCAbstractArchiveTask >
// FCZipArchiveThreadWrapper::appendByteLoadTask(const QString& zipRelatePath, int code)
// {
//     if (isBusy()) {
//         return std::shared_ptr< FCAbstractArchiveTask >();
//     }
//     std::shared_ptr< FCZipArchiveTask_ByteArray > task =
//         std::make_shared< FCZipArchiveTask_ByteArray >(zipRelatePath);
//     task->setCode(code);
//     d_ptr->mArchive->appendTask(task);
//     return task;
// }

std::shared_ptr< FCAbstractArchiveTask >
FCZipArchiveThreadWrapper::appendXmlLoadTask(const QString& zipRelatePath, int code)
{
    if (isBusy()) {
        return std::shared_ptr< FCAbstractArchiveTask >();
    }
    std::shared_ptr< FCZipArchiveTask_Xml > task =
        std::make_shared<FCZipArchiveTask_Xml>(zipRelatePath);
    task->setCode(code);
    d_ptr->mArchive->appendTask(task);
    return task;
}

std::shared_ptr< FCAbstractArchiveTask >
FCZipArchiveThreadWrapper::appendFileLoadTask(const QString& zipRelatePath, int code)
{
    if (isBusy()) {
        return std::shared_ptr< FCAbstractArchiveTask >();
    }
    std::shared_ptr< FCZipArchiveTask_ArchiveFile > task =
        std::make_shared< FCZipArchiveTask_ArchiveFile >(zipRelatePath);
    task->setCode(code);
    d_ptr->mArchive->appendTask(task);
    return task;
}

bool FCZipArchiveThreadWrapper::appendTask(const std::shared_ptr< FCAbstractArchiveTask >& task)
{
    if (isBusy()) {
        return false;
    }
    d_ptr->mArchive->appendTask(task);
    return true;
}

bool FCZipArchiveThreadWrapper::save(const QString& filePath)
{
    if (isBusy()) {
        return false;
    }
    d_ptr->mIsBusy = true;
    // 发射信号，把消息通知到线程中的DAZipArchive
    Q_EMIT beginSave(filePath);
    return true;
}

bool FCZipArchiveThreadWrapper::load(const QString& filePath)
{
    if (isBusy()) {
        return false;
    }
    d_ptr->mIsBusy = true;
    // 发射信号，把消息通知到线程中的DAZipArchive
    Q_EMIT beginLoad(filePath);
    return true;
}

void FCZipArchiveThreadWrapper::onTaskFinish(int code)
{
    d_ptr->mIsBusy = false;
    switch (code) {
    case FCAbstractArchive::SaveFailed:
        Q_EMIT saved(false);
        break;
    case FCAbstractArchive::SaveSuccess:
        Q_EMIT saved(true);
        break;
    case FCAbstractArchive::LoadFailed:
        Q_EMIT loaded(false);
        break;
    case FCAbstractArchive::LoadSuccess:
        Q_EMIT loaded(true);
        break;
    default:
        break;
    }
}

} // namespace FC
