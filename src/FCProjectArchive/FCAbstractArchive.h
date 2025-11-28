/**
 * @file FCAbstractArchive.h
 * @brief 持久化的基类
 * @date 2025-11-28
 * @version V0.0.1
 * @details 这个类设计中包含了一个任务队列，任务队列可以实现多线程执行批量写和读
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCABSTRACTARCHIVE_H
#define FCABSTRACTARCHIVE_H
#include "FCProjectArchiveAPI.h"
#include <QString>
#include <QByteArray>
#include <QObject>
#include "FCAbstractArchiveTask.h"

namespace FC 
{
class FCPROJECTARCHIVE_API FCAbstractArchive : public QObject
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCAbstractArchive)
public:
    /**
	 * @brief 结果号
	 */
    enum ResultCode
    {
        SaveSuccess,
        SaveFailed,
        LoadSuccess,
        LoadFailed
    };
    
public:
    FCAbstractArchive(QObject* par = nullptr);
    virtual ~FCAbstractArchive();
    /**
	 * @brief 设置基础路径
	 *
	 * 对于文件来说，基础路径就是要保存的目录，所有文件的写入都基于此目录，对应zip来说，这个路径就是zip文件路径
	 *
	 * @note 对于一些单文件类操作，例如zip文件，设置路径后需要打开文件的，应该继承此函数，把打开的操作也叫上，例如：
	 * @code
	 * @endcode
	 * @param path 基础路径
	 */
    virtual bool setBaseFilePath(const QString& path);
    QString getBaseFilePath() const;
    
    /**
	 * @brief 写数据
	 * @param relatePath 相对位置此位置相对BaseFilePath
	 * @param byte
	 * @return
	 */
    virtual bool write(const QString& relatePath, const QByteArray& byte) = 0;
    
    /**
	 * @brief 读取数据
	 * @param relatePath 相对位置此位置相对BaseFilePath相对位置此位置相对BaseFilePath
	 * @return 读取失败返回一个空QByteArray
	 */
    virtual QByteArray read(const QString& relatePath) = 0;
    
    /**
	 * @brief 删除文件
	 * @param relatePath
	 * @return
	 */
    virtual bool remove(const QString& relatePath) = 0;
    
    // 添加任务
    void appendTask(const std::shared_ptr< FCAbstractArchiveTask >& task);
    // 获取任务数量
    int getTaskCount() const;
    // 是否有任务
    bool isTaskQueueEmpty() const;
    
public Q_SLOTS:
    // 保存所有，执行任务队列
    virtual void saveAll(const QString& filePath) = 0;
    // 读取所有，执行任务队列，内个任务的读取结果通过taskProgress信号携带
    virtual void loadAll(const QString& filePath) = 0;
    
public:
    // 转换为临时路径
    static QString toTemporaryPath(const QString& path);
    // 替换文件
    static bool replaceFile(const QString& file, const QString& beReplaceFile);
    
Q_SIGNALS:
    /**
	 * @brief 当前进度信号
	 * 对于读取操作，这个函数会携带读取的结果
	 * @param task 任务
	 * @param mode 模式，具体为FCAbstractArchiveTask::Mode
	 */
    void taskProgress(std::shared_ptr< FC::FCAbstractArchiveTask > task, int mode);
    
    /**
	 * @brief 任务完成
	 */
    void taskFinished(int resultCode);
    
protected:
    // 从顶部提取一个任务
    std::shared_ptr< FCAbstractArchiveTask > takeTask();
};
} // namespace FC



#endif // FCABSTRACTARCHIVE_H
