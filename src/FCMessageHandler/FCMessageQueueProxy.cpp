/******************************************************************************
 * File     : FCMessageQueueProxy.cpp
 * Brief    : 这是一个全局的日志队列，所有的qdebug相关的消息都会推入这个队列中
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-09
 * Version  : V0.0.1
 * Detail   :队列提供一个惰性的信号，所谓惰性信号是指不会一直触发，而是会限制触发的频度，避免过多的消息导致
 *            系统缓慢，默认每个信号间隔1s，可以通过setSignalEmitInterval来改变
 *
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCMessageQueueProxy.h"
// stl
#include <memory>
// Qt
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>
#include <QTimer>
#include <QApplication>

namespace FC 
{
class FCMessageQueueProxy::PrivateData
{
    FC_DECLARE_PUBLIC(FCMessageQueueProxy)
public:
    enum EmitSignalType
    {
        SignalQueueAppended    = 0,
        SignalQueueSizeChanged = 1
    };
    PrivateData(FCMessageQueueProxy* p);
    ~PrivateData();
    //_FCThreadSafeMessageQueue通知FCGlobalMessageQueuePrivate，队列有东西插入
    void queueAppended();
    
    //_FCThreadSafeMessageQueue通知FCGlobalMessageQueuePrivate，队列的尺寸变化了
    void queueSizeChanged();
    
    //构建timer
    void buildTimer(int intervalms);
    
    //设置发射间隔
    void setEmitInterval(int ms);
    int getEmitInterval() const;
    //设置惰性发射
    void setLazyEmit(bool on);
    bool isLazyEmit() const;
    //这个是为了避免事件循环未启动就创建timer
    void delayCreateCheck();
    
public:
    bool mIsLazyEmit { true };                       ///< 信号是否惰性触发
    std::unique_ptr< QTimer > mTimer;                ///< 信号发射间隔
    int mEmitIntervalms { 1000 };                    ///发射间隔
    bool mNeedEmitSignalQueueAppended { false };     ///< 标记需要发射信号
    bool mNeedEmitSignalQueueSizeChanged { false };  ///< 标记需要发射信号
    bool mDelayCreateTimerBeforeEventLoopUp { false };  ///< 这个是标记timer需要创建，但由于app的事件循环还未建立，因此要延迟create
};


/**
 * @brief 一个线程安全的队列，所有的@sa FCGlobalMessageQueue 都会向这个队列注册
 *
 * 这个使用单例，避免全局变量的初始化顺序问题导致异常
 */
class FCThreadSafeMessageQueue_Private
{
private:
    FCThreadSafeMessageQueue_Private() : mCapacity(1000)
    {
    }
    
public:
    static FCThreadSafeMessageQueue_Private& getInstance()
    {
        static FCThreadSafeMessageQueue_Private s_queue;
        return s_queue;
    }
    
    int size() const
    {
        QMutexLocker lc(&mMutex);
        return mMessages.size();
    }
    
    FCMessageLogItem at(int index) const
    {
        QMutexLocker lc(&mMutex);
        return mMessages.value(index);
    }
    
    void append(const FCMessageLogItem& item)
    {
        bool needNotifySizeChanged = false;
        
        {
            QMutexLocker lc(&mMutex);
            if (mMessages.size() >= mCapacity) {
                mMessages.pop_front();
            } else {
                //通知队列的尺寸变化了
                needNotifySizeChanged = true;
            }
            mMessages.append(item);
        }
        //通知队列有东西插入了
        {
            QMutexLocker lc(&mMutexNotifys);
            if (needNotifySizeChanged) {
                for (FCMessageQueueProxy::PrivateData* p : qAsConst(mNotifys)) {
                    p->queueSizeChanged();
                }
            }
            for (FCMessageQueueProxy::PrivateData* p : qAsConst(mNotifys)) {
                p->queueAppended();
            }
        }
    }
    
