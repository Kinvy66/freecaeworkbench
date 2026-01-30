/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraphOperator.h"

namespace Comp
{
    FCGraphOperator::FCGraphOperator()
    {

    }

    FCGraphOperator::~FCGraphOperator()
    {

    }
   
    void FCGraphOperator::setGraph3DWindow(FCGraph3DWindowVTK* w)
    {
        //设置三维渲染窗口
        m_graph3DWindow = w;
    }

    Comp::FCGraph3DWindowVTK* FCGraphOperator::getGraph3DWindow()
    {
        //返回渲染窗口
        return m_graph3DWindow;
    }

}