/**
 * @file FCGmshThreadManager.h
 * @brief 网格划分线程管理类
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGMSHTHREADMANAGER_H
#define FCGMSHTHREADMANAGER_H
#include "FCMeshModuleAPI.h"
#include <QObject>
#include <QHash>

namespace FC 
{
class FCGmshThread;

class FCMESHMODULE_API FCGmshThreadManager : public QObject
{
    Q_OBJECT
public:
    FCGmshThreadManager();
    ~FCGmshThreadManager() = default;
    /**
		 * @brief 增加新的线程
		 * @param w 窗口部件
		 * @param t 线程
		 * @since 2.5.0
		 */
    void insertThread(QWidget *w, FCGmshThread *t);
    /**
		 * @brief 停止所有线程
		 * @since 2.5.0
		 */
    void stopAll();
    /**
		 * @brief 是否有线程在运行
		 * @return bool
		 * @since 2.5.0
		 */
    bool isRuning();
    
signals:
    /**
		 * @brief 增加新的线程并启动时会触发该信号
		 * @since 2.5.0
		 */
    void threadStarted(QWidget *);
    
private slots:
    /**
		 * @brief 停止线程槽函数
		 * @param w
		 * @since 2.5.0
		 */
    void stopThread(QWidget *w);
    /**
		 * @brief 线程结束槽函数
		 * @param t
		 * @since 2.5.0
		 */
    void threadFinished(FCGmshThread *t);
    
private:
    /**
		 * @brief 线程哈希表
		 * @since 2.5.0
		 */
    QHash<QWidget *, FCGmshThread *> _threadHash{};
    
};

} // namespace FC


#endif // FCGMSHTHREADMANAGER_H
