#include "FCComponentInterface.h"

namespace FC 
{
FCComponentInterface::~FCComponentInterface()
{
    //析构，清理数据，会收内存
}

void FCComponentInterface::init()
{
    //注册接口等操作
}

QWidget* FCComponentInterface::getWidget(const int indexPort)
{
    //错误值
    return nullptr;
}

QString FCComponentInterface::getComponentName()
{
    //抽象类，错误值
    return QString();
}

bool FCComponentInterface::exec(const int indexPort)
{
    return false;
}

void FCComponentInterface::setComponentObjName(const QString & name)
{
    //名称
    _compObjName = name;
}

QString FCComponentInterface::getComponentObjName() const
{
    return _compObjName;
}

CallBackFuns FCComponentInterface::getCallBackFuns(int key)
{
    if (_callBackFuns.contains(key))
        return _callBackFuns[key];
    return nullptr;
}

void FCComponentInterface::setCallBackFuns(int k, CallBackFuns f)
{
    _callBackFuns.insert(k, f);
}

void FCComponentInterface::removeCallBackFun(int k)
{
    _callBackFuns.remove(k);
}

void FCComponentInterface::setDataObject(const QString& name, QObject* data)
{
    _dataObjects[name] = data;
}

QObject* FCComponentInterface::getDataObject(const QString& name)
{
    return _dataObjects.value(name);
}

void FCComponentInterface::resetDataObjects()
{
    _dataObjects.clear();
}

QList<int> FCComponentInterface::getUnResetDataObj()
{
    return QList<int>();
}
} // namespace FC
