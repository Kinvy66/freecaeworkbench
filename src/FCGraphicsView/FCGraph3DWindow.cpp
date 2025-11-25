/**
 * @file FCFCGraph3DWindow.cpp
 * @brief 3D(VTK)渲染窗口
 * @date 2025-11-24
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGraph3DWindow.h"
#include "FCPropPickerInteractionStyle.h"
#include <QDebug>
#include <QColor>
#include <QDir>
#include <assert.h>
// vtk
#include <QVTKOpenGLNativeWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkAxesActor.h>
#include <vtkTextActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkTextWidget.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkScalarBarWidget.h>
#include <vtkScalarBarActor.h>
#include <vtkLookupTable.h>
#include <vtkWindowToImageFilter.h>
#include <vtkImageResize.h>
#include <vtkPNGWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkPolyData.h>
#include <vtkDataSet.h>
#include <vtkAppendFilter.h>
#include <vtkCaptionRepresentation.h>
#include <vtkCaptionActor2D.h>
#include <vtkCaptionWidget.h>
#include <vtkAreaPicker.h>
#include <vtkProperty2D.h>
#include <vtkAppendFilter.h>
#include <vtkVersionMacros.h>

namespace FC 
{


FCGraph3DWindow::FCGraph3DWindow(int id, GraphWindowType type, bool connectToMainwindow)
: FCGraphWindowBase(id, type)
{
    init();
    mRender->GlobalWarningDisplayOff();
    this->setFocusPolicy(Qt::ClickFocus);
    // connect(_mainWindow, SIGNAL(enableGraphWindowKeyBoard(bool)), this, SLOT(enableKeyBoard(bool)));
    // connect(this, SIGNAL(reRenderSig()), this, SLOT(reRender()));
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetParallelProjection(1);
}


FCGraph3DWindow::~FCGraph3DWindow()
{
    // if (mInteractionStyle)
    //     mInteractionStyle->Delete();
}


void FCGraph3DWindow::enableKeyBoard(bool on)
{
#ifdef Q_OS_WIN32
    if (on)
        this->grabKeyboard();
    else
        this->releaseKeyboard();
#endif
}
void FCGraph3DWindow::init()
{
#if VTK_MAJOR_VERSION < 9
    mRenderWindow = mVTKWidget->GetRenderWindow();
#else
    mRenderWindow = mVTKWidget->renderWindow();
#endif
    
    mRender = vtkSmartPointer<vtkRenderer>::New();
    mRender->SetGradientBackground(true);
    // 		_render->SetBackground2(0.0, 0.333, 1.0);
    // 		_render->SetBackground(1.0, 1.0, 1.0);
    mInteractor = mRenderWindow->GetInteractor();
    mRenderWindow->AddRenderer(mRender);
    // if (_graphWindowType == PreWindows)
    // {
    //     FCPropPickerInteractionStyle *style = PropPickerInteractionStyle::New();
    //     style->connectToMainWindow(_mainWindow, this);
    //     style->SetDefaultRenderer(_render);
    //     style->setRender(_render);
    //     style->setRenderWindow(_renderWindow);
    //     _interactor->SetInteractorStyle(style);
    //     vtkSmartPointer<vtkAreaPicker> areaPicker = vtkSmartPointer<vtkAreaPicker>::New();
    //     _interactor->SetPicker(areaPicker);
    //     _interactionStyle = style;
        
    //     //关联信号
    //     //			connect(style, SIGNAL(selectGeometry(bool)), this, SIGNAL(selectGeometry(bool)));
    //     connect(style, SIGNAL(selectGeometry(bool, vtkActor *, int)), this, SIGNAL(selectGeometry(bool, vtkActor *, int)));
        
    //     connect(this, SIGNAL(keyEvent(int, QKeyEvent *)), style, SLOT(keyEvent(int, QKeyEvent *)));
    //     connect(style, SIGNAL(highLight(QMultiHash<int, int> *)), this, SIGNAL(highLighSet(QMultiHash<int, int> *)));
    //     //			connect(style, SIGNAL(higtLightActorDisplayPoint(bool)), this, SIGNAL(highLightActorDispalyPoint(bool)));
    //     connect(style, SIGNAL(clearAllHighLight()), this, SIGNAL(clearAllHighLight()));
        
    //     connect(_mainWindow, SIGNAL(selectModelChangedSig(int)), this, SLOT(setSelectType(int)));
    //     //
    //     connect(style, SIGNAL(grabKeyBoard(bool)), this, SLOT(enableKeyBoard(bool)));
    //     connect(style, SIGNAL(mouseWhellMove()), this, SLOT(mouseWheelMove()));
    //     connect(style, SIGNAL(rightDownMenu()), this, SIGNAL(rightDownMenuSig()));
    // }
    
    initAxes();
    updateGraphOption();
}
void FCGraph3DWindow::initAxes()
{
    vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
    mAxesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    mAxesWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    mAxesWidget->SetOrientationMarker(axesActor);
    mAxesWidget->SetInteractor(mInteractor);
    mAxesWidget->SetViewport(0.0, 0.0, 0.2, 0.2);
    mAxesWidget->SetEnabled(1);
    ///禁止交互操作移动位置2
    mAxesWidget->InteractiveOff();
}
void FCGraph3DWindow::initText()
{
    vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
    textActor->SetInput("QianFan");
    textActor->GetTextProperty()->SetColor(0.8, 0.75, 0.75);
    textActor->SetDragable(false);
    mTextWidget = vtkSmartPointer<vtkTextWidget>::New();
    
    vtkSmartPointer<vtkTextRepresentation> textRepresentation = vtkSmartPointer<vtkTextRepresentation>::New();
    textRepresentation->GetPositionCoordinate()->SetValue(.02, 0.9);
    textRepresentation->GetPosition2Coordinate()->SetValue(.3, 0.1);
    mTextWidget->SetRepresentation(textRepresentation);
    
    mTextWidget->SetInteractor(mInteractor);
    mTextWidget->SetTextActor(textActor);
    mTextWidget->SelectableOff();
    mTextWidget->On();
    mTextWidget->SelectableOff();
}
void FCGraph3DWindow::initScalarBar()
{
    vtkSmartPointer<vtkTextProperty> propLable = vtkSmartPointer<vtkTextProperty>::New();
    propLable->SetBold(0);
    propLable->SetItalic(0);
    propLable->SetShadow(0);
    propLable->SetJustification(VTK_TEXT_LEFT);
    propLable->SetColor(0, 0, 0);
    propLable->SetFontSize(14);
    
    mScalarBarWidget = vtkSmartPointer<vtkScalarBarWidget>::New();
    mScalarBarWidget->GetScalarBarActor()->SetVerticalTitleSeparation(1);
    mScalarBarWidget->GetScalarBarActor()->SetBarRatio(0.02);
    mScalarBarWidget->GetBorderRepresentation()->SetPosition(0.90, 0.05);
    mScalarBarWidget->GetBorderRepresentation()->SetPosition2(0.91, 0.45);
    mScalarBarWidget->GetBorderRepresentation()->SetShowBorderToOff();
    mScalarBarWidget->GetScalarBarActor()->SetTitleTextProperty(propLable);
    mScalarBarWidget->GetScalarBarActor()->SetLabelTextProperty(propLable);
    mScalarBarWidget->GetScalarBarActor()->SetUnconstrainedFontSize(true);
    //		_scalarBarWidget->GetScalarBarActor()->SetLookupTable(_interactor);
    mScalarBarWidget->SetInteractor(mInteractor);
    mScalarBarWidget->Off();
}
void FCGraph3DWindow::updateScalarBar(vtkLookupTable *lookuptable, QString title /* = QString("") */)
{
    mScalarBarWidget->GetScalarBarActor()->SetLookupTable(lookuptable);
    mLookupTable = lookuptable;
    mScalarBarWidget->On();
}
void FCGraph3DWindow::enableActor(vtkActor *actor, bool show /* = true */)
{
    if (actor == nullptr)
        return;
    if (show)
    {
        actor->VisibilityOn();
    }
    else
    {
        actor->VisibilityOff();
    }
    mRenderWindow->Render();
}


