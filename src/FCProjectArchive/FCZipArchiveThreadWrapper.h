/**
 * @file FCZipArchiveThreadWrapper.h
 * @brief FCZipArchive的多线程封装，此类内部维护着一个线程，封装了@sa FCZipArchive 的操作
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCZIPARCHIVETHREADWRAPPER_H
#define FCZIPARCHIVETHREADWRAPPER_H
#include "FCProjectArchiveAPI.h"
#include <QObject>
#include <QString>
#include <QDomDocument>
#include "FCAbstractArchiveTask.h"

namespace FC 
{
class FCPROJECTARCHIVE_API FCZipArchiveThreadWrapper : public QObject
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCZipArchiveThreadWrapper)
    
public:
    FCZipArchiveThreadWrapper(QObject* par = nullptr);
    ~FCZipArchiveThreadWrapper();
    // 是否繁忙
    bool isBusy() const;
    // 保存任务
    // std::shared_ptr< FCAbstractArchiveTask > appendByteSaveTask(const QString& zipRelatePath, const QByteArray& data);
    std::shared_ptr< FCAbstractArchiveTask > appendXmlSaveTask(const QString& zipRelatePath, const QDomDocument& data);
    std::shared_ptr< FCAbstractArchiveTask > appendFileSaveTask(const QString& zipRelatePath, const QString& localFilePath);
    // std::shared_ptr< DAAbstractArchiveTask > appendChartItemSaveTask(const QString& zipRelateFolderPath,
                                                                   // DAChartItemsManager chartItemMgr);
    // 读取任务
    // std::shared_ptr< FCAbstractArchiveTask > appendByteLoadTask(const QString& zipRelatePath, int code);
    std::shared_ptr< FCAbstractArchiveTask > appendXmlLoadTask(const QString& zipRelatePath, int code);
    std::shared_ptr< FCAbstractArchiveTask > appendFileLoadTask(const QString& zipRelatePath, int code);
    // std::shared_ptr< DAAbstractArchiveTask > appendChartItemLoadTask(const QString& zipRelateFolderPath, int code);
    // 添加任务
    bool appendTask(const std::shared_ptr< FCAbstractArchiveTask >& task);
public Q_SLOTS:
    bool save(const QString& filePath);
    bool load(const QString& filePath);
private Q_SLOTS:
    void onTaskFinish(int code);
Q_SIGNALS:
    /**
	 * @brief 开始保存信号
	 * @param path
	 */
    void beginSave(const QString& path);
    
    /**
	 * @brief 开始加载信号
	 * @param path
	 */
    void beginLoad(const QString& path);
    
    /**
	 * @brief 保存结束信号
	 * @param success
	 */
    void saved(bool success);
    
    /**
	 * @brief 加载结束信号
	 * @param success
	 */
    void loaded(bool success);
    
    /**
	 * @brief 当前进度信号
	 * 对于读取操作，这个函数会携带读取的结果
	 * @param total 总任务
	 * @param pos 当前任务的位置
	 */
    void taskProgress(std::shared_ptr< FC::FCAbstractArchiveTask > task, int mode);
    
private:
    void init();
    
};
} // namespace FC



#endif // FCZIPARCHIVETHREADWRAPPER_H
