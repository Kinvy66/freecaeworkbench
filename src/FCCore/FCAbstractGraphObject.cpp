/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCAbstractGraphObject.h"
#include "FITKAbstractGraphWidget.h"

namespace Core
{
        /**
     * @brief 构造函数，初始化图形对象。
     * @param data 指向关联数据对象的指针。
     */
    FITKAbstractGraphObject::FITKAbstractGraphObject(FITKAbstractDataObject* data)
        :_dataObj(data)
    {
    }

    /**
     * @brief 析构函数，释放资源并发出图形对象销毁信号。
     */
    FITKAbstractGraphObject::~FITKAbstractGraphObject()
    {
        emit this->graphObjDestroyedSig(this); // 发出图形对象销毁的信号
    }

    /**
     * @brief 设置关联的数据对象。
     * @param dataobj 指向要设置的数据对象的指针。
     */
    void FITKAbstractGraphObject::setDataObject(FITKAbstractDataObject* dataobj)
    {
        _dataObj = dataobj;
    }

    /**
     * @brief 设置关联的图形小部件。
     * @param gwidget 指向要设置的图形小部件的指针。
     */
    void FITKAbstractGraphObject::setGraphWidget(FITKAbstractGraphWidget* gwidget)
    {
        _graphWidget = gwidget;
    }

    /**
     * @brief 获取关联的图形小部件。
     * @return 返回关联的图形小部件的指针。
     */
    Core::FITKAbstractGraphWidget* FITKAbstractGraphObject::getGraphWidget()
    {
        return _graphWidget;
    }

    /**
     * @brief 获取关联的数据对象。
     * @return 返回关联的数据对象的指针。
     */
    Core::FITKAbstractDataObject* FITKAbstractGraphObject::getDataOject()
    {
        return _dataObj;
    }

    /**
     * @brief 从图形小部件中移除当前图形对象。
     * 如果当前图形对象没有关联的图形小部件，则不执行任何操作。
     */
    void FITKAbstractGraphObject::removeFromGraphWidget()
    {
        if (_graphWidget == nullptr) return;
        _graphWidget->removeGraphObj(this);
        _graphWidget = nullptr;
    }

    void FITKAbstractGraphObject::update(bool mandatory /*= false*/)
    {

    }

    /**
     * @brief 析构函数，清除管理的所有图形对象。
     */
    FITKGraphObjManager::~FITKGraphObjManager()
    {
        this->clear(); // 清除管理的所有图形对象
    }

    /**
     * @brief 清除管理的图形对象列表。
     */
    void FITKGraphObjManager::clear()
    {
        _graphObjList.clear(); // 清除图形对象列表
    }
        /**
     * @brief 向图形对象管理器添加一个图形对象。
     * @param gobj 指向要添加的图形对象的指针。
     * 若传入空指针，则不执行任何操作。
     * 添加时建立图形对象销毁信号与管理器的槽函数之间的连接，
     * 以便在图形对象销毁时自动从管理器中移除。
     */
    void FITKGraphObjManager::appendGraphObj(FITKAbstractGraphObject* gobj)
    {
        if (gobj == nullptr) return;
        _graphObjList.append(gobj);
        connect(gobj, SIGNAL(graphObjDestroyedSig(FITKAbstractGraphObject*)),
            this, SLOT(removeGraphObjSlot(FITKAbstractGraphObject*)));
    }

    /**
     * @brief 从图形对象管理器中移除指定图形对象。
     * @param obj 指向要移除的图形对象的指针。
     * 若传入的对象不在管理器中，则不执行任何操作。
     * 移除时断开图形对象销毁信号与管理器槽函数之间的连接。
     */
    void FITKGraphObjManager::removeGraphObj(FITKAbstractGraphObject* obj)
    {
        if (!_graphObjList.contains(obj)) return;
        _graphObjList.removeOne(obj);
        disconnect(obj, SIGNAL(graphObjDestroyedSig(FITKAbstractGraphObject*)),
            this, SLOT(removeGraphObjSlot(FITKAbstractGraphObject*)));
    }

    /**
     * @brief 通过索引从图形对象管理器中移除图形对象。
     * @param index 待移除图形对象的索引位置。
     * 若索引超出有效范围，则按该索引从管理器中移除对应的图形对象。
     */
    void FITKGraphObjManager::removeGraphObj(const int index)
    {
        if (index < 0 || index >= _graphObjList.size())
        {
            this->removeGraphObj(_graphObjList.at(index));
        }
    }

    /**
     * @brief 判断图形对象管理器是否包含指定图形对象。
     * @param gobj 指向待检查的图形对象的指针。
     * @return 如果管理器包含指定图形对象，返回 true；否则返回 false。
     */
    bool FITKGraphObjManager::isContains(FITKAbstractGraphObject* gobj)
    {
        return _graphObjList.contains(gobj);
    }

    /**
     * @brief 获取图形对象管理器中的图形对象数量。
     * @return 返回管理器中当前存储的图形对象数量。
     */
    int FITKGraphObjManager::getGraphObjCount()
    {
        return _graphObjList.size();
    }

    /**
     * @brief 根据索引获取图形对象管理器中存储的图形对象。
     * @param index 待获取图形对象的索引位置。
     * @return 如果索引在有效范围内，返回对应位置的图形对象指针；否则返回 nullptr。
     */
    FITKAbstractGraphObject* FITKGraphObjManager::getGraphObjAt(const int index)
    {
        if (index < 0 || index >= _graphObjList.size())
            return nullptr;
        return  _graphObjList.at(index);
    }

    /**
     * @brief 私有槽函数，用于响应图形对象销毁信号并从管理器中移除相应对象。
     * @param obj 指向被销毁的图形对象的指针。
     */
    void FITKGraphObjManager::removeGraphObjSlot(FITKAbstractGraphObject* obj)
    {
        this->removeGraphObj(obj);
    }
}


