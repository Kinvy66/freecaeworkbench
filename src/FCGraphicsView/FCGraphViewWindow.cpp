/**
 * @file FCGraphViewWindow.cpp
 * @brief 绘图（前处理）窗口
 * @date 2025-11-25
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGraphViewWindow.h"
#include "FCGeometrySet.h"
#include "FCGeometryData.h"
#include "FCMeshData.h"
#include "FCMeshKernal.h"
#include "FCGeometryViewProvider.h"
#include "FCMeshViewProvider.h"

namespace FC 
{

FCGraphViewWindow::FCGraphViewWindow(int id, QWidget* parent)
    : FCGraph3DWindow(id, parent)
{
    mGeometryData = FCGeometryData::getInstance();
    mMeshData = FCMeshData::getInstance();
    mGeoProvider = new FCGeometryViewProvider(this);
    mMeshProvider = new FCMeshViewProvider(this);
    connect(this, &FCGraphViewWindow::showGeoSet,
            mGeoProvider, &FCGeometryViewProvider::showGeoSet);

    connect(this, &FCGraphViewWindow::updateGeometryActors,
            mGeoProvider, &FCGeometryViewProvider::updateGeomtryDisplayActor);
    
    connect(this, &FCGraphViewWindow::showMesh,
            mMeshProvider, &FCMeshViewProvider::showMesh);
}

FCGraphViewWindow::~FCGraphViewWindow()
{
    if (mGeoProvider != nullptr)
        delete mGeoProvider;
    emit closed();
}

void FCGraphViewWindow::updateGeometryActor()
{
    mGeoProvider->updateGeoActors();
}
void FCGraphViewWindow::updateGeoDispaly(int index, bool display)
{
    // FCGeometrySet *s = mGeometryData->getGeometrySetAt(index);
    // if (s == nullptr)
    //     return;
    // mGeoProvider->updateDiaplayStates(s, display);
}

void FCGraphViewWindow::removeGeoActor(const IdType id)
{
    FCGeometrySet *set = mGeometryData->getGeometrySetByID(id);
    if (set == nullptr)
        return;
    mGeoProvider->updateGeomtryDisplayActor(id);
    mGeometryData->removeGeometrySet(id);
    delete set;
}

void FCGraphViewWindow::removeMeshActor(const IdType id)
{
    FCMeshKernal* k = mMeshData->getMeshKernalByID(id);
    if (k == nullptr) return;
    mMeshProvider->removeMeshActor(id);
    mMeshData->removeKernalByID(id);
    delete k;
}


// FCGeometrySet *FCGraphViewWindow::getSelectedGeoSet()
// {
//     FCGeometrySet *set = nullptr;// = _geometryData->getGeometrySetAt(_selectedGeoIndex);
//     return set;
// }

/*void FCGraphViewWindow::setGeometryDisplay(QString m)
			{
					if (m.toLower() == "point") _displayGeometryModel =GeometryPoint;
					else if (m.toLower() == "curve") _displayGeometryModel = GeometryCurve;
					else if (m.toLower() == "surface") _displayGeometryModel = GeometrySurface;
					updateDisplayGeometryModel();
			}*/

void FCGraphViewWindow::setDisplay()
{
    // _meshProvider->updateDisplayModel();
    this->reRender();
}

void FCGraphViewWindow::updateMeshActor()
{
    
}

// 	void FCGraphViewWindow::updateMeshActor()
// 	{
//		_meshProvider->updateMeshActor();
//	}

void FCGraphViewWindow::updateMeshDispaly(int index, bool display)
{
    // auto k = MeshData::MeshData::getInstance()->getKernalAt(index);
    // if (nullptr == k)
    //     return;
    // _meshProvider->showKernal(k, display);
}


void FCGraphViewWindow::setSelectModel(int mode)
{
    // _selectModel = (ModuleBase::SelectModel)mode;
    // _meshProvider->setMeshSelectMode(_selectModel);
}

SelectModel FCGraphViewWindow::getSelectModel()
{
    return mSelectModel;
}

void FCGraphViewWindow::highLighSet(QMultiHash<int, int> *items)
{
    // _meshProvider->highLighSelectItem(items);
}

QMultiHash<int, int> *FCGraphViewWindow::getSelectItems()
{
    // return _meshProvider->getSelectItem();
    return  nullptr;
}


void FCGraphViewWindow::updateGraphOption()
{
    // _meshProvider->updateDisplayModel();
    // _meshProvider->updateGraphOption();
    // _geoProvider->updateGraphOption();
    // 		QColor c(0,0,0) /*= Setting::BusAPI::instance()->getGraphOption()->getGeometryColor()*/;
    // 		const int n = _geometryActors.size();
    // 		for (int i = 0; i < n; ++i)
    // 		{
    // 			vtkActor* actor = _geometryActors.at(i);
    // 			actor->GetProperty()->SetDiffuseColor(c.redF(), c.greenF(), c.blueF());
    // 		}
    // ModuleBase::Graph3DWindow::updateGraphOption();
    //		_renderWindow->Render();
}

void FCGraphViewWindow::startSketch(bool start, double *loc, double *dir)
{
    Q_UNUSED(loc)
    // if (start)
    // {
    //     vtkCamera *camera = _render->GetActiveCamera();
    //     gp_Ax3 *ax3 = Geometry::GeometryData::getInstance()->getSketchPlane();
    //     gp_Dir y = ax3->YDirection();
    //     camera->SetViewUp(y.X(), y.Y(), y.Z());
    //     camera->SetPosition(dir[0], dir[1], dir[2]);
    //     camera->SetFocalPoint(0, 0, 0);
    //     _interactionStyle->setSelectModel((int)ModuleBase::DrawSketch);
    //     this->resetCamera();
    // }
    // else
    // {
    //     _interactionStyle->setSelectModel((int)ModuleBase::None);
    //     _sketchProvider->setSketchType(ModuleBase::SketchNone);
    // }
    // _sketchProvider->showSketchPlane(start);
    this->resetCamera();
}

// void FCGraphViewWindow::setSketchType(SketchType t)
// {
    // _sketchProvider->setSketchType(t);
// }

QMultiHash<FCGeometrySet *, int> FCGraphViewWindow::getGeoSelectItems()
{
    // return _geoProvider->getGeoSelectItems();
    QMultiHash<FCGeometrySet *, int>  temp;
    return temp;
}

// 	void FCGraphViewWindow::setGeoSelectItems(QMultiHash<Geometry::GeometrySet*, int> items)
// 	{
// 		_geoProvider->setGeoSelectItems(items);
// 	}

// void FCGraphViewWindow::highLightGeoComponentSlot(Geometry::GeoComponent *aGC)
// {
//     auto selectedItems = aGC->getSelectedItems();
//     QMutableHashIterator<Geometry::GeometrySet *, int> iterator(selectedItems);
//     while (iterator.hasNext())
//     {
//         iterator.next();
//         switch (aGC->getGCType())
//         {
//         case Geometry::GeoComponentType::Node:
//             emit highLightGeometryPoint(iterator.key(), iterator.value(), true);
//             break;
//         case Geometry::GeoComponentType::Line:
//             emit highLightGeometryEdge(iterator.key(), iterator.value(), true);
//             break;
//         case Geometry::GeoComponentType::Surface:
//             emit highLightGeometryFace(iterator.key(), iterator.value(), true);
//             break;
//         case Geometry::GeoComponentType::Body:
//             emit highLightGeometrySolid(iterator.key(), iterator.value(), true);
//             break;
//         }
//     }
// }

} // namespace FC
