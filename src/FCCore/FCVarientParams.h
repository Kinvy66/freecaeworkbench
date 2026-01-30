#ifndef FCVARIENTPARAMS_H
#define FCVARIENTPARAMS_H

#include "FCCoreAPI.h"
#include <QHash>
#include <QString>
#include <QVariant>
    
namespace FC
{
/**
 * @brief 参数管理
 * @author libaojun (libaojunqd@Foxmail.com)
 * @date 2024-04-10
 */
class  FCCORE_API FCVarientParams
{
public:
    /**
     * @brief Construct a new FCRunTimeSetting object
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-10
     */
    explicit FCVarientParams() = default;
    /**
     * @brief Destroy the FCRunTimeSetting object
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-10
     */
    virtual ~FCVarientParams() = default;
    /**
     * @brief 设置参数
     * @param[i]  k              关键字
     * @param[i]  v              值
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-10
     */
    void setValue(const QString& k, const QVariant  v);
    /**
     * @brief 获取参数
     * @param[i]  k              关键字
     * @return QVariant          值
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-10
     */
    QVariant getValue(const QString& k) const;
    
    template <typename T>
    /**
     * @brief 获取参数
     * @param[i]  k              关键字
     * @return T                 值
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-10
     */
    T getValueT(const QString& k) const
    {
        QVariant v = this->getValue(k);
        return v.value<T>();
    }
    
    /**
     * @brief 移除参数
     * @param[i]  k              关键字
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-18
     */
    void removeVarient(const QString & k);
    /**
     * @brief 清空参数
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-18
     */
    void clear();
    
private:
    /**
     * @brief 参数链表
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-04-10
     */
    QHash<QString, QVariant> _settings;
    
};
    
}


#endif // FCVARIENTPARAMS_H
