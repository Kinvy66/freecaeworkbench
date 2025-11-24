/**
 * @file FCProcess.h
 * @brief 对QProcess的封装
 * @date 2025-11-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPROCESS_H
#define FCPROCESS_H

#include <QProcess>
#include "FCUtilsAPI.h"

class QThread;
class QTextStream;

namespace FC 
{

class FCUTILS_API FCProcess : public QProcess
{
    Q_OBJECT 
public:
    FCProcess(QObject *parent = nullptr);
};

} // namespace FC

#endif // FCPROCESS_H