void FCGraph3DWindow::AppendActor(vtkProp *actor, ActorType type, bool reRender, bool reset)
{
    if (type == ActorType::D3)
    {
        mRender->AddActor(actor);
    }
    else if (type == ActorType::D2)
    {
        mRender->AddActor2D(actor);
    }
    else
        assert(0);
    if (reRender)
    {
        if (reset)
            mRender->ResetCamera();
        mRenderWindow->Render();
    }
}
void FCGraph3DWindow::RemoveActor(vtkProp *actor)
{
    if (nullptr != mRender && nullptr != actor)
    {
        mRender->RemoveActor(actor);
    }
    //		_renderWindow->Render();
}

void FCGraph3DWindow::saveImage(QString filePath, int w, int h, bool showdlg)
{
    Q_UNUSED(showdlg)
    
    //		QString dir = Setting::BusAPI::instance()->getWorkingDir();
    
    vtkSmartPointer<vtkWindowToImageFilter> report_windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
    vtkSmartPointer<vtkImageResize> report_resize = vtkSmartPointer<vtkImageResize>::New();
    vtkSmartPointer<vtkPNGWriter> report_writer = vtkSmartPointer<vtkPNGWriter>::New();
    
    QString png_name = filePath;
    
    report_windowToImageFilter->SetInput(mRenderWindow);
    report_resize->SetInputConnection(report_windowToImageFilter->GetOutputPort());
    report_resize->SetOutputDimensions(w, h, 1);
    report_resize->Update();
    report_writer->SetFileName(png_name.toLocal8Bit().data());
    report_writer->SetInputConnection(report_resize->GetOutputPort());
    report_writer->Write();
}
void FCGraph3DWindow::updateScalarBarLecel(const int n)
{
    mLookupTable->SetNumberOfColors(n);
    mScalarBarWidget->GetScalarBarActor()->SetLookupTable(mLookupTable);
    //		int na = _render->GetActors()->GetNumberOfItems();
    mRenderWindow->Render();
}
int FCGraph3DWindow::getScalarBarLevel()
{
    if (mLookupTable == nullptr)
        return 0;
    int n = mLookupTable->GetNumberOfColors();
    return n;
}
void FCGraph3DWindow::resetCamera()
{
    mRender->ResetCamera();
    mRenderWindow->Render();
    this->mouseWheelMove();
}
void FCGraph3DWindow::setViewValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3)
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(x1, x2, x3);
    camera->SetPosition(y1, y2, y3);
    camera->SetFocalPoint(z1, z2, z3);
    resetCamera();
}
void FCGraph3DWindow::fitView()
{
    resetCamera();
}
void FCGraph3DWindow::setViewXPlus()
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(5000, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
}
void FCGraph3DWindow::setViewXMiuns()
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(-5000, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
}
void FCGraph3DWindow::setViewYPlus()
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(0, 5000, 0);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
}
void FCGraph3DWindow::setViewYMiuns()
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(0, -5000, 0);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
}
void FCGraph3DWindow::setViewZPlus()
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 5000);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
}
void FCGraph3DWindow::setViewZMiuns()
{
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, -1);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
}

