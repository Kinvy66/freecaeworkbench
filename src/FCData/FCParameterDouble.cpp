/**
 * @file FCParameterDouble.cpp
 * @brief 双精度浮点类型参数
 * @date 2025-11-28
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCParameterDouble.h"

namespace FC 
{

FCParameterDouble::FCParameterDouble()
    : FCParameterBase(Para_Double)
{
    _range[0] = -1e66;
    _range[1] = 1e66;
}

void FCParameterDouble::setValue(double v)
{
    if (fabs(v - _value) > 0.00000001)
    {
        _value = v;
        emit dataChanged();
    }
    
}
double FCParameterDouble::getValue()
{
    return _value;
}
void FCParameterDouble::setAccuracy(int a)
{
    _accuracy = a;
}
int FCParameterDouble::getAccuracy()
{
    return _accuracy;
}
void FCParameterDouble::setRange(double* range)
{
    _range[0] = range[0];
    _range[1] = range[1];
}
void FCParameterDouble::getRange(double* range)
{
    range[0] = _range[0];
    range[1] = _range[1];
}
void FCParameterDouble::setUnit(QString u)
{
    _unit = u;
}
QString FCParameterDouble::getUnit()
{
    return _unit;
}

void FCParameterDouble::copy(FCParameterBase* ori, bool valueOnly)
{
    FCParameterBase::copy(ori,valueOnly);
    FCParameterDouble* p = dynamic_cast<FCParameterDouble*> (ori);
    if (p != nullptr)
    {
        double v = p->getValue();
        this->setValue(v);
        if (valueOnly) return;
        _accuracy = p->getAccuracy();
        _unit = p->getUnit();
        p->getRange(_range);
    }
    
}

bool FCParameterDouble::isSameValueWith(FCParameterBase* p)
{
    bool same = false;
    FCParameterDouble* pd = dynamic_cast<FCParameterDouble*>(p);
    if (pd != nullptr)
    {
        double v = pd->getValue();
        if (fabs(v- _value) <0.00000001)
            same = true;
    }
    return same;
}

QString FCParameterDouble::valueToString()
{
    QString format = QString("%.%1f").arg(_accuracy);
    QByteArray ba = format.toLatin1();
    
    QString v = QString::asprintf(ba.data(), _value);
    return v;
}

void FCParameterDouble::setValueFromString(QString v)
{
    double value = v.toDouble();
    this->setValue(value);
}

} // namespace FC