    void setCapacity(int c)
    {
        QMutexLocker lc(&mMutex);
        mCapacity = c;
    }
    
    int getCapacity()
    {
        QMutexLocker lc(&mMutex);
        return mCapacity;
    }
    
    void registerNotify(FCMessageQueueProxy::PrivateData* p)
    {
        QMutexLocker lc(&mMutexNotifys);
        mNotifys.append(p);
    }
    
    void unregisterNotify(FCMessageQueueProxy::PrivateData* p)
    {
        QMutexLocker lc(&mMutexNotifys);
        mNotifys.removeAll(p);
    }
    
    void clear()
    {
        QMutexLocker lc(&mMutex);
        int oldsize = mMessages.size();
        mMessages.clear();
        
        if (oldsize != 0) {
            QMutexLocker lcNotifys(&mMutexNotifys);
            for (FCMessageQueueProxy::PrivateData* p : qAsConst(mNotifys)) {
                p->queueSizeChanged();
            }
        }
    }
    
private:
    mutable QMutex mMutex;
    mutable QMutex mMutexNotifys;
    QList< FCMessageLogItem > mMessages;                  ///< 消息
    int mCapacity;                                        ///< 容量
    QList< FCMessageQueueProxy::PrivateData* > mNotifys;  ///< 等待通知的
};

//===================================================
// FCMessageQueueProxyPrivate
//===================================================
FCMessageQueueProxy::PrivateData::PrivateData(FCMessageQueueProxy* p) : q_ptr(p)
{
    FCThreadSafeMessageQueue_Private::getInstance().registerNotify(this);
    //默认是惰性发射
    buildTimer(mEmitIntervalms);
}

FCMessageQueueProxy::PrivateData::~PrivateData()
{
    FCThreadSafeMessageQueue_Private::getInstance().unregisterNotify(this);
}

void FCMessageQueueProxy::PrivateData::queueAppended()
{
    if (isLazyEmit()) {
        //惰性发射仅仅做标记
        //        delayCreateCheck();
        mNeedEmitSignalQueueAppended = true;
    } else {
        //非惰性发射立即发射信号
        q_ptr->emitSignal(SignalQueueAppended);
    }
}

void FCMessageQueueProxy::PrivateData::queueSizeChanged()
{
    if (isLazyEmit()) {
        //惰性发射仅仅做标记
        //        delayCreateCheck();
        mNeedEmitSignalQueueSizeChanged = true;
    } else {
        //非惰性发射立即发射信号
        q_ptr->emitSignal(SignalQueueSizeChanged);
    }
}

void FCMessageQueueProxy::PrivateData::buildTimer(int intervalms)
{
    if (QApplication::startingUp() || QApplication::closingDown()) {
        //如果app还未启动,或者已经关闭不发射信号
        mDelayCreateTimerBeforeEventLoopUp = true;
        return;
    }
    if (!mTimer) {
        //如果timer没有建立，就建立一个timer
        mTimer.reset(new QTimer());
        mTimer->setInterval(intervalms);
        QObject::connect(mTimer.get(), &QTimer::timeout, q_ptr, &FCMessageQueueProxy::onTimeout);
        mTimer->start();
    }
}

void FCMessageQueueProxy::PrivateData::setEmitInterval(int ms)
{
    mEmitIntervalms = ms;
    if (mTimer) {
        mTimer->setInterval(ms);
    }
}

int FCMessageQueueProxy::PrivateData::getEmitInterval() const
{
    return mEmitIntervalms;
}

void FCMessageQueueProxy::PrivateData::setLazyEmit(bool on)
{
    mIsLazyEmit = on;
    if (on) {
        if (nullptr == mTimer) {
            buildTimer(mEmitIntervalms);
        } else {
            if (mTimer->interval() != mEmitIntervalms) {
                mTimer->setInterval(mEmitIntervalms);
            }
        }
    } else {
        //不是惰性发射就删除timer
        mTimer.reset(nullptr);
    }
}