void FCGraph3DWindow::keyPressEvent(QKeyEvent *e)
{
    emit keyEvent(0, e);
}
void FCGraph3DWindow::keyReleaseEvent(QKeyEvent *e)
{
    emit keyEvent(1, e);
}

SelectModel FCGraph3DWindow::getSelectModel()
{
    return mSelectModel;
}
void FCGraph3DWindow::setSelectType(int model)
{
    mSelectModel = (SelectModel)model;
}

void FCGraph3DWindow::updateGraphOption()
{
    // Setting::GraphOption *option = Setting::BusAPI::instance()->getGraphOption();
    // QColor topcolor = option->getBackgroundTopColor();
    // QColor bottomcolor = option->getBackgroundBottomColor();
    // _render->SetBackground2(topcolor.redF(), topcolor.greenF(), topcolor.blueF());
    // _render->SetBackground(bottomcolor.redF(), bottomcolor.greenF(), bottomcolor.blueF());
    // _renderWindow->Render();
}
// void FCGraph3DWindow::reTranslate()
// {
//     _ui->retranslateUi(this);
// }

void FCGraph3DWindow::addCaption(double *pos, QString cap)
{
    QByteArray array = cap.toLatin1();
    vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = vtkSmartPointer<vtkCaptionRepresentation>::New();
    captionRepresentation->GetCaptionActor2D()->SetCaption(array.data());
    captionRepresentation->GetCaptionActor2D()->GetTextActor()->GetTextProperty()->SetFontSize(50);
    captionRepresentation->SetAnchorPosition(pos);
    captionRepresentation->GetCaptionActor2D()->GetProperty()->SetColor(1.0, 0, 0);
    
    vtkSmartPointer<vtkCaptionWidget> captionWidget = vtkSmartPointer<vtkCaptionWidget>::New();
    captionWidget->SetInteractor(mInteractor);
    captionWidget->SetRepresentation(captionRepresentation);
    captionWidget->On();
    mCaptionList.append(captionWidget);
}

