/******************************************************************************
 * File     : FCRecentFilesManager.cpp
 * Brief    : 最近打开文件管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-01
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCRECENTFILESMANAGER_H
#define FCRECENTFILESMANAGER_H

#include <QObject>
#include <QStringList>
#include "FCGuiAPI.h"
class QActionGroup;
class QMenu;

namespace FC 
{
class FCGUI_API FCRecentFilesManager : public QObject
{
    Q_OBJECT
public:
    explicit FCRecentFilesManager(QObject* parent        = nullptr,
                                  int maxEntries         = 8,
                                  const QString& orgName = QString(),
                                  const QString& appName = QString());
    
    //! 把“最近文件”子菜单挂到任意 QMenu
    void attachToMenu(QMenu* parentMenu, const QString& title = tr("Recent files"));  // cn:最近打开文件
    
    //! 成功打开/保存文件后加入列表
    void addFile(const QString& filePath);
    
    //! 清空所有记录
    void clear();
    
    //! 重新扫描：删除不存在文件
    void rescan();
    
Q_SIGNALS:
    
    /**
	 * @brief 用户从菜单选中某文件
	 * @param filePath
	 */
    void fileSelected(const QString& filePath);
    
private:
    void rebuildMenu();                              //!< 重建菜单
    void readAndCleanSettings();                     //!< 首次读取并清理
    void writeSettings();                            //!< 保存到注册表/ini
    bool fileExists(const QString& filePath) const;  //!< 判断文件是否存在
    
    QActionGroup* m_group { nullptr };
    QMenu* m_recentMenu { nullptr };
    QStringList m_files;
    int m_max;
    QString m_org;
    QString m_app;
};
} // namespace FC


#endif // FCRECENTFILESMANAGER_H
