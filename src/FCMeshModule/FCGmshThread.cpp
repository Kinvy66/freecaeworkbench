/**
 * @file FCGmshThread.cpp
 * @brief gmsh网格划分线程
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGmshThread.h"
#include "FCGeometryData.h"
#include "FCGeometrySet.h"

// mesh
#include "FCMeshKernal.h"
#include "FCMeshData.h"
#include "FCGmshSettingData.h"

// gmsh
#include "gmsh.h"

// OCCT
#include <BRepTools.hxx>
#include <TopoDS_Shape.hxx>

// VTK
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>

// Qt helpers
#include <QDir>
#include <QFile>
#include <QTemporaryFile>
#include <QDebug>

namespace FC {

/**
 * @brief 
 * @param meshID
 * @param setting
 * @param parent
 */
FCGmshThread::FCGmshThread(IdType meshID, FCGmshSettingData* setting, QObject* parent)
    : QThread(parent)
    , mMeshID(meshID)
    , mSetting(setting)
{
}

FCGmshThread::~FCGmshThread()
{
}

/**
 * @brief run
 */
void FCGmshThread::run()
{
    try {
        if (!initGmsh()) {
            emit meshError(mMeshID, "gmsh init failed!");
            return;
        }
        emit progress(mMeshID, 5);
        
        if (!importAllOccShapesToGmsh()) {
            emit meshError(mMeshID, "import OCC shapes failed!");
            finalizeGmsh();
            return;
        }
        emit progress(mMeshID, 25);
        
        applyMeshSettings();
        emit progress(mMeshID, 40);
        
        if (!generateMesh()) {
            emit meshError(mMeshID, "gmsh generate failed!");
            finalizeGmsh();
            return;
        }
        emit progress(mMeshID, 75);
        
        // if (!saveMeshToFile(mMeshID)) {
        //     finalizeGmsh();
        //     return;
        // }
        
        vtkUnstructuredGrid* grid = convertGmshToVtk();
        if (!grid) {
            emit meshError(mMeshID, "convert VTK failed!");
            finalizeGmsh();
            return;
        }
        
        finalizeGmsh();
        
        emit meshFinished(mMeshID, grid);
        emit progress(mMeshID, 100);
    }
    catch (std::exception &e) {
        finalizeGmsh();
        emit meshError(mMeshID, e.what());
    }
    catch (...) {
        finalizeGmsh();
        emit meshError(mMeshID, "unknown exception in mesh thread");
    }
}


/**
 * @brief init gmsh
 * @return 
 */
bool FCGmshThread::initGmsh()
{
    try {
        gmsh::initialize();
        gmsh::option::setNumber("General.Terminal", 0);
        // model name will be created in import step or here
        return true;
    } catch (...) {
        return false;
    }
}

