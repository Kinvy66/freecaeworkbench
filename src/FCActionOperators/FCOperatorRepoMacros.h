/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 * @file FCOperatorRepoMacros.h
 * @brief 操作器仓库模块宏定义（含 DeclSingleton）
 */
#ifndef __FC_OPERATOR_REPO_MACROS_H__
#define __FC_OPERATOR_REPO_MACROS_H__

#include <QMutex>
#include <QMutexLocker>

/**
 * @brief 定义单例（与 Core 模块 DeclSingleton 一致，本模块独立使用）
 */
#define DeclSingleton(thisClass)        \
private:                                  \
    static thisClass* _instance;          \
    static QMutex m_mutex;                \
    thisClass() { initialize(); }        \
    ~thisClass() { finalize(); }          \
public:                                   \
    static thisClass* getInstance()       \
    {                                     \
        QMutexLocker l(&m_mutex);         \
        if (_instance == nullptr)        \
            _instance = new thisClass;    \
        return _instance;                 \
    }

#endif
