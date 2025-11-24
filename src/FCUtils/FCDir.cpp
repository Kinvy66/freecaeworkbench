/**
 * @file FCDir.cpp
 * @brief 定义了DA的固定路径，包括临时目录，配置文件目录等路径
 * @date 2025-11-20
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCDir.h"
#include <QStandardPaths>
#include <QDir>
#include <QApplication>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <filesystem>
#else
#include <unistd.h>
#include <limits.h>
#include <filesystem>
#endif


namespace FC 
{

FCDir::FCDir()
{
}

/**
 * @brief app名，%APPDATA%路径下的文件夹以app名创建
 * @return
 */
QString FCDir::getAPPName()
{
    const static QString cs_app_name = QStringLiteral("FCWorkBench");
    return cs_app_name;
}

/**
 * @brief 获取当前程序临时路径的根目录
 * @return 此函数返回的路径是临时路径的绝对路径
 * @note 注意此路径在程序结束时会自动删除
 */
QString FCDir::getTempPath()
{
    return tempDir().path();
}

/**
 * @brief 获取当前程序临时路径的QTemporaryDir
 * @return 
 */
QTemporaryDir& FCDir::tempDir()
{
    static QTemporaryDir s_temp_dir;  ///< 本应用的临时目录，程序销毁时会自动删除
    // 确保临时目录有效
    if (!s_temp_dir.isValid()) {
        qCritical() << "Failed to create temporary directory:" << s_temp_dir.errorString();
    }
    return s_temp_dir;
}

/**
 * @brief 根据folderName，在临时路径下创建一个文件夹，返回{RootTempPath}/{folderName}路径
 * @param folderName 临时路径下文件夹的名字
 * @return  如果路径已经存在将直接返回路径，如果不存在则创建
 */
QString FCDir::getTempPath(const QString& folderName)
{
    if (folderName.isEmpty()) {
        return getTempPath();  // 处理空文件夹名的情况
    }
    // 构建完整路径
    const static QString cs_fullPath = QDir::cleanPath(getTempPath() + QDir::separator() + folderName);
    // 创建一个 QDir 对象
    if (QDir().mkpath(cs_fullPath)) {
        qWarning() << "Failed to create directory:" << cs_fullPath;
    }
    // 返回目标文件夹路径
    return cs_fullPath;
}

/**
 * @brief 根据folderName，在临时路径下创建一个文件夹，返回{RootTempPath}/{folderName}的QDir
 * @param folderName 临时路径下文件夹的名字
 * @return 如果路径已经存在将直接返回路径，如果不存在则创建
 */
QDir FCDir::tempDir(const QString& folderName)
{
    return QDir(getTempPath(folderName));
}

/**
 * @brief 获取一个临时目录下的文件
 *
 * 此函数等效@a FCADir::getRootTempDir.filePath(fileName)
 * @param fileName
 * @return
 */
QString FCDir::getTempFilePath(const QString& fileName)
{
    return tempDir().filePath(fileName);
}

/**
 * @brief 获取本应用的配置文件路径
 *
 * 如果配置文件路径不存在，将创建此路径，并返回
 * 配置文件路径等同于：
 * @code
 * getAppDataPath(QStringLiteral("config"));
 * @endcode
 *
 * @return
 */
QString FCDir::getConfigPath()
{
    // 获取配置文件路径
    const static QString cs_configPath = getAppDataPath(QStringLiteral("config"));
    
    // 如果路径不存在，则创建它
    if (!QDir().mkpath(cs_configPath)) {
        qCritical() << "Failed to create application config directory:" << cs_configPath;
    }
    return cs_configPath;
}

/**
 * @brief 根据folderName，在配置文件路径下创建一个文件夹，返回{getConfigPath}/{folderName}路径
 * @param 配置文件路径下文件夹的名字
 * @return 如果路径已经存在将直接返回路径，如果不存在则创建
 */
QString FCDir::getConfigPath(const QString& folderName)
{
    if (folderName.isEmpty()) {
        return getConfigPath();  // 处理空文件夹名的情况
    }
    // 构建完整路径
    QString fullPath = QDir::cleanPath(getConfigPath() + QDir::separator() + folderName);
    // 创建目录（如果不存在）
    if (!QDir().mkpath(fullPath)) {
        qWarning() << "Failed to create directory:" << fullPath;
    }
    
    return fullPath;
}

