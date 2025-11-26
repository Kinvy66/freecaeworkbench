/**
 * @file FCGeometryViewProvider.h
 * @brief 
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
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
    FCGeometryViewProvider(FCGraphViewWindow* viewWindow, QObject *parent = nullptr);
    ~FCGeometryViewProvider();
    
    
    void updateGeoActors();
    void updateGraphOption();
    void updateDiaplayStates(FCGeometrySet *s, bool visibility);
    QMultiHash<FCGeometrySet *, int> getGeoSelectItems();
    
public slots:
    void showGeoSet(FCGeometrySet *set, bool render = true);
    void showDatum(FCGeometrySet *datm);
    void removeActors(FCGeometrySet *set);
    void setGeometryDisplay(bool v, bool c, bool f);
    void setGeoSelectMode(int);
    
signals:
    void geoShapeSelected(FCGeometrySet *shape, int index);
    
private slots:
    //高亮显示函数
    void highLightGeometrySet(FCGeometrySet *s, bool on);
    void highLightGeometryFace(FCGeometrySet *s, int id, bool on);	//高亮显示面
    void highLightGeometryEdge(FCGeometrySet *s, int id, bool on);	//高亮显示边
    void highLightGeometryPoint(FCGeometrySet *s, int id, bool on); //高亮显示点
    void highLightGeometrySolid(FCGeometrySet *s, int id, bool on);
    void selectGeometry(bool ctrlpress);
    void selectGeometry(bool pre, vtkActor *ac, int index);
    void clearAllHighLight();
    
private:
    void init();
    
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
    
    QHash<FCGeometrySet *, GeoViewObj> mGeoViewHash{};
};
} // namespace FC


#endif // FCGEOMETRYVIEWPROVIDER_H
