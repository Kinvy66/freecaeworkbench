/******************************************************************************
 * File     : FCMessageLogItem.h
 * Brief    : 包含了一个信息的所有内容
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-09
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCMESSAGELOGITEM_H
#define FCMESSAGELOGITEM_H
#include <QMetaType>
#include <QDateTime>
#include <memory>
#include "FCMessageHandlerAPI.h"

namespace FC 
{
class FCMESSAGEHANDLER_API FCMessageLogItem
{
public:
    //构造一个无效的
    FCMessageLogItem();
    //构造一个有效的
    FCMessageLogItem(QtMsgType type, const QMessageLogContext& context, const QString& m);
    //拷贝构造
    FCMessageLogItem(const FCMessageLogItem& i);
    //赋值操作
    FCMessageLogItem& operator=(const FCMessageLogItem& i);
    
public:
    bool isValid() const;
    QString datetimeToString(bool showms = false) const;
    const QString& getMsg() const;
    const QString& getFileName() const;
    const QString& getFunctionName() const;
    const QDateTime& getDateTime() const;
    QtMsgType getMsgType() const;
    int getLine() const;
    
private:
    bool mValidFlag;
    QtMsgType mMsgType;
    QString mMsg;
    QDateTime mDatetime;
    QString mFileName;
    QString mFunctionName;
    int mLine;
    
};
} // namespace FC

Q_DECLARE_METATYPE(FC::FCMessageLogItem)

#endif // FCMESSAGELOGITEM_H
