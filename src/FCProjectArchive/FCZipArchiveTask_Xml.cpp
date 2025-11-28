/**
 * @file FCZipArchiveTask_Xml.cpp
 * @brief 保存/加载xml文件的任务
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCZipArchiveTask_Xml.h"
#include "FCZipArchive.h"
#include <QDebug>

namespace FC 
{
FCZipArchiveTask_Xml::FCZipArchiveTask_Xml() : FCAbstractArchiveTask()
{
}

FCZipArchiveTask_Xml::FCZipArchiveTask_Xml(const QString& path)
{
    setPath(path);
}

FCZipArchiveTask_Xml::FCZipArchiveTask_Xml(const QString& path, const QDomDocument& doc)
    : FCAbstractArchiveTask()
{
    setPath(path);
    setDomDocument(doc);
}

FCZipArchiveTask_Xml::~FCZipArchiveTask_Xml()
{
}

QDomDocument FCZipArchiveTask_Xml::getDomDocument() const
{
    return mDomDocument;
}

void FCZipArchiveTask_Xml::setDomDocument(const QDomDocument& domDocument)
{
    mDomDocument = domDocument;
}

QString FCZipArchiveTask_Xml::getPath() const
{
    return mPath;
}

void FCZipArchiveTask_Xml::setPath(const QString& path)
{
    mPath = path;
}

bool FCZipArchiveTask_Xml::exec(FCAbstractArchive* archive, FCAbstractArchiveTask::Mode mode)
{
    if (!archive) {
        return false;
    }
    FCZipArchive* zip = static_cast< FCZipArchive* >(archive);
    if (mode == FCAbstractArchiveTask::WriteMode) {
        // 写模式
        if (!zip->isOpened()) {
            if (!zip->create()) {
                qCritical() << QObject::tr("can not create archive at \"%1\",because %2")
                .arg(zip->getBaseFilePath())
                    .arg(zip->getLastErrorString());
                return false;
            }
        }
        QByteArray data = mDomDocument.toByteArray();
        if (data.isEmpty()) {
            qDebug() << QString("create archive error:%1,get null xml data")
                            .arg(zip->getBaseFilePath());
            return false;
        }
        if (!zip->write(mPath, data)) {
            qDebug() << QString("write data to \"%1\" error").arg(mPath);
            return false;
        }
    } else {
        // 读取数据模式
        // 读取数据模式
        if (!zip->isOpened()) {
            if (!zip->open()) {
                qDebug() << QString("open archive error:%1").arg(zip->getBaseFilePath());
                return false;
            }
        }
        if (!zip->contains(mPath)) {
            // 没有这个文件也返回true
            qDebug() << QString("%1 not in archive").arg(mPath);
            return true;
        }
        QByteArray data = zip->read(mPath);
        if (data.isEmpty()) {
            qDebug() << QString("can not read %1 from %2").arg(mPath, zip->getBaseFilePath());
            return false;
        }
        if (!mDomDocument.setContent(data, &mLastErrorString)) {
            qDebug() << QString("can not read %1 from %2,last error string is %3")
                            .arg(mPath, zip->getBaseFilePath(), mLastErrorString);
            return false;
        }
    }
    return true;
}

QString FCZipArchiveTask_Xml::getLastErrorString() const
{
    return mLastErrorString;
}

void FCZipArchiveTask_Xml::setLastErrorString(const QString& lastErrorString)
{
    mLastErrorString = lastErrorString;
}
} // namespace FC
