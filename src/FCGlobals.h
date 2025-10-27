#ifndef FCGLOBALS_H
#define FCGLOBALS_H
#include <QScopedPointer>
#include <QHash>
#include <memory>
#include <QString>
#include "FCConfigs.h"
#ifndef FC_VERSION_MAJ
#define FC_VERSION_MAJ 0
#endif
#ifndef FC_VERSION_MIN
#define FC_VERSION_MIN 0
#endif
#ifndef FC_VERSION_PAR
#define FC_VERSION_PAR 4
#endif
/**
 *@def FC_IMPL_FORWARD_DECL
 *@brief 前置声明的定义
 */
#ifndef FC_IMPL_FORWARD_DECL
#define FC_IMPL_FORWARD_DECL(ClassName) class ClassName##Private;
#endif

/**
 *@def FC_IMPL_FORWARD_DECL_NS
 *@brief 前置声明的定义(带命名空间)
 */
#ifndef FC_IMPL_FORWARD_DECL_NS
#define FC_IMPL_FORWARD_DECL_NS(NS, ClassName)                                                                         \
	namespace NS                                                                                                       \
	{                                                                                                                  \
	class ClassName##Private;                                                                                          \
	}
#endif

/**
 *@def FC_IMPL
 *@brief impl的简易实现
 */
#ifndef FC_IMPL
#define FC_IMPL(Class)                                                                                                 \
private:                                                                                                               \
	inline Class##Private* d_func()                                                                                    \
	{                                                                                                                  \
		return (d_ptr.data());                                                                                         \
	}                                                                                                                  \
	inline const Class##Private* d_func() const                                                                        \
	{                                                                                                                  \
		return (d_ptr.data());                                                                                         \
	}                                                                                                                  \
	friend class Class##Private;                                                                                       \
	QScopedPointer< Class##Private > d_ptr;
#endif

/**
 *@def FC_IMPL_PUBLIC
 *@brief impl的定义
 */
#ifndef FC_IMPL_PUBLIC
#define FC_IMPL_PUBLIC(Class)                                                                                          \
	inline Class* q_func()                                                                                             \
	{                                                                                                                  \
		return (static_cast< Class* >(q_ptr));                                                                         \
	}                                                                                                                  \
	inline const Class* q_func() const                                                                                 \
	{                                                                                                                  \
		return (static_cast< const Class* >(q_ptr));                                                                   \
	}                                                                                                                  \
	friend class Class;                                                                                                \
	Class* q_ptr;
#endif

/**
 * @def FC_DECLARE_PRIVATE
 * @brief 模仿Q_DECLARE_PRIVATE，但不用前置声明而是作为一个内部类
 *
 * 例如:
 *
 * @code
 * //header
 * class A
 * {
 *  FC_DECLARE_PRIVATE(A)
 * };
 * @endcode
 *
 * 其展开效果为：
 *
 * @code
 * class A{
 *  class PrivateData;
 *  friend class A::PrivateData;
 *  std::unique_ptr< PrivateData > d_ptr;
 * }
 * @endcode
 *
 * 这样前置声明了一个内部类PrivateData，在cpp文件中建立这个内部类的实现
 *
 * @code
 * //cpp
 * class A::PrivateData{
 *  FC_DECLARE_PUBLIC(A)
 *  PrivateData(A* p):q_ptr(p){
 *  }
 * };
 *
 * A::A():d_ptr(new PrivateData(this)){
 * }
 * @endcode
 *
 */
#ifndef FC_DECLARE_PRIVATE
#define FC_DECLARE_PRIVATE(classname)                                                                                  \
	class PrivateData;                                                                                                 \
	friend class classname::PrivateData;                                                                               \
	std::unique_ptr< PrivateData > d_ptr;                                                                              \
	inline PrivateData* d_func()                                                                                       \
	{                                                                                                                  \
		return (d_ptr.get());                                                                                          \
	}                                                                                                                  \
	inline const PrivateData* d_func() const                                                                           \
	{                                                                                                                  \
		return (d_ptr.get());                                                                                          \
	}
#endif

/**
 * @def FC_DECLARE_PUBLIC
 * @brief 模仿Q_DECLARE_PUBLIC
 *
 * 配套FC_DECLARE_PRIVATE使用
 */
#ifndef FC_DECLARE_PUBLIC
#define FC_DECLARE_PUBLIC(classname)                                                                                   \
	friend class classname;                                                                                            \
	classname* q_ptr { nullptr };                                                                                      \
	inline classname* q_func()                                                                                         \
	{                                                                                                                  \
		return (static_cast< classname* >(q_ptr));                                                                     \
	}                                                                                                                  \
	inline const classname* q_func() const                                                                             \
	{                                                                                                                  \
		return (static_cast< const classname* >(q_ptr));                                                               \
	}
#endif

/**
 * @def  FC_PIMPL_CONSTRUCT
 *
 * 配套FC_DECLARE_PRIVATE使用,在构造函数中构建privatedata
 */
#ifndef FC_PIMPL_CONSTRUCT
#define FC_PIMPL_CONSTRUCT d_ptr(std::make_unique< PrivateData >(this))
#endif

/**
 *@def FC_D
 *@brief impl获取指针，参考Q_D
 */
#ifndef FC_D
#define FC_D(pointerName) PrivateData* pointerName = d_func()
#endif

/**
 *@def FC_DC
 *@brief impl获取指针，参考Q_D
 */
#ifndef FC_DC
#define FC_DC(pointerName) const PrivateData* pointerName = d_func()
#endif

