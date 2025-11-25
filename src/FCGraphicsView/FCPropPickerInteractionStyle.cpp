/**
 * @file FCFCPropPickerInteractionStyle.cpp
 * @brief 拾取交互器
 * @date 2025-11-25
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPropPickerInteractionStyle.h"
// vtk
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPropPicker.h>
#include <vtkPointPicker.h>
#include <vtkCellPicker.h>
#include <vtkActor.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkMapper.h>
#include <vtkDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkRenderer.h>
#include <vtkAreaPicker.h>
#include <vtkExtractGeometry.h>
#include <vtkPlanes.h>
#include <vtkCoordinate.h>
#include <vtkPolyData.h>
#include <vtkInteractorStyleRubberBand2D.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActorCollection.h>
#include <vtkCell.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QList>

namespace FC 
{

FCPropPickerInteractionStyle::FCPropPickerInteractionStyle(QObject* parent)
    : QObject(parent)
{
    m_interactorStyle = vtkSmartPointer<vtkInteractorStyleRubberBandPick>::New();
    m_callback = vtkSmartPointer<CommandCallback>::New(this);
    SetupCallbacks();
    
    // 初始化其他成员
    mCoordinate = vtkCoordinate::New();
}

FCPropPickerInteractionStyle::~FCPropPickerInteractionStyle()
{
    if (mCoordinate) {
        mCoordinate->Delete();
    }
}

void FCPropPickerInteractionStyle::setRenderWindow(vtkRenderWindow* w)
{
    mRenderWindow = w;
}

void FCPropPickerInteractionStyle::setRender(vtkRenderer* r)
{
    mRenderer = r;
    if (mCoordinate && mRenderer) {
        mCoordinate->SetCoordinateSystemToWorld();
    }
}

void FCPropPickerInteractionStyle::SetInteractor(vtkRenderWindowInteractor* interactor)
{
    if (interactor) {
        m_interactorStyle->SetInteractor(interactor);
        interactor->SetInteractorStyle(m_interactorStyle);
    }
}

void FCPropPickerInteractionStyle::SetupCallbacks()
{
    if (m_interactorStyle) {
        // 监听所有需要的VTK事件
        m_interactorStyle->AddObserver(vtkCommand::LeftButtonPressEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::MiddleButtonPressEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::MiddleButtonReleaseEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::RightButtonPressEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::RightButtonReleaseEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::MouseMoveEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::MouseWheelForwardEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::MouseWheelBackwardEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::KeyPressEvent, m_callback);
        m_interactorStyle->AddObserver(vtkCommand::KeyReleaseEvent, m_callback);
    }
}

void FCPropPickerInteractionStyle::HandleVTKEvent(vtkObject* caller, unsigned long eventId, void* callData)
{
    switch (eventId) {
    case vtkCommand::LeftButtonPressEvent:
        OnLeftButtonDown();
        break;
    case vtkCommand::LeftButtonReleaseEvent:
        OnLeftButtonUp();
        break;
    case vtkCommand::MiddleButtonPressEvent:
        OnMiddleButtonDown();
        break;
    case vtkCommand::MiddleButtonReleaseEvent:
        OnMiddleButtonUp();
        break;
    case vtkCommand::RightButtonPressEvent:
        OnRightButtonDown();
        break;
    case vtkCommand::RightButtonReleaseEvent:
        OnRightButtonUp();
        break;
    case vtkCommand::MouseMoveEvent:
        OnMouseMove();
        break;
    case vtkCommand::MouseWheelForwardEvent:
        OnMouseWheelForward();
        break;
    case vtkCommand::MouseWheelBackwardEvent:
        OnMouseWheelBackward();
        break;
    case vtkCommand::KeyPressEvent:
        OnKeyBoardDown();
        break;
    case vtkCommand::KeyReleaseEvent:
        OnKeyBoardUp();
        break;
    default:
        break;
    }
}

/**
 * @brief 设置当前拾取模型选择模式
 * @param m
 */
void FCPropPickerInteractionStyle::setSelectModel(int m)
{
    mSelectModel = (SelectModel)m;
    if (m_interactorStyle) {
        // m_interactorStyle->SetCurrentMode(0);
    }
    if (mActor != nullptr && mProperty != nullptr)
        mActor->GetProperty()->DeepCopy(mProperty);
    mActor = nullptr;
    mPreGeoSeltctActor = nullptr;
    mSelectItems.clear();
    
    emit grabKeyBoard(false);
}

/**
 * @brief 按键触发
 * @param type
 * @param e
 */
