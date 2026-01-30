/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 *
 * @file FITKAbstractGraphObject.h
 * @brief 显示对象与显示对象管理器声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-04-18
 *
 */
#ifndef _FITKABSTRACTGRAPH_OBJECT_H__
#define _FITKABSTRACTGRAPH_OBJECT_H__

#include <QObject>
#include "FITKAbstractObject.hpp"
#include "FITKCoreAPI.h"
#include <QList>

#ifndef FITKGraphObjectRegist
#define FITKGraphObjectRegist( \
    thisClass, superclass) \
protected: \
    virtual const char* GetClassName() const { return #thisClass; } \
public: \
    typedef superclass Superclass; \
    static thisClass* SafeDownCast(Core::FITKAbstractGraphObject* o) \
    { \
        return dynamic_cast<thisClass*>(o); \
    }
#endif // !FITKGraphObjectRegist

namespace Core
{
    class FITKAbstractDataObject;
    class FITKAbstractGraphWidget;

    /**
     * @brief 显示对象抽象类
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-18
     */
    class FITKCoreAPI FITKAbstractGraphObject
        :public QObject,  public FITKAbstractObject
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param data 数据对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        explicit FITKAbstractGraphObject(FITKAbstractDataObject* data);
        /**
         * @brief Destroy the FITKAbstractGraphObject object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual ~FITKAbstractGraphObject() = 0;
        /**
         * @brief 设置数据对象
         * @param[i]  dataobj        数据对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        void setDataObject(FITKAbstractDataObject* dataobj);
        /**
         * @brief 记录显示窗口
         * @param[i]  gwidget       显示窗口
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        void setGraphWidget(FITKAbstractGraphWidget* gwidget );
        /**
         * @brief 获取显示对象所在的窗口
         * @return FITKAbstractGraphWidget*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        FITKAbstractGraphWidget* getGraphWidget();
        /**
         * @brief 获取数据对象
         * @return FITKAbstractDataObject*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        FITKAbstractDataObject* getDataOject();
        /**
         * @brief 从显示窗口移除
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void removeFromGraphWidget();
        /**
         * @brief 更新对象
         * @param[i]  mandatory       是否强制更新
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void update(bool  mandatory = false);

    signals:
        /**
         * @brief 显示对象被释放信号，析构函数调用发出
         * @param[i]  gobj           显示对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        void graphObjDestroyedSig(FITKAbstractGraphObject* gobj);

    protected:
        /**
         * @brief 数据对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        FITKAbstractDataObject* _dataObj{};
        /**
         * @brief 显示窗口对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        FITKAbstractGraphWidget* _graphWidget{};
    };

    /**
     * @brief 显示对象管理器抽象类  不会delete对象
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-18
     */
    class FITKCoreAPI FITKGraphObjManager
        : public QObject, public FITKAbstractObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Construct a new FITKGraphObjManager object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        explicit FITKGraphObjManager() = default;
        /**
         * @brief Destroy the FITKGraphObjManager object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual ~FITKGraphObjManager();
        /**
         * @brief 清空管理器
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void clear();
        /**
         * @brief 追加显示对象
         * @param[i]  gobj           显示对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void appendGraphObj(FITKAbstractGraphObject* gobj);
        /**
         * @brief 移除显示对象
         * @param[i]  obj            显示对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void removeGraphObj(FITKAbstractGraphObject* obj);
            /**
         * @brief 移除显示对象
         * @param[i]  index          显示对象索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void removeGraphObj(const int index);
        /**
         * @brief 是否包含显示对象
         * @param[i]  gobj          显示对象
         * @return true
         * @return false
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual bool isContains(FITKAbstractGraphObject* gobj);
        /**
         * @brief 获取显示对象数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        int getGraphObjCount();
        /**
         * @brief 获取显示对象
         * @param[i]  index          显示对象索引
         * @return FITKAbstractGraphObject*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        FITKAbstractGraphObject* getGraphObjAt(const int index);

        template <class T>
        /**
         * @brief 获取显示对象
         * @param[i]  index          显示对象索引
         * @return T*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        T* getGraphObjTAt(const int index)
        {
            return dynamic_cast<T*>(this->getGraphObjAt(index));
        }

    private slots:
        /**
         * @brief  移除显示对象，关联显示对象的析构发出的信号
         * @param[i]  obj            显示对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        void removeGraphObjSlot(FITKAbstractGraphObject* obj);

    protected:
        /**
         * @brief 显示对象列表
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        QList<FITKAbstractGraphObject*> _graphObjList{};
    };


}



#endif // !_FITKABSTRACTGRAPH_OBJECT_H__