void FCGraph3DWindow::reRender()
{
    mRenderWindow->Render();
}

vtkRenderer *FCGraph3DWindow::getRenderer()
{
    return mRender;
}

FCPropPickerInteractionStyle *FCGraph3DWindow::getInteractionStyle()
{
    // return mInteractionStyle;
    return nullptr;
}

double FCGraph3DWindow::getWorldHight()
{
    double s[3] = {0.0};
    double e[3] = {0.0};
    vtkSmartPointer<vtkCoordinate> coor = vtkSmartPointer<vtkCoordinate>::New();
    coor->SetCoordinateSystemToNormalizedDisplay();
    coor->SetValue(0, 0, 0);
    double *c = coor->GetComputedWorldValue(mRender);
    for (int i = 0; i < 3; ++i)
        s[i] = c[i];
    coor->SetValue(0, 1, 0);
    c = coor->GetComputedWorldValue(mRender);
    for (int i = 0; i < 3; ++i)
        e[i] = c[i];
    
    double m = 0;
    for (int i = 0; i < 3; ++i)
        m += pow(e[i] - s[i], 2);
    
    return sqrt(m);
}

double FCGraph3DWindow::getWorldWidth()
{
    double s[3] = {0.0};
    double e[3] = {0.0};
    vtkSmartPointer<vtkCoordinate> coor = vtkSmartPointer<vtkCoordinate>::New();
    coor->SetCoordinateSystemToNormalizedDisplay();
    coor->SetValue(0, 0, 0);
    double *c = coor->GetComputedWorldValue(mRender);
    for (int i = 0; i < 3; ++i)
        s[i] = c[i];
    coor->SetValue(1, 0, 0);
    c = coor->GetComputedWorldValue(mRender);
    for (int i = 0; i < 3; ++i)
        e[i] = c[i];
    
    double m = 0;
    for (int i = 0; i < 3; ++i)
        m += pow(e[i] - s[i], 2);
    
    return sqrt(m);
}

void FCGraph3DWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    double w = this->getWorldWidth();
    double h = this->getWorldHight();
    emit showGraphRange(w, h);
}

void FCGraph3DWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    mRenderWindow->Render();
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void FCGraph3DWindow::enterEvent(QEnterEvent *event)
#else
void FCGraph3DWindow::enterEvent(QEvent *event)
#endif
{
    Q_UNUSED(event)
    mRenderWindow->Render();
}

void FCGraph3DWindow::mouseWheelMove()
{
    double w = this->getWorldWidth();
    double h = this->getWorldHight();
    emit showGraphRange(w, h);
}

} // namespace FC
