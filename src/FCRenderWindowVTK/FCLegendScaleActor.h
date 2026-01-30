/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/*****************************************************************//**
 * @file        FCLegendScaleActor.h
 * @brief       Scale actor with a single legend.
 *  
 * @author      ChengHaotian (yeguangbaozi@foxmail.com)
 * @date        2024-05-28
 *********************************************************************/

#ifndef FCLegendScaleActor_h
#define FCLegendScaleActor_h

#include "vtkCoordinate.h" // For vtkViewportCoordinateMacro
#include "vtkProp.h"
#include "vtkRenderingAnnotationModule.h" // For export macro

#include "FCRenderWindowVTKAPI.h"

class vtkAxisActor2D;
class vtkTextProperty;
class vtkPolyData;
class vtkPolyDataMapper2D;
class vtkActor2D;
class vtkTextMapper;
class vtkPoints;
class vtkCoordinate;

class FCRENDERWINDOWVTK_API FCLegendScaleActor : public vtkProp
{
public:
    /**
     * Instantiate the class.
     */
    static FCLegendScaleActor* New();

    //@{
    /**
     * Standard methods for the class.
     */
    vtkTypeMacro(FCLegendScaleActor, vtkProp);
    void PrintSelf(ostream& os, vtkIndent indent) override;
    //@}

    //@{
    /**
     * These are methods to retrieve the vtkAxisActors used to represent
     * the four axes that form this representation. Users may retrieve and
     * then modify these axes to control their appearance.
     */
    vtkGetObjectMacro(BottomAxis, vtkAxisActor2D);
    //@}

    //@{
    /**
     * Standard methods supporting the rendering process.
     */
    virtual void BuildRepresentation(vtkViewport* viewport);
    void GetActors2D(vtkPropCollection*) override;
    void ReleaseGraphicsResources(vtkWindow*) override;
    int RenderOverlay(vtkViewport*) override;
    int RenderOpaqueGeometry(vtkViewport*) override;
    //@}

protected:
    FCLegendScaleActor();
    ~FCLegendScaleActor() override;

    // The four axes around the borders of the renderer
    vtkAxisActor2D* BottomAxis;

    // Control the display of the axes
    vtkTypeBool BottomAxisVisibility;

    // Support for the legend.
    vtkPolyData* Legend;
    vtkPoints* LegendPoints;
    vtkPolyDataMapper2D* LegendMapper;
    vtkActor2D* LegendActor;
    vtkPolyData* LegendBorder;
    vtkPolyDataMapper2D* LegendBorderMapper;
    vtkActor2D* LegendBorderActor;
    vtkTextMapper* LabelMappers[5];
    vtkActor2D* LabelActors[5];
    vtkTextProperty* LegendLabelProperty;
    vtkCoordinate* Coordinate;

    vtkTimeStamp BuildTime;

private:
    FCLegendScaleActor(const FCLegendScaleActor&) = delete;
    void operator=(const FCLegendScaleActor&) = delete;
};

#endif