bool FCGmshThread::importAllOccShapesToGmsh()
{
    using namespace gmsh;
    
    // add a model name
    gmsh::model::add("fc_mesh_model");
    
    FCMeshKernal *mk = FCMeshData::getInstance()->getMeshKernalByID(mMeshID);
    if (!mk) {
        qDebug() << "FCGmshThread: mesh kernal not found for id" << mMeshID;
        return false;
    }
    
    QList<IdType> geoIds = mk->getBindedGeometry();
    if (geoIds.isEmpty()) {
        qWarning() << "Not select geometry!";
        return false;
    }
    
    // We'll collect created temporary filenames so we can cleanup reliably
    QStringList tmpFiles;
    
    for (IdType gid : geoIds) {
        FCGeometrySet *gset = FCGeometryData::getInstance()->getGeometrySetByID(gid);
        if (!gset) continue;
        
        TopoDS_Shape *shape = gset->getShape();
        if (!shape) continue;
        
        // Create a unique temp filename under system temp
        QString tmpPath = QDir::temp().filePath(QString("fc_gmsh_%1_%2.brep").arg(mMeshID).arg(gid));
        std::string tmpPathStd = tmpPath.toStdString();
        
        // Use the file-writing overload of BRepTools::Write(...)
        // Prototype used: Standard_Boolean Write(const TopoDS_Shape& theShape, const Standard_CString theFile, ...)
        // Returns Standard_Boolean (converted to bool)
        bool writeOk = false;
        try {
            writeOk = static_cast<bool>(BRepTools::Write(*shape, tmpPathStd.c_str()));
            qDebug() << "Brep write into: " << tmpPathStd;
        } catch (...) {
            writeOk = false;
        }
        
        if (!writeOk) {
            // try an alternative: sometimes BRepTools::Write to std::ofstream is available, but here we require file write
            emit meshError(mMeshID, QString("Failed to write temporary BREP file for geometry %1").arg(gid));
            // cleanup any tmp files created so far
            for (const QString &f : tmpFiles) QFile::remove(f);
            return false;
        }
        
        tmpFiles << tmpPath;
        
        // Import the file into Gmsh
        gmsh::vectorpair dimTags;
        try {
            // signature: importShapes(const std::string & fileName, gmsh::vectorpair & outDimTags, const bool highestDimOnly = true, const std::string & format = "")
            gmsh::model::occ::importShapes(tmpPathStd, dimTags, true, "brep");
        } catch (std::exception &ex) {
            emit meshError(mMeshID, QString("gmsh importShapes failed for %1 : %2").arg(gid).arg(ex.what()));
            for (const QString &f : tmpFiles) QFile::remove(f);
            return false;
        }
    }
    
    // synchronize once after importing all shapes
    try {
        gmsh::model::occ::synchronize();
    } catch (std::exception &ex) {
        emit meshError(mMeshID, QString("gmsh synchronize failed: %1").arg(ex.what()));
        for (const QString &f : tmpFiles) QFile::remove(f);
        return false;
    }
    
    // Clean up temporary files
    for (const QString &f : tmpFiles) {
        // ignore removal errors
        QFile::remove(f);
    }
    
    return true;
}


/**
 * @brief apply mesh settings
 */
void FCGmshThread::applyMeshSettings()
{
    if (!mSetting) return;
    gmsh::option::setNumber("Mesh.MeshSizeMin", mSetting->getMinSize());
    gmsh::option::setNumber("Mesh.MeshSizeMax", mSetting->getMaxSize());
    gmsh::option::setNumber("Mesh.MeshSizeFactor", mSetting->getSizeFactor());
    gmsh::option::setNumber("Mesh.ElementOrder", mSetting->getElementOrder());
    gmsh::option::setNumber("Mesh.Smoothing", mSetting->getSmoothIteration());
    gmsh::option::setNumber("Mesh.Algorithm", mSetting->getMethod());
    
    if (mSetting->getElementType() == "quad" ||
        mSetting->getElementType() == "hex") {
        gmsh::option::setNumber("Mesh.RecombineAll", 1);
    } else {
        gmsh::option::setNumber("Mesh.RecombineAll", 0);
    }
}

/**
 * @brief generate mesh
 * @return 
 */
bool FCGmshThread::generateMesh()
{
    try {
        gmsh::model::mesh::generate(mSetting ? mSetting->getDimension() : 3);
        return true;
    } catch (std::exception &ex) {
        qDebug() << "gmsh generate exception:" << ex.what();
        return false;
    } catch (...) {
        qDebug() << "gmsh generate unknown exception";
        return false;
    }
}

/**
 * @brief convert Gmsh To Vtk
 * @return 
 */
