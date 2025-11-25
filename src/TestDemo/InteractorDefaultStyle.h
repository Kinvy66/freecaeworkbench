#ifndef INTERACTORDEFAULTSTYLE_H
#define INTERACTORDEFAULTSTYLE_H

#include <QObject>
#include <QMetaObject>
#include <vtkInteractorStyleRubberBandPick.h>

class vtkActor;

namespace FC 
{
class InteractorDefaultStyle
    : public QObject , public  vtkInteractorStyleRubberBandPick
{   
    Q_OBJECT

public:
    static InteractorDefaultStyle* New();
    vtkTypeMacro(InteractorDefaultStyle, vtkInteractorStyleRubberBandPick);
    
    InteractorDefaultStyle();
    virtual ~InteractorDefaultStyle();
    
private:
    
    // vtkActor *_actor{};
    
};

} // namespace FC


#endif // INTERACTORDEFAULTSTYLE_H
