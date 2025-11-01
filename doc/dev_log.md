# 开发日志



## Part 1: 与CMake斗智斗勇



#### 1. 子模块无法生成lib文件，导致无法link （20251029）

在写`FCGui` 模块时，完成了该模块下的一个类时，进行编译，出现无法link `FGui.lib` ,查看发现没有生成lib文件，但是单独编译该模块又没有任何错误，可以编译通过。下面是该模块下唯一的类的头文件：

```cpp
#ifndef FCMESSAGELOGVIEWWIDGET_H
#define FCMESSAGELOGVIEWWIDGET_H

#include <QWidget>
#include "FCGuiAPI.h"
class QMenu;

namespace Ui {
class FCMessageLogViewWidget;
}

namespace FC 
{
class FCMessageLogViewWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FCMessageLogViewWidget(QWidget *parent = nullptr);
    ~FCMessageLogViewWidget();
    
private:
    Ui::FCMessageLogViewWidget *ui;
};
} // namespace FC

#endif // FCMESSAGELOGVIEWWIDGET_H
```

原因：**msvc编译器默认是不会生成符号表的**，该子模块下又只有一个类，这个类没有声明导出符号表，自然就无c法生成对应lib，工程中的其他模块又依赖该模块，自然编译就会出现link错误。

解决方法：

1. 在类声明时使用qt的  `Q_DECL_EXPORT` 宏导出符号表

   ```cpp
   class Q_DECL_EXPORT FCMessageLogViewWidget : public QWidget
   ```

 2. 在cmake文件中设置导出符号表选项

    ```cmake
    if(MSVC)
    	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    	set(BUILD_SHARED_LIBS TRUE)
    endif()
    ```

    



## Part2: C++是最好的编程语言

#### 1. Qt的 D-Pointer原理 ，PIMPL(pointer to implementation) 设计模式

*TODO*

```c++
#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() noexcept \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr));) } \
    inline const Class##Private* d_func() const noexcept \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr));) } \
    friend class Class##Private;

```



```c++
#define Q_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() noexcept { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const noexcept { return static_cast<const Class *>(q_ptr); } \
    friend class Class; \
    friend const QObject *QtPrivate::getQObject(const QObjectPrivate *d); \
    template <typename ObjPrivate> friend void QtPrivate::assertObjectType(QObjectPrivate *d);
```

