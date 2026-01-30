#include "FCVarientParams.h"

namespace FC 
{
void FCVarientParams::setValue(const QString& k, const QVariant v)
{
    // 使用_insert方法将键k和值v插入到_settings哈希表中。
    _settings.insert(k, v);
}

QVariant FCVarientParams::getValue(const QString& k) const
{
    // 直接调用_settings哈希表的value方法，传入键k，返回与其对应的QVariant值。
    // 如果键k不存在，则可能返回一个默认初始化的QVariant。
    return _settings.value(k);
}

void FCVarientParams::removeVarient(const QString & k)
{
    _settings.remove(k);
}

void FCVarientParams::clear()
{
    _settings.clear();
}
} // namespace FC
