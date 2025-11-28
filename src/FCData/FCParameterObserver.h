/**
 * @file FCParameterObserver.h
 * @brief 参数观察者
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPARAMETEROBSERVER_H
#define FCPARAMETEROBSERVER_H
#include "FCDataAPI.h"
#include <QHash>
#include <QString>
#include <QStringList>
#include <QObject>

namespace FC 
{
class FCParameterBase;
class FCParameterGroup;

class FCDATA_API FCParameterObserver : public QObject
{
    Q_OBJECT
public:
    FCParameterObserver() = default;
    ~FCParameterObserver();
    
    FCParameterObserver* copy();
    
    void appendCofigActive(QString name, FCParameterBase* p);
    void appendConfigFollow(QString name, FCParameterBase* p);
    void appendConfigFollowGroup(QString name, FCParameterGroup* p);
    
    void removeConfigActive(QString name);
    void removeConfigFollow(QString name);
    void removeConfigFollowGroup(QString name);
    
    QStringList getActiveParameterNames();
    QStringList getFollowParameterNames();
    QStringList getFollowGroupNames();
    
    void appendDataActive(QString name, FCParameterBase* p);
    void appendDataFollow(QString name, FCParameterBase* p);
    void appendDataFollowGroup(QString name, FCParameterGroup* p);
    
signals:
    void updateDisplay();
    
public slots:
    void observe();
    
private:
    bool check();
    void changeStates();
    
private:
    QHash<QString, FCParameterBase*> _configActive{};
    QHash<QString, FCParameterBase*> _configfollow{};
    QHash<QString, FCParameterGroup*> _configfollowGroup{};
    
    QHash<QString, FCParameterBase*> _dataActive{};
    QHash<QString, FCParameterBase*> _datafollow{};
    QHash<QString, FCParameterGroup*> _datafollowGroup{};
};

} // namespace FC



#endif // FCPARAMETEROBSERVER_H