void FCPropPickerInteractionStyle::keyEvent(int type, QKeyEvent* e)
{
    if (type == 0) // press
    {
        if (e->key() == Qt::Key_Control)
        {
            mCtrlPressed = true;
        }
        else if (e->key() == Qt::Key_Up)
            OnKeyBoardUp();
        else if (e->key() == Qt::Key_Down)
            OnKeyBoardDown();
        else if (e->key() == Qt::Key_Alt)
            mAltPressed = true;
    }
    else if (type == 1) // release
    {
        if (e->key() == Qt::Key_Control)
        {
            mCtrlPressed = false;
        }
        else if (e->key() == Qt::Key_Alt)
            mAltPressed = false;
    }
}

/**
 * @brief 鼠标左键按下触发事件
 */
void FCPropPickerInteractionStyle::OnLeftButtonDown()
{
    mLeftButtonDown = true;
    mMouseMoved = false;
    
    vtkRenderWindowInteractor* interactor = m_interactorStyle->GetInteractor();
    if (interactor) {
        interactor->GetEventPosition(mStartPos);
        qDebug() << "start  " << mStartPos[0] << "   " << mStartPos[1];
    }
    
    mSelected = false;
    
    // 调用原有的左键按下逻辑
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnLeftButtonDown();
}

/**
 * @brief 鼠标左键抬起触发事件
 */
void FCPropPickerInteractionStyle::OnLeftButtonUp()
{
    vtkRenderWindowInteractor* interactor = m_interactorStyle->GetInteractor();
    
    if (mSelectModel == None && !mMouseMoved)
        emit this->clearAllHighLight();
    
    if ((mSelectModel != BoxMeshCell) && (mSelectModel != BoxMeshNode) && (mSelectModel != DrawSketch))
    {
        m_interactorStyle->vtkInteractorStyleRubberBandPick::OnLeftButtonUp();
        return;
    }
    
    // if (m_interactorStyle->GetCurrentMode() == 0)
    // {
    //     m_interactorStyle->vtkInteractorStyleRubberBandPick::OnLeftButtonUp();
    //     return;
    // }
    
    mSelectItems.clear();
    if (interactor) {
        int* endPos = interactor->GetEventPosition();
        mEndPos[0] = endPos[0];
        mEndPos[1] = endPos[1];
    }
    
    if (mSelectModel != DrawSketch && interactor)
    {
        vtkAreaPicker* areaPicker = dynamic_cast<vtkAreaPicker*>(interactor->GetPicker());
        if (areaPicker) {
            vtkActor* ac = areaPicker->GetActor();
            if (ac == nullptr) {
                m_interactorStyle->vtkInteractorStyleRubberBandPick::OnLeftButtonUp();
                return;
            }
        }
    }
    
    mMouseMoved = false;
    mLeftButtonDown = false;
    
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnLeftButtonUp();
}

/**
 * @brief 鼠标移动
 */
void FCPropPickerInteractionStyle::OnMouseMove()
{
    mMouseMoved = true;
    
    vtkRenderWindowInteractor* interactor = m_interactorStyle->GetInteractor();
    if ((mSelectModel == BoxMeshCell) || (mSelectModel == BoxMeshNode) || (mSelectModel == DrawSketch))
    {
        if (interactor) {
            int* endPos = interactor->GetEventPosition();
            mEndPos[0] = endPos[0];
            mEndPos[1] = endPos[1];
            
            if (mSelectModel == DrawSketch && mCoordinate && mRenderer)
            {
                mCoordinate->SetCoordinateSystemToDisplay();
                mCoordinate->SetValue(endPos[0], endPos[1], 0);
                double* d = mCoordinate->GetComputedWorldValue(mRenderer);
                emit mouseMovePoint(d);
            }
        }
    }
    else if (mSelectModel == GeometryCurve || mSelectModel == GeometrySurface || mSelectModel == GeometryPoint || mSelectModel == GeometryBody ||
             mSelectModel == GeometryWinCurve || mSelectModel == GeometryWinSurface || mSelectModel == GeometryWinPoint || mSelectModel == GeometryWinBody)
    {
        clickSelectGeometry(true);
    }
    
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnMouseMove();
}

/**
 * @brief 鼠标中间滚轮按下事件
 */
