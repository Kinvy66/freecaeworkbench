/**
 * @file FCGmshThreadManager.cpp
 * @brief 网格划分线程管理类
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGmshThreadManager.h"
#include "FCGmshThread.h"
#include "FCGmshSettingData.h"

#include <QDebug>
#include <QMetaType>

#include <vtkDataSet.h>

namespace FC 
{
FCGmshThreadManager* FCGmshThreadManager::s_instance = nullptr;

FCGmshThreadManager* FCGmshThreadManager::getInstance()
{
    static QMutex createMutex;
    if (!s_instance)
    {
        QMutexLocker locker(&createMutex);
        if (!s_instance)
            s_instance = new FCGmshThreadManager();
    }
    return s_instance;
}

FCGmshThreadManager::FCGmshThreadManager(QObject* parent)
    : QObject(parent)
{
    // register vtkDataSet* as metatype for signal/slot passing
    qRegisterMetaType<vtkDataSet*>("vtkDataSet*");
}

FCGmshThreadManager::~FCGmshThreadManager()
{
    stopAll();
}

bool FCGmshThreadManager::addTask(IdType meshID, FCGmshSettingData* setting)
{
    QMutexLocker locker(&mMutex);
    if (mThreads.contains(meshID))
    {
        qWarning() << "Task already running for meshID" << meshID;
        return false;
    }
    
    FCGmshThread* t = new FCGmshThread(meshID, setting, this);
    connect(t, &FCGmshThread::meshFinished, this, &FCGmshThreadManager::onThreadFinished);
    connect(t, &FCGmshThread::meshFinished, t, &FCGmshThread::deleteLater); // auto delete when finished (slot triggered)
    connect(t, &FCGmshThread::progress, this, &FCGmshThreadManager::onThreadProgress);
    connect(t, &FCGmshThread::meshError, this, &FCGmshThreadManager::onThreadError);
    
    mThreads.insert(meshID, t);
    t->start();
    return true;
}

void FCGmshThreadManager::stopAll()
{
    QMutexLocker locker(&mMutex);
    auto keys = mThreads.keys();
    for (int k : keys)
    {
        FCGmshThread* t = mThreads.value(k);
        if (t)
        {
            t->requestAbort();
            t->wait(2000); // wait a bit
            // if still running, force deleteLater
            if (t->isRunning())
            {
                t->terminate(); // best-effort; use with caution
                t->wait();
            }
            // delete will be handled by deleteLater connection (or we can delete now)
            t->deleteLater();
        }
    }
    mThreads.clear();
}

bool FCGmshThreadManager::isGenerating(int meshID) const
{
    QMutexLocker locker(&mMutex);
    return mThreads.contains(meshID);
}

void FCGmshThreadManager::onThreadFinished(IdType meshID, vtkDataSet* dataset)
{
    // remove thread from tracking
    {
        QMutexLocker locker(&mMutex);
        if (mThreads.contains(meshID))
        {
            FCGmshThread* t = mThreads.take(meshID);
            Q_UNUSED(t);
            // thread has a deleteLater connected; leave cleanup to Qt
        }
    }
    
    // emit outward for FCMeshModule to handle storing dataset
    emit meshReady(meshID, dataset);
}

void FCGmshThreadManager::onThreadProgress(IdType meshID, int percent)
{
    emit meshProgress(meshID, percent);
}

void FCGmshThreadManager::onThreadError(IdType meshID, const QString& err)
{
    // remove thread from tracking similar to finished
    {
        QMutexLocker locker(&mMutex);
        if (mThreads.contains(meshID))
        {
            FCGmshThread* t = mThreads.take(meshID);
            Q_UNUSED(t);
        }
    }
    emit meshError(meshID, err);
}

} // namespace FC


