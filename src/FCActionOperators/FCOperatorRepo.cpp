/**
 * @file FCOperatorRepo.cpp
 * @brief 操作器仓库声明
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#include "FCOperatorRepo.h"
#include "FCOperatorRepoPrivate.h"
#include <QMutexLocker>

namespace FC
{
class FCOperatorDeletor
{
public:
    FCOperatorDeletor() = default;
    ~FCOperatorDeletor()
    {
        auto p = FCOPERREPO->_private;
        delete p;
        FCOPERREPO->_private = nullptr;
    }
};

static FCOperatorDeletor __OPER_DELEATOR__;
FCOperatorRepo* FCOperatorRepo::_instance = nullptr;
QMutex FCOperatorRepo::m_mutex;

FCAbstractOperatorBase* FCOperatorRepo::getOperator(const QString& key)
{
    QMutexLocker locker(&m_mutex);
    return _private->getOperator(key);
}

void FCOperatorRepo::removeOperator(const QString& key, bool removeFun)
{
    QMutexLocker locker(&m_mutex);
    _private->removeOperator(key, removeFun);
}

void FCOperatorRepo::registerOperatorFunction(const QString& key, std::function<FCAbstractOperatorBase*()> fun)
{
    QMutexLocker locker(&m_mutex);
    _private->registerOperatorFunction(key, fun);
}

void FCOperatorRepo::initialize()
{
    _private = new FCOperatorRepoPrivate(_createFuns);
}

void FCOperatorRepo::finalize()
{
}
}