void FCPropPickerInteractionStyle::OnMiddleButtonDown()
{
    mMouseMoved = false;
    mLeftButtonDown = false;
    
    if ((mSelectModel != BoxMeshCell) && (mSelectModel != BoxMeshNode))
    {
        m_interactorStyle->vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
        return;
    }
    
    // if (m_interactorStyle->GetCurrentMode() == 0)
    //     m_interactorStyle->SetCurrentMode(1);
    // else
    //     m_interactorStyle->SetCurrentMode(0);
        
    m_interactorStyle->vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
}

/**
 * @brief 鼠标中间滚轮抬起事件
 */
void FCPropPickerInteractionStyle::OnMiddleButtonUp()
{
    mMouseMoved = false;
    mLeftButtonDown = false;
    
    if (mSelectModel == DrawSketch)
    {
        emit mouseMiddleUp();
        m_interactorStyle->vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
        return;
    }
    
    if ((mSelectModel != BoxMeshCell) && (mSelectModel != BoxMeshNode))
    {
        m_interactorStyle->vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
        return;
    }
    
    // m_interactorStyle->SetCurrentMode(1);
    m_interactorStyle->vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
}

/**
 * @brief 鼠标中间滚轮向前事件
 */
void FCPropPickerInteractionStyle::OnMouseWheelForward()
{
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnMouseWheelForward();
    emit mouseWhellMove();
}

/**
 * @brief 鼠标中间滚轮向后事件
 */
void FCPropPickerInteractionStyle::OnMouseWheelBackward()
{
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnMouseWheelBackward();
    emit mouseWhellMove();
}

/**
 * @brief 鼠标右键按下触发事件
 */
void FCPropPickerInteractionStyle::OnRightButtonDown()
{
    //判断是否选中几何，bool
    // bool isSelectBody = false;
    // if (_preGeoSeltctActor != nullptr) return;
    // Geometry::GeometryData *data = Geometry::GeometryData::getInstance();
    // if (data->getGeometrySetCount() > 0)
    // {
    //     emit rightDownMenu();
    // }
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnRightButtonDown();
}

/**
 * @brief 鼠标右键抬起触发事件
 */
void FCPropPickerInteractionStyle::OnRightButtonUp()
{
    mMouseMoved = false;
    mLeftButtonDown = false;
    m_interactorStyle->vtkInteractorStyleRubberBandPick::OnRightButtonUp();
    emit mouseRightUp();
}

/**
 * @brief键盘上的向上箭头按键触发事件
 */
void FCPropPickerInteractionStyle::OnKeyBoardUp()
{
    /*switch (_selectModel)
    {
    case ModuleBase::GeometryBody:
    case ModuleBase::GeometryCurve:
    case ModuleBase::GeometrySurface:
    case ModuleBase::GeometryPoint:
    case ModuleBase::GeometryWinPoint:
    case ModuleBase::GeometryWinCurve:
    case ModuleBase::GeometryWinSurface:
    case ModuleBase::GeometryWinBody:
    const int n = _tempActorContainer.size();
    _currentTempIndex--;
    if (_currentTempIndex < 0)
    _currentTempIndex = n - 1;
    if (_currentTempIndex >= 0 && _currentTempIndex < n)
    {
    vtkActor* ac = _tempActorContainer.at(_currentTempIndex);
    QList<double*> pickeds = _actorPickedPoints.values(ac);
    for (auto picked : pickeds)
    emit selectGeometry(ac, picked, _ctrlPressed);
    return;
    }
    }*/
}

/**
 * @brief 键盘上的向下箭头按键事件
 */
void FCPropPickerInteractionStyle::OnKeyBoardDown()
{
    /*switch (_selectModel)
    {
    case ModuleBase::GeometryBody:
    case ModuleBase::GeometryCurve:
    case ModuleBase::GeometrySurface:
    case ModuleBase::GeometryPoint:
    case ModuleBase::GeometryWinPoint:
    case ModuleBase::GeometryWinCurve:
    case ModuleBase::GeometryWinSurface:
    case ModuleBase::GeometryWinBody:
    const int n = _tempActorContainer.size();
    _currentTempIndex++;
    if (_currentTempIndex >= n)
    _currentTempIndex = 0;
    if (_currentTempIndex >= 0 && _currentTempIndex < n)
    {
    vtkActor* ac = _tempActorContainer.at(_currentTempIndex);
    QList<double*> setPickeds = _actorPickedPoints.values(ac);
    for (auto picked:setPickeds)
    emit selectGeometry(ac, picked, _ctrlPressed);
    return;
    }
    }*/
}

/**
 * @brief 几何相关的鼠标选取高亮触发函数
 * @param preSelect
 */
