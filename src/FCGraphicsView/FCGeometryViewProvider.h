/**
 * @file FCGeometryViewProvider.h
 * @brief 几何模型可视化管理器
 * @date 2025-11-26
 * @version V0.0.1
 * @details 功能：FCGeometryViewProvider 是几何模块的「可视化管理器」，
 * 负责把 OCCT 的几何对象（FCGeometrySet）转换为 VTK Actor 并管理其
 * 显示、隐藏、选中、高亮等图形状态。 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYVIEWPROVIDER_H
#define FCGEOMETRYVIEWPROVIDER_H

#include <QObject>
#include <QPair>
#include <QHash>
#include "FCGraphicsViewGlobal.h"


class vtkActor;
class vtkPolyData;

namespace FC 
{
class FCGeometryData;
class FCGeometrySet;
class FCGeometryDatum;
class FCGeometryViewData;
class FCGraphViewWindow;

class FCGRAPHICSVIEW_API FCGeometryViewProvider : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCGeometryViewProvider(FCGraphViewWindow* viewWindow, QObject *parent = nullptr);
    ~FCGeometryViewProvider();
    
    void updateGeoActors();
    void removeGeoActors();
    void updateGraphOption();
    void updateDiaplayStates(const IdType id, bool visibility);
    QMultiHash<IdType, int> getGeoSelectItems();
    
    // 隐藏/显示所有几何体
    void setAllGeometryVisible(bool visible);
    
public slots:
    void showGeoSet(const IdType id, bool render = true);
    // void showDatum(const IdType id);
    void updateGeomtryDisplayActor(const IdType id);
    void setGeometryDisplay(bool v, bool c, bool f);
    void setGeoSelectMode(int);
    
signals:
    void geoShapeSelected(const IdType shapeID, int index);
    
private slots:
    //高亮显示函数
    void highLightGeometrySet(const IdType setID, bool on);
    void highLightGeometryFace(const IdType setID, int id, bool on);	//高亮显示面
    void highLightGeometryEdge(const IdType setID, int id, bool on);	//高亮显示边
    void highLightGeometryPoint(const IdType setID, int id, bool on); //高亮显示点
    void highLightGeometrySolid(const IdType setID, int id, bool on);
    void selectGeometry(bool ctrlpress);
    void selectGeometry(bool pre, vtkActor *ac, int index);
    void clearAllHighLight();
    
private:
    void init();
    void removeAllActors();  // todo 调试使用
    
private:
    struct GeoViewObj
    {
        QPair<vtkActor *, vtkPolyData *> mFaceObj{nullptr, nullptr};
        QPair<vtkActor *, vtkPolyData *> mEdgeObj{nullptr, nullptr};
        QPair<vtkActor *, vtkPolyData *> mPointObj{nullptr, nullptr};
    };
    
    FCGeometryData *mGeoData{};
    FCGeometryViewData *mViewData{};
    FCGraphViewWindow* mGraphViewWindow;
    
    QHash<IdType, GeoViewObj> mGeoViewHash{};
};
} // namespace FC


#endif // FCGEOMETRYVIEWPROVIDER_H