/**
 * @brief 获取程序运行路径
 * @note 这个路径不会应该工作路径的改变而改变，就是exe所在文件夹
 * @return
 */
QString FCDir::getExecutablePath()
{
#if 0
    return QApplication::applicationDirPath();
#else
    const static std::string cs_executablePath = get_executable_path();
    // 这时文本是系统编码的，要转换为utf-8
    return QString::fromLocal8Bit(cs_executablePath.c_str());
#endif
}

/**
 * @brief 获取程序运行路径
 * @return 这个路径不会应该工作路径的改变而改变，就是exe所在文件夹
 */
std::string FCDir::get_executable_path()
{
#if defined(_WIN32) || defined(_WIN64)
    char buffer[ MAX_PATH ];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);  // 显式 A 版
    std::string fullPath(buffer);
    std::filesystem::path path(fullPath);
    return path.parent_path().string();
#else
    char buffer[ PATH_MAX ];
    ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
    if (count == -1) {
        return "";  // Error occurred
    }
    std::string fullPath(buffer, count);
    std::filesystem::path path(fullPath);
    return path.parent_path().string();
#endif
}

/**
 * @brief 获取日志文件名字
 * @return 默认返回"fc_log.log"
 */
QString FCDir::getLogFileName()
{
    const static QString cs_da_log_file = QStringLiteral("fc_log.log");
    return cs_da_log_file;
}

/**
 * @brief 获取日志文件所在路径
 * @return 默认返回"{ExecutablePath}/log"
 */
QString FCDir::getLogPath()
{
    const static QString cs_logPath = getAppDataPath(QStringLiteral("log"));
    return cs_logPath;
}

/**
 * @brief 获取dump文件夹
 * @return
 */
QString FCDir::getDumpFilePath()
{
    const static QString cs_dumpPath = getAppDataPath(QStringLiteral("dumps"));
    return cs_dumpPath;
}

/**
 * @brief 获取日志文件的完整路径
 * @return 默认返回"{getLogPath()}/log/da_log.log"
 */
QString FCDir::getLogFilePath()
{
    const static QString cs_logFilePath = QDir::toNativeSeparators(getLogPath() + QDir::separator() + getLogFileName());
    return cs_logFilePath;
}

/**
 * @brief 获取程序数据路径
 *
 * 此函数等价于：
 * @code
 * return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
 * @endcode
 * @return
 */
QString FCDir::getAppDataPath()
{
    // 获取应用数据文件夹
    const static QString cs_appDataPath = QDir::toNativeSeparators(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + getAPPName());
    // 使用单次操作创建路径（如果不存在）
    if (!QDir().mkpath(cs_appDataPath)) {
        qCritical() << "Failed to create application data directory:" << cs_appDataPath;
    }
    return cs_appDataPath;
}

/**
 * @brief 返回应用目录下的文件夹，如果文件没有，此函数会保证创建好文件夹
 * @param folderName
 * @return
 */
QString FCDir::getAppDataPath(const QString& folderName)
{
    if (folderName.isEmpty()) {
        return getAppDataPath();  // 处理空文件夹名的情况
    }
    // 构建完整路径
    QString fullPath = QDir::cleanPath(getAppDataPath() + QDir::separator() + folderName);
    // 创建目录（如果不存在）
    if (!QDir().mkpath(fullPath)) {
        qWarning() << "Failed to create directory:" << fullPath;
    }
    
    return fullPath;
}

/**
 * @brief 重载QDebug针对DADir的<<操作符，打印RootTempPath和RootConfigPath位置
 * @param debug
 * @param c
 * @return 
 */
QDebug operator<<(QDebug debug, const FCDir& c)
{
    QDebugStateSaver saver(debug);
    debug.noquote() << "Executable Dir:" << FCDir::getExecutablePath();
    debug.noquote() << "\nApp Data Dir:" << FCDir::getAppDataPath();
    debug.noquote() << "\nTemporary Dir:" << FCDir::getTempPath();
    debug.noquote() << "\nLog File Path:" << FCDir::getLogFilePath();
    debug.noquote() << "\nConfig Dir:" << FCDir::getConfigPath();
    debug.noquote() << "\nApp Data Dir:" << FCDir::getDumpFilePath();
    return debug;
}
} // namespace FC

