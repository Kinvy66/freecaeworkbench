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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <assert.h>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QStyle>
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


FCGraph3DWindow::FCGraph3DWindow(int id,QWidget* parent)
: FCGraphWindowBase(id, parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);  // 去掉边距，让工具栏融入窗口
    layout->setSpacing(0);
    
    // ===== 创建工具栏 =====
    mToolBar = new QToolBar(this);
    mToolBar->setMovable(false);
    mToolBar->setFloatable(false);
    mToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    
    // 设置工具栏样式：背景色250, 251, 254，无边框
    mToolBar->setStyleSheet(
        "QToolBar {"
        "background-color: rgb(250, 251, 254);"
        "border: none;"
        "spacing: 3px;"
        "}"
        "QToolBar QToolButton {"
        "border: none;"
        "padding: 3px;"
        "}"
    );
    
    // ===== 创建Actions =====
    // 1. 适应窗口
    QAction *actionFitView = new QAction(this);
    actionFitView->setIcon(QIcon(":/icon/icon/others/autofit.png"));
    actionFitView->setToolTip(tr("适应窗口"));
    connect(actionFitView, &QAction::triggered, this, [this]() {
        this->fitView();
        this->reRender();
    });
    mToolBar->addAction(actionFitView);
    
    // 2. 切换到默认视图
    QAction *actionDefaultView = new QAction(this);
    actionDefaultView->setIcon(QIcon(":/icon/icon/others/default_view.png"));
    actionDefaultView->setToolTip(tr("切换到默认视图"));
    connect(actionDefaultView, &QAction::triggered, this, &FCGraph3DWindow::setDefaultView);
    mToolBar->addAction(actionDefaultView);
    
    // 3. 切换到xy平面
    QAction *actionViewXY = new QAction(this);
    actionViewXY->setIcon(QIcon(":/icon/icon/others/xy_view.png"));
    actionViewXY->setToolTip(tr("切换到xy平面"));
    connect(actionViewXY, &QAction::triggered, this, &FCGraph3DWindow::setViewXY);
    mToolBar->addAction(actionViewXY);
    
    // 4. 切换到yz平面
    QAction *actionViewYZ = new QAction(this);
    actionViewYZ->setIcon(QIcon(":/icon/icon/others/yz_view.png"));
    actionViewYZ->setToolTip(tr("切换到yz平面"));
    connect(actionViewYZ, &QAction::triggered, this, &FCGraph3DWindow::setViewYZ);
    mToolBar->addAction(actionViewYZ);
    
    // 5. 切换到xz平面
    QAction *actionViewXZ = new QAction(this);
    actionViewXZ->setIcon(QIcon(":/icon/icon/others/xz_view.png"));
    actionViewXZ->setToolTip(tr("切换到xz平面"));
    connect(actionViewXZ, &QAction::triggered, this, &FCGraph3DWindow::setViewXZ);
    mToolBar->addAction(actionViewXZ);
    
    // 6. 投影切换
    QAction *actionProjection = new QAction(this);
    actionProjection->setIcon(QIcon(":/icon/icon/others/projection.png"));
    actionProjection->setToolTip(tr("投影切换"));
    connect(actionProjection, &QAction::triggered, this, &FCGraph3DWindow::toggleProjection);
    mToolBar->addAction(actionProjection);
    
    layout->addWidget(mToolBar);
    
    // ===== VTK Widget =====
    mVTKWidget = new QVTKOpenGLNativeWidget(this);
    layout->addWidget(mVTKWidget);
    
    init();
    mRender->GlobalWarningDisplayOff();
    this->setFocusPolicy(Qt::ClickFocus);
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetParallelProjection(false);
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
    mRender->SetBackground2(250/255.0, 251/255.0, 254/255.0);
    mRender->SetBackground(230/255.0, 242/255.0, 255/255.0);
    mInteractor = mRenderWindow->GetInteractor();
    mRenderWindow->AddRenderer(mRender);
    initAxes();
    initScalarBar();
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
    if (!mScalarBarWidget) {
        qWarning() << "FCGraph3DWindow::updateScalarBar: mScalarBarWidget is null";
        return;
    }
    
    if (!lookuptable) {
        qWarning() << "FCGraph3DWindow::updateScalarBar: lookuptable is null";
        return;
    }
    
    mScalarBarWidget->GetScalarBarActor()->SetLookupTable(lookuptable);
    if (!title.isEmpty()) {
        mScalarBarWidget->GetScalarBarActor()->SetTitle(title.toStdString().c_str());
    }
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
    if (!mLookupTable) {
        qWarning() << "FCGraph3DWindow::updateScalarBarLecel: mLookupTable is null";
        return;
    }
    
    if (!mScalarBarWidget) {
        qWarning() << "FCGraph3DWindow::updateScalarBarLecel: mScalarBarWidget is null";
        return;
    }
    
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