void FCPropPickerInteractionStyle::clickSelectGeometry(bool preSelect)
{
    vtkRenderWindowInteractor* interactor = m_interactorStyle->GetInteractor();
    if (!interactor) return;
    
    int* clickPos = interactor->GetEventPosition();
    int success = -1, index = -1;
    vtkActor* actor = nullptr;
    
    if (mSelectModel == GeometryPoint || mSelectModel == GeometryWinPoint)
    {
        vtkSmartPointer<vtkPointPicker> picker = vtkSmartPointer<vtkPointPicker>::New();
        success = picker->Pick(clickPos[0], clickPos[1], 0, m_interactorStyle->GetDefaultRenderer());
        if (0 != success)
        {
            index = picker->GetPointId();
            actor = picker->GetActor();
        }
    }
    else
    {
        vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
        if (mSelectModel == GeometryCurve || mSelectModel == GeometryWinCurve)
            picker->SetTolerance(0.0025);
        success = picker->Pick(clickPos[0], clickPos[1], 0, m_interactorStyle->GetDefaultRenderer());
        if (0 != success)
        {
            index = picker->GetCellId();
            actor = picker->GetActor();
        }
    }
    emit selectGeometry(preSelect, actor, index);
}

/**
 * @brief 网格模型选取高亮点触发函数
 */
void FCPropPickerInteractionStyle::clickSelectMeshNode()
{
    emit clearAllHighLight();
    
    vtkRenderWindowInteractor* interactor = m_interactorStyle->GetInteractor();
    if (!interactor) return;
    
    int* clickPos = interactor->GetEventPosition();
    vtkSmartPointer<vtkPointPicker> picker = vtkSmartPointer<vtkPointPicker>::New();
    picker->Pick(clickPos[0], clickPos[1], 0, m_interactorStyle->GetDefaultRenderer());
    if (picker->GetPointId() >= 0)
    {
        if (!mCtrlPressed)
            mSelectItems.clear();
        int id = picker->GetPointId();
        vtkDataSet* dataset = picker->GetActor()->GetMapper()->GetInput();
        vtkDataArray* idArray = dataset->GetPointData()->GetArray("IDS");
        double* k_index = idArray->GetTuple2(id);
        mSelectItems.insert(k_index[0], k_index[1]);
        emit highLight(&mSelectItems);
    }
}

/**
 * @brief 网格相关的拾取高亮单元的触发函数
 */
void FCPropPickerInteractionStyle::clickSelectMeshCell()
{
    emit clearAllHighLight();
    
    vtkRenderWindowInteractor* interactor = m_interactorStyle->GetInteractor();
    if (!interactor) return;
    
    int* clickPos = interactor->GetEventPosition();
    vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
    picker->Pick(clickPos[0], clickPos[1], 0, m_interactorStyle->GetDefaultRenderer());
    if (picker->GetCellId() >= 0)
    {
        if (!mCtrlPressed)
            mSelectItems.clear();
        int id = picker->GetCellId();
        vtkDataSet* dataset = picker->GetActor()->GetMapper()->GetInput();
        vtkDataArray* idArray = dataset->GetCellData()->GetArray("IDS");
        double* k_index = idArray->GetTuple2(id);
        mSelectItems.insert(k_index[0], k_index[1]);
        emit highLight(&mSelectItems);
    }
}

/**
 * @brief 网格显示点的相关信息
 * @param dataset
 * @param id
 */
void FCPropPickerInteractionStyle::displayNodeInfo(vtkDataSet* dataset, int id)
{
    // 实现显示节点信息的具体逻辑
}

/**
 * @brief 网格相关的框选点的选取高亮触发函数
 */
void FCPropPickerInteractionStyle::boxSelectMeshNode()
{
    emit clearAllHighLight();
    mSelectItems.clear();
    
    int range[4];
    this->getBoxRange(range);
    
    if (!mRenderer) return;
    
    vtkActorCollection* actors = mRenderer->GetActors();
    actors->InitTraversal();
    const int nac = actors->GetNumberOfItems();
    for (int i = 0; i < nac; ++i)
    {
        vtkActor* actor = actors->GetNextActor();
        if (actor == nullptr || !actor->GetVisibility() || !actor->GetPickable())
            continue;
            
        vtkMapper* mapper = actor->GetMapper();
        if (mapper == nullptr)
            continue;
            
        vtkDataSet* dataset = mapper->GetInputAsDataSet();
        if (dataset == nullptr)
            continue;
            
        vtkDataArray* IDS = dataset->GetPointData()->GetArray("IDS");
        if (IDS == nullptr)
            continue;
        
        this->selectMesh(dataset, range);
    }
    emit highLight(&mSelectItems);
}

