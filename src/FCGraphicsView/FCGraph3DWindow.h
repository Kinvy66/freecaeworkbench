/**
 * @file FCGraph3DWindow.h
 * @brief 3D(VTK)渲染窗口
 * @date 2025-11-24
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGRAPH3DWINDOW_H
#define FCGRAPH3DWINDOW_H

#include "FCGraphicsViewGlobal.h"
#include "FCGraphWindowBase.h"
#include <QWidget>
#include <vtkSmartPointer.h>
#include <vtkAutoInit.h>
#include <QString>
#include <QStringList>


VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
//VTK_MODULE_INIT(vtkRenderingGL2PSOpenGL2);
//VTK_MODULE_INIT(vtkIOExportOpenGL2);

class vtkActor;
class vtkDataSetMapper;
class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;
class vtkOrientationMarkerWidget;
class vtkTextWidget;
class vtkProp;
class vtkScalarBarWidget;
class vtkLookupTable;
class vtkDataSet;
class vtkPolyData;
class vtkIdTypeArray;
class vtkCaptionWidget;
class QVTKOpenGLNativeWidget;


namespace FC 
{

enum ActorType
{
    D2,
    D3,
};

class FCPropPickerInteractionStyle;

class FCGRAPHICSVIEW_API  FCGraph3DWindow : public FCGraphWindowBase
{
    Q_OBJECT
public:
    FCGraph3DWindow(int id, QWidget* parent = nullptr);
    virtual ~FCGraph3DWindow() = 0;
    //添加渲染对象
    void AppendActor(vtkProp* actor, ActorType type = ActorType::D3, bool reRender = true, bool reset = true);
    //移除渲染对象
    void RemoveActor(vtkProp* actor);
    //启用/禁用渲染读一下
    void enableActor(vtkActor* actor, bool show = true);
    void saveImage(QString fileName, int w, int h, bool showdlg) override;
    void setViewValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3) override;
    void updateScalarBar(vtkLookupTable* lookuptable, QString title = QString(""));
    void updateScalarBarLecel(const int n);
    int getScalarBarLevel();
    //重置视角
    void resetCamera();
    //根据设置重绘
    void updateGraphOption() override;
    // void reTranslate() override;
    void addCaption(double* pos, QString cap);
    //获取交互器
    FCPropPickerInteractionStyle* getInteractionStyle();
    //获取渲染器
    vtkRenderer* getRenderer();
    //获取选择模式
    SelectModel getSelectModel();
    //获取窗体世界坐标系下高度
    double getWorldHight();
    //获取窗体世界坐标系下宽度
    double getWorldWidth();
    
public slots:
    //重绘
    void reRender();
    void toggleProjection();
    
protected slots:
    void setSelectType(int model);
    void enableKeyBoard(bool on);
    void mouseWheelMove();
    
    
private:
    void init();
    void initAxes();
    void initText();
    void initScalarBar();
    
private:
    void fitView() override;
    void setViewXPlus() override;
    void setViewXMiuns() override;
    void setViewYPlus() override;
    void setViewYMiuns() override;
    void setViewZPlus() override;
    void setViewZMiuns() override;
    //void setViewValue(int x1, int x2, int x3, int y1, int y2, int y3, int z1, int z2, int z3) override;
    
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void resizeEvent(QResizeEvent * e) override;
    void leaveEvent(QEvent *event) override;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    // 
signals:
    //type  0-press  1-release
    void keyEvent(int type, QKeyEvent* e);
    //		void selectGeometry(bool ctrlpress);
    void selectGeometry( bool pre, vtkActor* actor, int index);
    void reRenderSig();
    void clearAllHighLight();
    //还原几何颜色
    void rightDownMenuSig();
    //网格
    void highLighSet(QMultiHash<int,int>* items);
    //		void highLightActorDispalyPoint(bool on);
    
protected:
    // Ui::Graph3DWindow* _ui{};
    //		QStringList m_ltFilePath = QStringList();
    QVTKOpenGLNativeWidget* mVTKWidget;
    
    
    vtkSmartPointer<vtkRenderer> mRender{};
    vtkSmartPointer<vtkRenderWindow> mRenderWindow{};
    vtkSmartPointer< vtkRenderWindowInteractor > mInteractor{};
    
    vtkSmartPointer<vtkOrientationMarkerWidget> mAxesWidget{};
    vtkSmartPointer<vtkTextWidget> mTextWidget{};
    vtkSmartPointer<vtkScalarBarWidget> mScalarBarWidget{};
    vtkLookupTable* mLookupTable{};
    QList<vtkSmartPointer<vtkCaptionWidget>> mCaptionList{};
    
    //拾取相关
    FCPropPickerInteractionStyle* mInteractionStyle{};
    SelectModel mSelectModel{ None };
    
};
} // namespace FC



#endif // FCGRAPH3DWINDOW_H