vtkUnstructuredGrid* FCGmshThread::convertGmshToVtk()
{
    // get nodes
    std::vector<std::size_t> nodeTags;
    std::vector<double> coords;
    std::vector<double> params;
    try {
        gmsh::model::mesh::getNodes(nodeTags, coords, params);
    } catch (std::exception &ex) {
        emit meshError(mMeshID, QString("gmsh getNodes failed: %1").arg(ex.what()));
        return nullptr;
    }
    
    if (nodeTags.empty()) {
        emit meshError(mMeshID, "no nodes returned from gmsh");
        return nullptr;
    }
    
    // Create VTK points
    auto grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    auto points = vtkSmartPointer<vtkPoints>::New();
    
    // coords are returned as [x0,y0,z0, x1,y1,z1, ...]
    points->SetNumberOfPoints(nodeTags.size());
    for (size_t i = 0; i < nodeTags.size(); ++i) {
        double x = coords[3 * i + 0];
        double y = coords[3 * i + 1];
        double z = coords[3 * i + 2];
        points->SetPoint(static_cast<vtkIdType>(i), x, y, z);
    }
    grid->SetPoints(points);
    
    // get elements
    std::vector<int> types;
    std::vector<std::vector<std::size_t>> elemTags;
    std::vector<std::vector<std::size_t>> elemNodeTags;
    try {
        gmsh::model::mesh::getElements(types, elemTags, elemNodeTags);
    } catch (std::exception &ex) {
        emit meshError(mMeshID, QString("gmsh getElements failed: %1").arg(ex.what()));
        return nullptr;
    }
    
    // For mapping node tag -> local index, build a map because node tags may not be 1..N
    // But earlier we assumed coords are in nodeTags order and used index (nodeTagIndex-1).
    // Safer mapping: nodeTags[i] -> i
    std::unordered_map<std::size_t, vtkIdType> nodeTagToIndex;
    nodeTagToIndex.reserve(nodeTags.size());
    for (size_t i = 0; i < nodeTags.size(); ++i) nodeTagToIndex[nodeTags[i]] = static_cast<vtkIdType>(i);
    
    // iterate element groups
    for (size_t gi = 0; gi < types.size(); ++gi) {
        int elType = types[gi];
        const auto &nodesFlat = elemNodeTags[gi];
        
        // query element properties
        std::string name;
        int dim = 0, order = 0, numNodesPerElem = 0, numPrimary = 0;
        std::vector<double> nodeOrdering;
        try {
            gmsh::model::mesh::getElementProperties(elType, name, dim, order, numNodesPerElem, nodeOrdering, numPrimary);
        } catch (std::exception &ex) {
            // fallback: try guess common sizes
            qDebug() << "Warning: getElementProperties failed:" << ex.what();
            // try minimal assumptions (tri/tet/quad/hex)
            if (elType == 2) numNodesPerElem = 3;
            else if (elType == 3) numNodesPerElem = 4;
            else if (elType == 4) numNodesPerElem = 4;
            else if (elType == 5) numNodesPerElem = 8;
            else {
                qDebug() << "Unsupported element type:" << elType;
                continue;
            }
        }
        
        if (numNodesPerElem <= 0) {
            qDebug() << "Invalid nodes-per-element for element type" << elType;
            continue;
        }
        
        size_t nElems = nodesFlat.size() / static_cast<size_t>(numNodesPerElem);
        
        for (size_t ei = 0; ei < nElems; ++ei) {
            vtkIdType ids[64]; // enough for typical elements
            for (int k = 0; k < numNodesPerElem; ++k) {
                std::size_t nodeTag = nodesFlat[ei * static_cast<size_t>(numNodesPerElem) + k];
                auto it = nodeTagToIndex.find(nodeTag);
                if (it == nodeTagToIndex.end()) {
                    // should not happen
                    ids[k] = -1;
                } else ids[k] = it->second;
            }
            
            switch (elType) {
            case 2: // triangle
                grid->InsertNextCell(VTK_TRIANGLE, 3, ids);
                break;
            case 3: // quad
                grid->InsertNextCell(VTK_QUAD, 4, ids);
                break;
            case 4: // tetra
                grid->InsertNextCell(VTK_TETRA, 4, ids);
                break;
            case 5: // hexahedron
                grid->InsertNextCell(VTK_HEXAHEDRON, 8, ids);
                break;
            default:
                // unsupported element type for now -> ignore
                break;
            }
        }
    }
    
    // register and return raw pointer (caller will delete)
    grid->Register(nullptr);
    return grid.GetPointer();
}

/**
 * @brief  finalize gmsh
 */
void FCGmshThread::finalizeGmsh()
{
    try {
        gmsh::finalize();
    } catch (...) {}
}

bool FCGmshThread::saveMeshToFile(IdType meshID)
{
    try {
        // 文件名： meshID.msh
        QString fileName = QString("%1.msh").arg(meshID);
        QString savePath = QDir::current().filePath(fileName);
        
        // Gmsh 当前 model → 写入文件
        gmsh::write(savePath.toStdString());
        
        qDebug() << "FCGmshThread: mesh saved to" << savePath;
        return true;
    }
    catch (std::exception &ex) {
        qDebug() << "FCGmshThread: saveMeshToFile error:" << ex.what();
        emit meshError(meshID,
                       QString("gmsh write msh failed: %1").arg(ex.what()));
        return false;
    }
    catch (...) {
        emit meshError(meshID, "gmsh write msh unknown exception");
        return false;
    }
}

} // namespace FC