/**
 *@def FC_Q
 *@brief impl获取指针，参考Q_Q
 */
#ifndef FC_Q
#define FC_Q(classname, pointerName) classname* pointerName = q_func()
#endif

/**
 *@def FC_QC
 *@brief impl获取指针，参考Q_Q
 */
#ifndef FC_QC
#define FC_QC(classname, pointerName) const classname* pointerName = q_func()
#endif

/**
 *@def Qt5Qt6Compat_QXXEvent_Pos
 *@brief QXXEvent_Pos函数的兼容宏
 *
 *'pos' is deprecated: Use position().toPoint()
 *
 *qevent.h:740:5: note: 'pos' has been explicitly marked deprecated here
 *
 *qglobal.h:369:44: note: expanded from macro 'QT_DEPRECATED_VERSION_X_6_0'
 *
 *qglobal.h:281:33: note: expanded from macro 'QT_DEPRECATED_X'
 *
 */
#ifndef Qt5Qt6Compat_QXXEvent_Pos
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#define Qt5Qt6Compat_QXXEvent_Pos(valuePtr) valuePtr->pos()
#else
#define Qt5Qt6Compat_QXXEvent_Pos(valuePtr) valuePtr->position().toPoint()
#endif
#endif

/**
 *@def Qt5Qt6Compat_QXXEvent_x
 *@brief QXXEvent_x函数的兼容宏
 *
 * warning: 'int QMouseEvent::x() const' is deprecated: Use position()
 *
 * QMouseEvent::x
 */
#ifndef Qt5Qt6Compat_QXXEvent_x
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#define Qt5Qt6Compat_QXXEvent_x(valuePtr) valuePtr->pos().x()
#else
#define Qt5Qt6Compat_QXXEvent_x(valuePtr) valuePtr->position().x()
#endif
#endif

/**
 *@def Qt5Qt6Compat_QXXEvent_y
 *@brief QXXEvent_y函数的兼容宏
 *
 * warning: 'int QMouseEvent::y() const' is deprecated: Use position()
 *
 * QMouseEvent::y
 */
#ifndef Qt5Qt6Compat_QXXEvent_y
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#define Qt5Qt6Compat_QXXEvent_y(valuePtr) valuePtr->pos().y()
#else
#define Qt5Qt6Compat_QXXEvent_y(valuePtr) valuePtr->position().y()
#endif
#endif
/**
 * @def Qt5Qt6Compat_fontMetrics_width
 * @brief QFontMetrics的字体宽度适配
 */
#ifndef Qt5Qt6Compat_fontMetrics_width
#if QT_VERSION < QT_VERSION_CHECK(5, 12, 0)
#define Qt5Qt6Compat_fontMetrics_width(fontMeter, str) fontMeter.width(str)
#else
#define Qt5Qt6Compat_fontMetrics_width(fontMeter, str) fontMeter.horizontalAdvance(str)
#endif
#endif

#ifndef Qt5Qt6Compat_Connect_ButtonGroupClicked_int
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#define Qt5Qt6Compat_Connect_ButtonGroupClicked_int(buttonGroup, funName)                                              \
	do {                                                                                                               \
		connect(buttonGroup, QOverload< int >::of(&QButtonGroup::buttonClicked), this, &funName);                      \
	} while (0)
#else
#define Qt5Qt6Compat_Connect_ButtonGroupClicked_int(buttonGroup, funName)                                              \
	do {                                                                                                               \
		connect(buttonGroup, &QButtonGroup::idClicked, this, &funName);                                                \
	} while (0)
#endif
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
template< typename T >
uint qHash(const std::shared_ptr< T >& ptr, uint seed = 0)
{
	return qHash(ptr.get(), seed);
}
#endif  // QT_VERSION < QT_VERSION_CHECK(5, 15, 0)

/**
 * @def 自动注册元类型，在cpp文件中使用，避免在头文件中使用
 *
 * MyClass.cpp
 * @code
 * FC_AUTO_REGISTER_META_TYPE(MyClass)
 * @endcode
 *
 * @note 注意，此宏应该写在命名空间之外，注册的参数如果在命名空间需带上完整的命名空间，例如
 * @code
 * //MyClass.h
 * namespace FC{
 * class MyClass{
 * };
 * }
 * Q_DECLARE_METATYPE(FC::MyClass)
 *
 * // MyClass.cpp
 * namespace FC{
 * ....
 * }
 *
 * FC_AUTO_REGISTER_META_TYPE(FC::MyClass)
 * @endcode
 */
#ifndef FC_AUTO_REGISTER_META_TYPE
#define FC_CONCAT_(a, b) a##b
#define FC_CONCAT(a, b) FC_CONCAT_(a, b)
#define FC_MAKE_UNIQUE_NAME(base) FC_CONCAT(base, __LINE__)
#define FC_AUTO_REGISTER_META_TYPE(Type)                                                                               \
	namespace                                                                                                          \
	{                                                                                                                  \
	static const struct FC_MAKE_UNIQUE_NAME(FC_MetaTypeRegistrar_)                                                     \
	{                                                                                                                  \
		inline FC_MAKE_UNIQUE_NAME(FC_MetaTypeRegistrar_)()                                                            \
		{                                                                                                              \
			qRegisterMetaType< Type >();                                                                               \
		}                                                                                                              \
	} FC_MAKE_UNIQUE_NAME(FC_MetaTypeRegistrar_instance_);                                                             \
	}
#endif

#endif  // GLOBALS_H
