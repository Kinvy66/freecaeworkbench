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

namespace FC 
{
FCGmshThreadManager* FCGmshThreadManager::mInstance = nullptr;
FCGmshThreadManager::FCGmshThreadManager()
{
    // connect(mw, SIGNAL(stopSolve(QWidget *)), this, SLOT(stopThread(QWidget *)));
    // connect(this, SIGNAL(threadStarted(QWidget *)), mw, SIGNAL(addProcessBarSig(QWidget *)));
}
void FCGmshThreadManager::stopThread(QWidget *w)
{
    FCGmshThread *t = _threadHash.value(w);
    if (t == nullptr)
        return;
    _threadHash.remove(w);
    t->stop();
    //		delete t;
}

FCGmshThreadManager *FCGmshThreadManager::getInstance()
{
    if (mInstance == nullptr){
        mInstance = new FCGmshThreadManager();
        
    }
    return mInstance;
}

void FCGmshThreadManager::insertThread(QWidget *w, FCGmshThread *t)
{
    
    _threadHash.insert(w, t);
    emit threadStarted(w);
    connect(t, SIGNAL(threadFinished(FCGmshThread *)), this, SLOT(threadFinished(FCGmshThread *)));
    t->run();
}

void FCGmshThreadManager::threadFinished(FCGmshThread *t)
{
    QWidget *w = _threadHash.key(t);
    delete t;
    _threadHash.remove(w);
    // ModuleBase::ProcessBar *bar = dynamic_cast<ModuleBase::ProcessBar *>(w);
    // if (bar == nullptr)
    //     return;
    // bar->setProcessRange(0, 100);
    // bar->setProcess(100);
}

void FCGmshThreadManager::stopAll()
{
    QList<FCGmshThread *> ts = _threadHash.values();
    for (auto t : ts)
    {
        t->stop();
        delete t;
    }
    _threadHash.clear();
}

bool FCGmshThreadManager::isRuning()
{
    return !_threadHash.isEmpty();
}

} // namespace FC


