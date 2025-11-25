#include "InteractorDefaultStyle.h"
#include <vtkActor.h>
#include <vtkSmartPointer.h>


namespace FC 
{

InteractorDefaultStyle::InteractorDefaultStyle()
    :QObject(), vtkInteractorStyleRubberBandPick()
{
    // _actor = nullptr;
}

InteractorDefaultStyle::~InteractorDefaultStyle()
{
    
}

InteractorDefaultStyle *InteractorDefaultStyle::New()
{
    return new InteractorDefaultStyle; 
}


} // namespace name

