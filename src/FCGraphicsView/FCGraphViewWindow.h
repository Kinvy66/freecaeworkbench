/**
 * @file FCGraphViewWindow.h
 * @brief 绘图（前处理）窗口
 * @date 2025-11-25
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGRAPHVIEWWINDOW_H
#define FCGRAPHVIEWWINDOW_H
#include "FCGraphicsViewGlobal.h"
#include "FCGraph3DWindow.h"

namespace FC 
{

class FCGeometryData;
class FCGeometrySet;
class FCGeometryViewProvider;

class FCGRAPHICSVIEW_API FCGraphViewWindow : public FCGraph3DWindow
{
    Q_OBJECT
public:
    FCGraphViewWindow(int id = -1, QWidget* parent = nullptr);
    ~FCGraphViewWindow();
    
    //获取选择的几何
    QMultiHash<FCGeometrySet *, int> getGeoSelectItems();
    //设置已经选择的几何
    SelectModel getSelectModel();
    QMultiHash<int, int> *getSelectItems();
    
    // MeshViewProvider *getMeshViewProvider();
    
signals:
    //关闭
    void closed();
    //显示几何形状
    void showGeoSet(FCGeometrySet *set, bool render = true);
    //移除几何形状的显示
    void removeGemoActors(FCGeometrySet *set);
    //显示基准
    // void showDatum(GeometryDatum *);
    //移除几何基准显示
    // void removeGeoDatumActors(Geometry::GeometryDatum *);
    //设置选择模式
    void setGeoSelectMode(int);
    //选择的几何元素
    void selectGeoActorShape(vtkActor *ac, int shape, FCGeometrySet *set);
    //新增接口
    void geoShapeSelected(FCGeometrySet *shape, int index);			//被选中接口
    void highLightGeometrySet(FCGeometrySet *s, bool on);			//高亮显示主体
    void highLightGeometryPoint(FCGeometrySet *s, int id, bool on); //高亮显示点
    void highLightGeometryEdge(FCGeometrySet *s, int id, bool on);	//高亮显示边
    void highLightGeometryFace(FCGeometrySet *s, int id, bool on);	//高亮显示面
    void highLightGeometrySolid(FCGeometrySet *s, int id, bool on); //高亮显示实体
    void clearGeometryHighLight();											//清空所有高亮对象
    void removeSetDataSig(const int index);
    //更新网格渲染元素
    void updateMeshActorSig();
    // void highLighKernel(MeshData::MeshKernal *k);
    // void highLighMeshSet(MeshData::MeshSet *set);
    void setMeshSelectMode(int model);
    void highLighDataSet(vtkDataSet *dataset);
    void clearMeshSetHighLight();
    
    // void highLightGeoComponentSig(GeoComponent *aGC);
    
public slots:
    //设置选择模式
    void setSelectModel(int mode) override;
    //		void setGeoSelectItems(QMultiHash<Geometry::GeometrySet*, int> items);
    //设置草图类型
    // void setSketchType(ModuleBase::SketchType t);
    //选择网格类型
    void setDisplay();
    //更新网格渲染
    void updateMeshActor();
    //
    void highLighSet(QMultiHash<int, int> *items);
    //更新几何渲染
    void updateGeometryActor();
    //高亮一个几何组件;
    // void highLightGeoComponentSlot(GeoComponent *);
    
private slots:
    void updateGraphOption() override;
    //几何
    void updateGeoDispaly(int index, bool display);
    void removeGemoActor(const int index);
    //网格
    void updateMeshDispaly(int index, bool display);
    void removeMeshActor(const int index);
    //草图
    void startSketch(bool start, double *loc, double *dir);
    
private:
    QList<vtkActor*> mMeshActors{};
    QList<vtkActor*> mGeometryActors{};
    SelectModel mSelectModel;
    QMultiHash<vtkDataSet *, int> *mSelectItems{};
    //
    // MeshData::MeshData *_meshData{};
    FCGeometryData *mGeometryData{};
    
    // ModelData::ModelDataSingleton *_modelData{};
    int mSelectedGeoIndex{-1};
    
    FCGeometryViewProvider *mGeoProvider{};
    // MeshViewProvider *_meshProvider{};
    // SketchViewProvider *_sketchProvider{};
};
} // namespace FC



#endif // FCGRAPHVIEWWINDOW_H
