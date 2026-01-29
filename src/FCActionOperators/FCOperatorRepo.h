/**
 * @file FCOperatorRepo.h
 * @brief 操作器仓库声明
 * @date 2026-01-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2026 Kinvy. All rights reserved.
 */
#ifndef __FC_OPERATOR_REPO_H__
#define __FC_OPERATOR_REPO_H__

#include "FCActionOperatorsAPI.h"
#include "FCOperatorRepoMacros.h"
#include "FCAbstractOperatorBase.h"
#include <QObject>
#include <QMutex>
#include <QHash>
#include <functional>
#include <QString>

namespace FC
{
class FCOperatorRepoPrivate;
class FCOperatorDeletor;

/**
 * @brief 操作器仓库（单例，按 key 创建/获取操作器）
 */
class FCACTIONOPERATORS_API FCOperatorRepo : public QObject
{
    friend class FCOperatorDeletor;
    DeclSingleton(FCOperatorRepo)

public:
    FCAbstractOperatorBase* getOperator(const QString& key);

    template <class T>
    T* getOperatorT(const QString& key)
    {
        return dynamic_cast<T*>(getOperator(key));
    }

    void removeOperator(const QString& key, bool removeFun = true);
    void registerOperatorFunction(const QString& key,
                                  std::function<FCAbstractOperatorBase*()> fun);

private:
    void initialize();
    void finalize();

private:
    QHash<QString, std::function<FCAbstractOperatorBase*()>> _createFuns{};
    FCOperatorRepoPrivate* _private{};

public:
    template <typename T>
    class FCOperatorRepoRegHelper
    {
    public:
        explicit FCOperatorRepoRegHelper(QString key)
        {
            auto ins = FCOperatorRepo::getInstance();
            ins->_createFuns.insert(key, [&] { return new T; });
        }
    };
};
}

#ifndef Register2FCOperatorRepo
#define Register2FCOperatorRepo(key, Class, ...)          \
    static FC::FCOperatorRepo::FCOperatorRepoRegHelper<Class> \
        _FCDataIORegHelper_##key##_##Class##__VA_ARGS__(#key)
#endif

#ifndef FCOPERREPO
#define FCOPERREPO  FC::FCOperatorRepo::getInstance()
#endif

#endif