bool FCMessageQueueProxy::PrivateData::isLazyEmit() const
{
    return mIsLazyEmit;
}

void FCMessageQueueProxy::PrivateData::delayCreateCheck()
{
    if (mDelayCreateTimerBeforeEventLoopUp) {
        if (mIsLazyEmit) {
            mDelayCreateTimerBeforeEventLoopUp = false;
            buildTimer(mEmitIntervalms);
        }
    }
}
//===================================================
// FCMessageQueueProxy
//===================================================
FCMessageQueueProxy::FCMessageQueueProxy(QObject* par) : QObject(par), FC_PIMPL_CONSTRUCT
{
}

FCMessageQueueProxy::~FCMessageQueueProxy()
{
}

/**
 * @brief 设置信号发射间隔
 *
 * 在设置了lazyEmit才会起作用
 * @param ms
 */
void FCMessageQueueProxy::setEmitInterval(int ms)
{
    d_ptr->setEmitInterval(ms);
}
/**
 * @brief 获取信号发射间隔，次间隔只有在设置了惰性触发时起作用
 * @return
 */
int FCMessageQueueProxy::getEmitInterval() const
{
    return d_ptr->getEmitInterval();
}

void FCMessageQueueProxy::append(const FCMessageLogItem& item)
{
    FCThreadSafeMessageQueue_Private::getInstance().append(item);
}

FCMessageLogItem FCMessageQueueProxy::at(int index) const
{
    return FCThreadSafeMessageQueue_Private::getInstance().at(index);
}

int FCMessageQueueProxy::size() const
{
    return FCThreadSafeMessageQueue_Private::getInstance().size();
}

/**
 * @brief 设置信号惰性触发
 * @param on
 */
void FCMessageQueueProxy::setLazyEmit(bool on)
{
    d_ptr->setLazyEmit(on);
}

/**
 * @brief 判断信号是否惰性触发
 * @return
 */
bool FCMessageQueueProxy::isLazyEmit() const
{
    return d_ptr->isLazyEmit();
}

/**
 * @brief 清空队列
 */
void FCMessageQueueProxy::clear()
{
    FCThreadSafeMessageQueue_Private::getInstance().clear();
}

/**
 * @brief 设置全局队列的容量
 * @param c
 */
void FCMessageQueueProxy::setGlobalQueueCapacity(int c)
{
    FCThreadSafeMessageQueue_Private::getInstance().setCapacity(c);
}

/**
 * @brief 获取全局队列的容量
 * @return
 */
int FCMessageQueueProxy::getGlobalQueueCapacity()
{
    return FCThreadSafeMessageQueue_Private::getInstance().getCapacity();
}

/**
 * @brief 计时器到达
 */
void FCMessageQueueProxy::onTimeout()
{
    if (d_ptr->mNeedEmitSignalQueueAppended) {
        d_ptr->mNeedEmitSignalQueueAppended = false;
        emit messageQueueAppended();
    }
    if (d_ptr->mNeedEmitSignalQueueSizeChanged) {
        d_ptr->mNeedEmitSignalQueueSizeChanged = false;
        emit messageQueueSizeChanged(FCThreadSafeMessageQueue_Private::getInstance().size());
    }
}

void FCMessageQueueProxy::emitSignal(int type)
{
    if (QApplication::startingUp() || QApplication::closingDown()) {
        //如果app还未启动,或者已经关闭不发射信号
        return;
    }
    switch (type) {
    case FCMessageQueueProxy::PrivateData::SignalQueueAppended:
        emit messageQueueAppended();
        break;
    case FCMessageQueueProxy::PrivateData::SignalQueueSizeChanged:
        emit messageQueueSizeChanged(FCThreadSafeMessageQueue_Private::getInstance().size());
        break;
    default:
        break;
    }
}


} // namespace FC