void FCGraph3DWindow::showScalarBar(bool show)
{
    if (mScalarBarWidget) {
        if (show) {
            mScalarBarWidget->On();
        } else {
            mScalarBarWidget->Off();
        }
        mRenderWindow->Render();
    }
}

bool FCGraph3DWindow::isScalarBarVisible() const
{
    if (mScalarBarWidget) {
        return mScalarBarWidget->GetEnabled() != 0;
    }
    return false;
}

void FCGraph3DWindow::showAxes(bool show)
{
    if (mAxesWidget) {
        mAxesWidget->SetEnabled(show ? 1 : 0);
        mRenderWindow->Render();
    }
}

bool FCGraph3DWindow::isAxesVisible() const
{
    if (mAxesWidget) {
        return mAxesWidget->GetEnabled() != 0;
    }
    return false;
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

void FCGraph3DWindow::toggleProjection()
{
    vtkCamera* cam = mRender->GetActiveCamera();
    bool isParallel = cam->GetParallelProjection();
    
    cam->SetParallelProjection(!isParallel);   // 切换
    
    if (isParallel)
        qDebug() << "Parallel";
    else
        qDebug() << "Parallel false";
    
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

void FCGraph3DWindow::setViewXY()
{
    // XY平面视图：从Z+方向看，ViewUp为Y+方向
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 5000);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
    reRender();
}

void FCGraph3DWindow::setViewYZ()
{
    // YZ平面视图：从X+方向看，ViewUp为Z+方向
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(5000, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
    reRender();
}

void FCGraph3DWindow::setViewXZ()
{
    // XZ平面视图：从Y+方向看，ViewUp为Z+方向
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(0, 5000, 0);
    camera->SetFocalPoint(0, 0, 0);
    resetCamera();
    reRender();
}

void FCGraph3DWindow::setDefaultView()
{
    // 默认视角：yz视图下绕z轴顺时针旋转45度
    // 首先设置YZ视图
    vtkCamera *camera = mRender->GetActiveCamera();
    camera->SetViewUp(0, 0, 1);
    camera->SetPosition(5000, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    
    // 绕z轴顺时针旋转45度
    // 在YZ视图基础上，绕z轴（0,0,1）顺时针旋转45度
    // 顺时针旋转意味着从Z+方向看，是顺时针，即绕Z轴旋转-45度
    // 旋转后的位置：x' = x*cos(-45°) - y*sin(-45°), y' = x*sin(-45°) + y*cos(-45°)
    // cos(-45°) = cos(45°) = √2/2, sin(-45°) = -sin(45°) = -√2/2
    const double cos45 = 0.7071067811865476;  // √2/2
    const double sin45 = 0.7071067811865476;  // √2/2
    
    // 原始位置是(5000, 0, 0)，绕z轴顺时针旋转45度后
    // x' = 5000*cos45 - 0*sin45 = 5000*cos45
    // y' = 5000*sin45 + 0*cos45 = 5000*sin45
    // z' = 0 (z坐标不变)
    double newX = 5000 * cos45;
    double newY = -5000 * sin45;  // 顺时针旋转，y取负值
    double newZ = 0;
    
    camera->SetPosition(newX, newY, newZ);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetViewUp(0, 0, 1);
    
    resetCamera();
    reRender();
}

} // namespace FC
