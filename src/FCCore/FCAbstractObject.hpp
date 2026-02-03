/**
 *
 * @file FCAbstractObject.hpp
 * @brief 抽象对象声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-23
 *
 */
#ifndef _FCABSTRACTOBJ_HPP__
#define _FCABSTRACTOBJ_HPP__

#include "FCCoreAPI.h"
// #include "FCType.h"
#include <QString>
#include <QMetaType>
#include <QVariant>
#include <QList>

namespace Core
{
    class FCAbstractObjectContainerPrivate;
    /**
     * @brief 私有对象，用于处理与容器对象的关系
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-05-10
     */
    class FCCORE_API FCAbstractObjectPrivate
    {
        friend FCAbstractObjectContainerPrivate;
    public:
        /**
         * @brief Construct a new FCAbstractObjectPrivate object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-10
         */
        FCAbstractObjectPrivate() = default;
        /**
         * @brief Destroy the FCAbstractObjectPrivate object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-10
         */
         virtual  ~FCAbstractObjectPrivate() = 0;

    private:
        /**
         * @brief 与数据关联的容器
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-10
         */
        QList<FCAbstractObjectContainerPrivate*> _containers{};
    };

    /**
     * @brief 抽象对象声明
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-02-23
     */
    class /*FCCoreAPI*/ FCAbstractObject : public FCAbstractObjectPrivate
    {

    public:
        /**
         * @brief Construct a new FCAbstractObject object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-23
         */
        explicit FCAbstractObject() = default;
        /**
         * @brief Destroy the FCAbstractObject object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-23
         */
        FCCORE_API virtual ~FCAbstractObject() = 0 ;

        /**
         * @brief 是否为className的类对象
         * @param[i]  className  类名，不包含命名空间
         * @return true
         * @return false
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-04
         */
        virtual bool isFCClass(const QString& className) { Q_UNUSED(className); return false; }
        /**
         * @brief 获取类名，包含命名空间
         * @return QString
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-04
         */
        virtual QString getClassName() { return QString(); }

        template< class T>
        /**
         * @brief 强制转换this对象类型
         * @return T* 转换后的类型指针
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-23
         */
        T* FCSafedownCast()
        {
            return dynamic_cast<T*>(this);
        }

        template< class T>
        /**
         * @brief 强制转换指针类型
         * @param[i]  obj          转换对象
         * @return T* 转换后输出的对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-23
         */
        static T* FCSafedownCast(FCAbstractObject* obj)
        {
            return dynamic_cast<T*>(obj);
        }
        /**
         * @brief 将对象转换为QVarient
         * @return QVariant
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-04
         */
        QVariant FCObj2QVarient()
        {
            return QVariant::fromValue<FCAbstractObject*>(this);
        }

        template <class T>
        /**
         * @brief 将qvarient转化为T对象指针
         * @param[i]  va             qvarient变量
         * @return T*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-04
         */
        static T* QVariant2FCObj(QVariant va)
        {
            return va.value<T*>();
        }
        /**
         * @brief 是否enable
         * @return true
         * @return false
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-13
         */
        bool FCCORE_API isEnable();
        /**
         * @brief 设置enable
         * @param[i]  en  enable
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-13
         */
        void FCCORE_API enable(bool en = true);

    private:
        /**
         * @brief 是否enable
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-13
         */
        bool _objEnable{ true };

    };

}

Q_DECLARE_METATYPE(Core::FCAbstractObject*)

#endif // _FCABSTRACTOBJ_HPP__
