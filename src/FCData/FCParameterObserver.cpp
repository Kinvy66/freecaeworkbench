/**
 * @file FCParameterObserver.cpp
 * @brief 参数观察者
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCParameterObserver.h"
#include "FCParameterBase.h"
#include "FCParameterGroup.h"
#include "FCParameterList.h"
#include <QDebug>

namespace FC 
{

FCParameterObserver::~FCParameterObserver()
{
    QList<FCParameterBase*> plist = _configActive.values();
    for (int i = 0; i < plist.size(); ++i)
    {
        auto p = plist.at(i);
        delete p;
    }
    _configActive.clear();
    plist = _configfollow.values();
    for (int i = 0; i < plist.size(); ++i)
    {
        auto p = plist.at(i);
        delete p;
    }
    _configfollow.clear();
    QList<FCParameterGroup*> gplist = _configfollowGroup.values();
    for (int i = 0; i < gplist.size(); ++i)
    {
        auto p = gplist.at(i);
        delete p;
    }
    _configfollowGroup.clear();
    
    _dataActive.clear();
    _datafollow.clear();
}
    
void FCParameterObserver::appendCofigActive(QString name, FCParameterBase* p)
{
    if (_configActive.contains(name))
    {
        FCParameterBase* o = _configActive.value(name);
        delete o;
    }
    _configActive[name] = p;
}

void FCParameterObserver::appendConfigFollow(QString name, FCParameterBase* p)
{
    if (_configfollow.contains(name))
    {
        FCParameterBase* o = _configfollow.value(name);
        delete o;
    }
    _configfollow[name] = p;
}

void FCParameterObserver::appendConfigFollowGroup(QString name, FCParameterGroup* p)
{
    if (_configfollowGroup.contains(name))
    {
        auto g = _configfollowGroup.value(name);
        delete g;
    }
    _configfollowGroup[name] = p;
}

FCParameterObserver* FCParameterObserver::copy()
{
    FCParameterObserver* observer = new FCParameterObserver;
    QList<QString> names = _configActive.keys();
    for (int i = 0; i < names.size(); ++i)
    {
        QString name = names.at(i);
        auto p = _configActive.value(name);
        auto cp = FCParameterList::copyParameter(p);
        if (cp != nullptr)
            observer->appendCofigActive(name,cp);
    }
    names = _configfollow.keys();
    for (int i = 0; i < names.size(); ++i)
    {
        QString name = names.at(i);
        auto p = _configfollow.value(name);
        auto cp = FCParameterList::copyParameter(p);
        if (cp != nullptr)
            observer->appendConfigFollow(name, cp);
    }
    names = _configfollowGroup.keys();
    for (int i = 0; i < names.size(); ++i)
    {
        QString name = names.at(i);
        auto g = _configfollowGroup.value(name);
        if (g == nullptr) continue;
        FCParameterGroup* cg = new FCParameterGroup;
        cg->copy(g);
        observer->appendConfigFollowGroup(name, cg);
    }
    return observer;
}

void FCParameterObserver::appendDataActive(QString name, FCParameterBase*p)
{
    _dataActive[name] = p;
    connect(p, SIGNAL(dataChanged()), this, SLOT(observe()));
}

void FCParameterObserver::appendDataFollow(QString name, FCParameterBase*p)
{
    _datafollow[name] = p;
}

void FCParameterObserver::appendDataFollowGroup(QString name, FCParameterGroup* p)
{
    _datafollowGroup[name] = p;
}


QStringList FCParameterObserver::getActiveParameterNames()
{
    return _configActive.keys();
}

QStringList FCParameterObserver::getFollowParameterNames()
{
    return _configfollow.keys();
}

QStringList FCParameterObserver::getFollowGroupNames()
{
    //		qDebug() << _configfollowGroup.keys();
    return _configfollowGroup.keys();
}

void FCParameterObserver::removeConfigActive(QString name)
{
    auto para = _configActive.value(name);
    if (para != nullptr)
    {
        delete para;
        _configActive.remove(name);
    }	
}
void FCParameterObserver::removeConfigFollow(QString name)
{
    auto para = _configfollow.value(name);
    if (para != nullptr)
    {
        delete para;
        _configfollow.remove(name);
        
    }
}

void FCParameterObserver::removeConfigFollowGroup(QString name)
{
    auto pg = _configfollowGroup.value(name);
    if (pg != nullptr)
    {
        delete pg;
        _configfollowGroup.remove(name);
    }
}

void FCParameterObserver::observe()
{
    if (check())
    {
        changeStates();
        emit updateDisplay();
    }
    
}

bool FCParameterObserver::check()
{
    bool same = true;
    QStringList activenames = _configActive.keys();
    for (int i = 0; i < activenames.size(); ++i)
    {
        QString name = activenames.at(i);
        auto cp = _configActive.value(name);
        auto dp = _dataActive.value(name);
        if ((cp == nullptr) || (dp == nullptr)) continue;
        if (!cp->isSameValueWith(dp))
        {
            same = false;
            break;
        }
    }
    return same;
}

void FCParameterObserver::changeStates()
{
    QStringList follolwnames = _configfollow.keys();
    for (int i = 0; i < follolwnames.size(); ++i)
    {
        QString name = follolwnames.at(i);
        auto cp = _configfollow.value(name);
        auto dp = _datafollow.value(name);
        if ((cp == nullptr) || (dp == nullptr)) continue;
        dp->copy(cp, true);
        dp->copyStatus(cp);
    }
    follolwnames = _configfollowGroup.keys();
    for (int i = 0; i < follolwnames.size(); ++i)
    {
        QString name = follolwnames.at(i);
        auto cg = _configfollowGroup.value(name);
        auto dg = _datafollowGroup.value(name);
        if ((cg == nullptr) || (dg == nullptr)) continue;
        dg->copyStates(cg);
    }
    
} 


} // namespace name
