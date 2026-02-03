/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

// #include "FCAbstractObjectContainer.hpp"
#include "FCAbstractObject.hpp"
// #include "FCScriptTextRepo.h"

/**
 * ~FCAbstractObjectPrivate()
 * 析构函数，用于清理资源。
 * 此函数不接受参数，也不返回任何值。
 */
Core::FCAbstractObjectPrivate::~FCAbstractObjectPrivate()
{
    // 遍历容器中的所有对象，调用它们的ObjectDestoried函数，然后清空容器
    // {
    //     for (FCAbstractObjectContainerPrivate* c : _containers)
    //         c->ObjectDestoried();
    //     _containers.clear();
    // }
}

Core::FCAbstractObject::~FCAbstractObject()
{

}

bool Core::FCAbstractObject::isEnable()
{
    return  _objEnable;
}

void Core::FCAbstractObject::enable(bool en /*= true*/)
{
    _objEnable = en;
}
