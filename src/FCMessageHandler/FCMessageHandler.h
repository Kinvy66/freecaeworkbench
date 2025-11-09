#ifndef FCMESSAGEHANDLER_H
#define FCMESSAGEHANDLER_H

#include "FCMessageHandlerAPI.h"
#include <QObject>
#include <QTextStream>
#include <string>


namespace FC 
{
/**
 * @brief 禁止MessageQueueCapture，如果针对一些qDebug、qInfo不想被捕获的，可以调用此函数，次数消息不会推入队列中，但会被spdlog写入文件中
 */

void FCMESSAGEHANDLER_API daDisableMessageQueueCapture();
/**
   @brief 允许MessageQueueCapture
 */
void FCMESSAGEHANDLER_API daEnableMessageQueueCapture();

/**
   @brief 判断当前是否运行消息捕获
   @return
 */
bool FCMESSAGEHANDLER_API daIsEnableMessageQueueCapture();

// 注册控制台的消息处理
void FCMESSAGEHANDLER_API daRegisterConsolMessageHandler(int flush_every_sec = 1, bool async_logger = true);

// 注册一个旋转文件的消息处理
void FCMESSAGEHANDLER_API daRegisterRotatingMessageHandler(const QString& filename,
                                                           int maxfile_size    = 1048576 * 10,
                                                           int maxfile_counts  = 5,
                                                           int flush_every_sec = 15,
                                                           bool output_stdout  = true,
                                                           bool async_logger   = true);
void FCMESSAGEHANDLER_API daRegisterRotatingMessageHandler(const std::string& filename,
                                                           int maxfile_size    = 1048576 * 10,
                                                           int maxfile_counts  = 5,
                                                           int flush_every_sec = 15,
                                                           bool output_stdout  = true,
                                                           bool async_logger   = true);
/**
 * @brief 设置消息的模板
 *
 * da消息占位符有如下：
 *
 * - {level} 代表是否打印消息等级，消息等级有debug/warn/critical/error/info五种
 * - {datetime} 代表日期
 * - {line} 代表打印行号
 * - {fun} 代表打印函数名
 * - {file} 代表打印文件名
 * - {msg} 代表消息主体
 * @param p patter字符串，默认为[{datetime}][{line}]{msg}
 */
void FCMESSAGEHANDLER_API daSetMessagePattern(const QString& p);

/**
 * @brief 设置记录进入全局消息队列的消息等级，默认为QtWarningMsg
 * @sa QtMsgType
 * @param type
 */
void FCMESSAGEHANDLER_API daSetMsgQueueRecordMsgType(QtMsgType type);

/**
 * @brief 注销
 * @note 最后需要调用此函数进行释放
 */
void FCMESSAGEHANDLER_API daUnregisterMessageHandler();
} // namespace FC



#endif // FCMESSAGEHANDLER_H
