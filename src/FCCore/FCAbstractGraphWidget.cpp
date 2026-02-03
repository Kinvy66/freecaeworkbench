/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCAbstractGraphWidget.h"

namespace Core
{

    FCAbstractGraphWidget::FCAbstractGraphWidget(QWidget* parent /*= nullptr*/)
        :QWidget(parent)
    {
        static int viewPortID = 0;
        _graphWidgetID = ++viewPortID;
    }

    FCAbstractGraphWidget::~FCAbstractGraphWidget()
    {

    }

    void FCAbstractGraphWidget::clear()
    {
        // TODO
    }
 
    void FCAbstractGraphWidget::saveImage(const QString& image, int w /*= -1*/, int h /*= -1*/)
    {
        // TODO
    }

    void FCAbstractGraphWidget::fitView()
    {
        //TODO
    }

    void FCAbstractGraphWidget::setBackgroundColor(float* rgb1, float* rgb2)
    {
        //TODO 
    }

    void FCAbstractGraphWidget::getBackgroundColor(float* rgb1, float* rgb2 /*= nullptr*/)
    {
        //TODO
    }

    void FCAbstractGraphWidget::removeGraphObj(FCAbstractGraphObject* gobj)
    {

    }


    int FCAbstractGraphWidget::getGraphWidgetID() const
    {
        return _graphWidgetID;
    }

    FCAbstractGraph3DWidget::~FCAbstractGraph3DWidget()
    {

    }

    void FCAbstractGraph3DWidget::setView(double * focalPoint, double * viewUp, double * position)
    {
        // TODO
    }

    void FCAbstractGraph3DWidget::setView(FCGraph3DStandardView v)
    {

    }

    bool FCAbstractGraph3DWidget::getView(double * pos, double * focual, double * viewup)
    {
        return false;
    }

    void FCAbstractGraph3DWidget::setParallelProjection(bool on /*= true*/)
    {

    }

    FCAbstractGraph2DWidget::~FCAbstractGraph2DWidget()
    {

    }

}
