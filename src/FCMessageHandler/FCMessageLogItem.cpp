/******************************************************************************
 * File     : FCMessageLogItem.cpp
 * Brief    : 包含了一个信息的所有内容
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-09
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCMessageLogItem.h"
//===================================================
// using DA namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

//===================================================
// FCMessageLogItem
//===================================================
FCMessageLogItem::FCMessageLogItem()
    : mValidFlag(false), mMsgType(QtDebugMsg),
    mMsg(""), mDatetime(QDateTime::currentDateTime())
{
    mFileName     = "";
    mFunctionName = "";
    mLine         = -1;
}

FCMessageLogItem::FCMessageLogItem(QtMsgType type,
                                   const QMessageLogContext& context,
                                   const QString& m)
    : mValidFlag(true), mMsgType(type), mMsg(m), mDatetime(QDateTime::currentDateTime())
{
    mFileName     = (context.file ? context.file : "");
    mFunctionName = (context.function ? context.function : "");
    mLine         = context.line;
}

FCMessageLogItem::FCMessageLogItem(const FCMessageLogItem& i)
{
    operator=(i);
}

FCMessageLogItem& FCMessageLogItem::operator=(const FCMessageLogItem& i)
{
    mValidFlag    = i.mValidFlag;
    mMsgType      = i.mMsgType;
    mMsg          = i.mMsg;
    mDatetime     = i.mDatetime;
    mFileName     = i.mFileName;
    mFunctionName = i.mFunctionName;
    mLine         = i.mLine;
    return *this;
}

bool FCMessageLogItem::isValid() const
{
    return mValidFlag;
}

QString FCMessageLogItem::datetimeToString(bool showms) const
{
    return mDatetime.toString(showms ? "yyyy-MM-dd HH:mm:ss.zzz" : "yyyy-MM-dd HH:mm:ss");
}

const QString& FCMessageLogItem::getMsg() const
{
    return mMsg;
}

const QString& FCMessageLogItem::getFileName() const
{
    return mFileName;
}

const QString& FCMessageLogItem::getFunctionName() const
{
    return mFunctionName;
}

QtMsgType FCMessageLogItem::getMsgType() const
{
    return mMsgType;
}

int FCMessageLogItem::getLine() const
{
    return mLine;
}

const QDateTime& FCMessageLogItem::getDateTime() const
{
    return mDatetime;
}