void FCPropPickerInteractionStyle::boxSelectMeshCell()
{
    emit clearAllHighLight();
    mSelectItems.clear();
    
    int range[4];
    this->getBoxRange(range);
    
    if (!mRenderer) return;
    
    vtkActorCollection* actors = mRenderer->GetActors();
    actors->InitTraversal();
    const int nac = actors->GetNumberOfItems();
    for (int i = 0; i < nac; ++i)
    {
        vtkActor* actor = actors->GetNextActor();
        if (actor == nullptr || !actor->GetVisibility() || !actor->GetPickable())
            continue;
            
        vtkMapper* mapper = actor->GetMapper();
        if (mapper == nullptr)
            continue;
            
        vtkDataSet* dataset = mapper->GetInputAsDataSet();
        if (dataset == nullptr)
            continue;
            
        vtkDataArray* IDS = dataset->GetCellData()->GetArray("IDS");
        if (IDS == nullptr)
            continue;
        
        this->selectMesh(dataset, range);
    }
    emit highLight(&mSelectItems);
}

/**
 * @brief 网格框选获取当前框选的范围区域值
 * @param range
 */
void FCPropPickerInteractionStyle::getBoxRange(int* range)
{
    // range ---- xmin xmax ymin ymax
    range[0] = mStartPos[0];
    range[1] = mEndPos[0];
    range[2] = mStartPos[1];
    range[3] = mEndPos[1];
    
    int temp;
    if (range[0] > range[1])
    {
        temp = range[0];
        range[0] = range[1];
        range[1] = temp;
    }
    if (range[2] > range[3])
    {
        temp = range[2];
        range[2] = range[3];
        range[3] = temp;
    }
}

/**
 * @brief 根据框选的范围区域值计算出当前实体下的选取到的所有单元或点的集合
 * @param dataSet
 * @param range
 */
void FCPropPickerInteractionStyle::selectMesh(vtkDataSet* dataSet, int* range)
{
    if (!mRenderer) return;
    
    vtkSmartPointer<vtkCoordinate> coordinate = vtkSmartPointer<vtkCoordinate>::New();
    coordinate->SetCoordinateSystemToWorld();
    
    if (mSelectModel == BoxMeshNode)
    {
        vtkDataArray* ids = dataSet->GetPointData()->GetArray("IDS");
        const int npoint = dataSet->GetNumberOfPoints();
        for (int i = 0; i < npoint; ++i)
        {
            double coor[3];
            dataSet->GetPoint(i, coor);
            coordinate->SetValue(coor);
            int* va = coordinate->GetComputedDisplayValue(mRenderer);
            if (isPointInRange(va, range))
            {
                double* k_id = ids->GetTuple2(i);
                mSelectItems.insert(k_id[0], k_id[1]);
            }
        }
    }
    else if (mSelectModel == BoxMeshCell)
    {
        vtkDataArray* ids = dataSet->GetCellData()->GetArray("IDS");
        const int ncell = dataSet->GetNumberOfCells();
        for (int i = 0; i < ncell; ++i)
        {
            vtkCell* cell = dataSet->GetCell(i);
            double pcenter[3] = {0};
            cell->GetParametricCenter(pcenter);
            int subid;
            double coor[3];
            double w[100];
            cell->EvaluateLocation(subid, pcenter, coor, w);
            
            coordinate->SetValue(coor);
            int* va = coordinate->GetComputedDisplayValue(mRenderer);
            if (isPointInRange(va, range))
            {
                double* k_id = ids->GetTuple2(i);
                mSelectItems.insert(k_id[0], k_id[1]);
            }
        }
    }
}

/**
 * @brief 判断当前点是否在框选的范围区域值内
 * @param p
 * @param range
 * @return 
 */
bool FCPropPickerInteractionStyle::isPointInRange(int* p, int* range)
{
    bool isx = p[0] >= range[0] && p[0] <= range[1] ? true : false;
    bool isy = p[1] >= range[2] && p[1] <= range[3] ? true : false;
    
    return isx && isy;
}

/**
 * @brief 根据颜色值的比较来判断当前actor是否已经高亮（未使用）
 * @param ac
 * @return 
 */
bool FCPropPickerInteractionStyle::isActorHightLighted(vtkActor* ac)
{
    if (ac == nullptr)
        return false;
    
    return true;
}

} // namespace FC
