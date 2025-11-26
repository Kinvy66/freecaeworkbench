/**
 * @file FCPropPickerInteractionStyle.h
 * @brief 拾取交互器
 * @date 2025-11-25
 * @version V0.0.1
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPROPPICKERINTERACTIONSTYLE_H
#define FCPROPPICKERINTERACTIONSTYLE_H

#include <QObject>
#include <QMultiHash>
#include <QList>
#include "FCGraphicsViewGlobal.h"
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkIdFilter.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>

// ---------------- 前向声明 VTK 类型 ----------------
class vtkActor;
class vtkProperty;
class vtkDataSet;
class vtkAreaPicker;
class vtkRenderWindow;
class vtkRenderer;
class vtkCoordinate;

class QKeyEvent;
class QWidget;

// ---------------- 命名空间 ----------------
namespace FC 
{

class FCGRAPHICSVIEW_API FCPropPickerInteractionStyle : public QObject
{
    Q_OBJECT
public:
    explicit FCPropPickerInteractionStyle(QObject* parent = nullptr);
    ~FCPropPickerInteractionStyle();
    
    // 获取VTK交互样式
    vtkInteractorStyleRubberBandPick* GetInteractorStyle() { 
        return mInteractorStyle; 
    }
    
    // 设置渲染窗口和渲染器
    void setRenderWindow(vtkRenderWindow* w);
    void setRender(vtkRenderer* r);
    
    // 设置交互器
    void SetInteractor(vtkRenderWindowInteractor* interactor);
    
signals:
    void selectGeometry(bool pre, vtkActor* actor, int index);
    void highLight(QMultiHash<int, int>*);
    void grabKeyBoard(bool g);
    void mouseReleasePoint(double*);
    void mouseMovePoint(double*);
    void mouseRightUp();
    void mouseMiddleUp();
    void mouseWhellMove();
    void rightDownMenu();
    void clearAllHighLight();
    
public slots:
    void setSelectModel(int m);
    void keyEvent(int type, QKeyEvent* e);
    
protected:
    void clickSelectGeometry(bool preSelect = false);
    void clickSelectMeshNode();
    void clickSelectMeshCell();
    void boxSelectMeshNode();
    void boxSelectMeshCell();
    void getBoxRange(int*);
    void selectMesh(vtkDataSet* dataset, int* range);
    bool isPointInRange(int* p, int* range);
    
private:
    // VTK事件回调类
    class CommandCallback : public vtkCommand
    {
    public:
        static CommandCallback* New(FCPropPickerInteractionStyle* client) {
            CommandCallback* cb = new CommandCallback;
            cb->m_client = client;
            return cb;
        }
        
        virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData) {
            if (m_client) {
                m_client->HandleVTKEvent(caller, eventId, callData);
            }
        }
        
    private:
        FCPropPickerInteractionStyle* m_client;
    };
    
    // VTK事件处理
    void HandleVTKEvent(vtkObject* caller, unsigned long eventId, void* callData);
    void SetupCallbacks();
    
    // 鼠标事件
    void OnLeftButtonDown();
    void OnLeftButtonUp();
    void OnMiddleButtonDown();
    void OnMiddleButtonUp();
    void OnRightButtonDown();
    void OnRightButtonUp();
    void OnMouseMove();
    void OnMouseWheelForward();
    void OnMouseWheelBackward();
    void OnKeyBoardUp();
    void OnKeyBoardDown();
    void displayNodeInfo(vtkDataSet* dataset, int id);
    bool isActorHightLighted(vtkActor* ac);
    
private:
    vtkSmartPointer<vtkInteractorStyleRubberBandPick> mInteractorStyle;
    vtkSmartPointer<CommandCallback> mCallback;
    
    vtkActor* mActor{};
    vtkProperty* mProperty{};
    QWidget* mParent{};
    vtkRenderWindow* mRenderWindow{};
    vtkRenderer* mRenderer{};
    SelectModel mSelectModel{SelectModel::None};
    QMultiHash<int, int> mSelectItems{};
    bool mCtrlPressed{false};
    bool mAltPressed{false};
    bool mMouseMoved{false};
    bool mLeftButtonDown{false};
    int mStartPos[2]{};
    int mEndPos[2]{};
    bool mSelected{false};
    vtkActor* mPreGeoSeltctActor{};
    vtkCoordinate* mCoordinate{};
};

} // namespace FC

#endif // FCPROPPICKERINTERACTIONSTYLE_H
