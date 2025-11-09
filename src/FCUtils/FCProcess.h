/******************************************************************************
 * File     : FCProcess.cpp
 * Brief    : 对QProcess的封装
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-09
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
