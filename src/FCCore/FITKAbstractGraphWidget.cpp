/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FITKAbstractGraphWidget.h"

namespace Core
{

    FITKAbstractGraphWidget::FITKAbstractGraphWidget(QWidget* parent /*= nullptr*/)
        :FITKWidget(parent)
    {
        static int viewPortID = 0;
        _graphWidgetID = ++viewPortID;
    }

    FITKAbstractGraphWidget::~FITKAbstractGraphWidget()
    {

    }

    void FITKAbstractGraphWidget::clear()
    {
        // TODO
    }
 
    void FITKAbstractGraphWidget::saveImage(const QString& image, int w /*= -1*/, int h /*= -1*/)
    {
        // TODO
    }

    void FITKAbstractGraphWidget::fitView()
    {
        //TODO
    }

    void FITKAbstractGraphWidget::setBackgroundColor(float* rgb1, float* rgb2)
    {
        //TODO 
    }

    void FITKAbstractGraphWidget::getBackgroundColor(float* rgb1, float* rgb2 /*= nullptr*/)
    {
        //TODO
    }

    void FITKAbstractGraphWidget::removeGraphObj(FITKAbstractGraphObject* gobj)
    {

    }


    int FITKAbstractGraphWidget::getGraphWidgetID() const
    {
        return _graphWidgetID;
    }

    FITKAbstractGraph3DWidget::~FITKAbstractGraph3DWidget()
    {

    }

    void FITKAbstractGraph3DWidget::setView(double * focalPoint, double * viewUp, double * position)
    {
        // TODO
    }

    void FITKAbstractGraph3DWidget::setView(FITKGraph3DStandardView v)
    {

    }

    bool FITKAbstractGraph3DWidget::getView(double * pos, double * focual, double * viewup)
    {
        return false;
    }

    void FITKAbstractGraph3DWidget::setParallelProjection(bool on /*= true*/)
    {

    }

    FITKAbstractGraph2DWidget::~FITKAbstractGraph2DWidget()
    {

    }

}