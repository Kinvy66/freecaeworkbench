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
#include "FCGmshSettingData.h"
#include <QApplication>
#include <string>
#include <QDir>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>
// vtk
#include <vtkDataSetReader.h>
#include <vtkCell.h>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkIdList.h>
// occ
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <TopExp.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
// sub module
#include "FCGmshScriptWriter.h"
#include "FCMeshKernal.h"
#include "FCMeshData.h"
#include "FCMeshModule.h"
#include "FCParameterString.h"
#include "FCParameterInt.h"
#include "FCParameterDouble.h"

// #include "MainWindow/MainWindow.h"
// #include "MainWindow/SubWindowManager.h"
// #include "MainWidgets/preWindow.h"
// #include "ModuleBase/processBar.h"
//#include "IO/TemplateReplacer.h"
// #include "MeshReader.h"
// #include "Geometry/GeoCommon.h"
// #include "GmshSettingData.h"
// #include "GeometryCommand/GeoCommandCommon.h"
// #include "FluidMeshPreProcess.h"

namespace FC 
{

FCGmshThread::FCGmshThread(int dim)
{
    
}

FCGmshThread::~FCGmshThread()
{
    
}

void FCGmshThread::appendSolid(int id, int index)
{
    _solidHash.insert(id, index);
}

void FCGmshThread::appendSurface(int geo, int face)
{
    _surfaceHash.insert(geo, face);
}

void FCGmshThread::setElementType(QString t)
{
    _elementType = t;
    int type = 0;
    if (t.toLower() == "quad")
        type = 1;
    else if (t.toLower() == "hex")
        type = 2;
    
    // 		DataProperty::ParameterInt* pi = new DataProperty::ParameterInt();
    // 		pi->setDescribe("ElementType");
    // 		pi->setValue(type);
    // 		this->appendParameter(pi);
}

void FCGmshThread::setElementOrder(int order)
{
    _elementOrder = order;
    
    // 		DataProperty::ParameterInt* pi = new DataProperty::ParameterInt();
    // 		pi->setDescribe("ElementOrder");
    // 		pi->setValue(order);
    // 		this->appendParameter(pi);
}

void FCGmshThread::setMethod(int m)
{
    _method = m;
    
    // 		DataProperty::ParameterInt* pi = new DataProperty::ParameterInt();
    // 		pi->setDescribe("Method");
    // 		pi->setValue(m);
    // 		this->appendParameter(pi);
}

void FCGmshThread::setSizeFactor(double f)
{
    _sizeFactor = f;
    FCParameterDouble *pd = new FCParameterDouble();
    pd->setDescribe("SizeFactor");
    pd->setValue(f);
    this->appendParameter(pd);
}

void FCGmshThread::setMinSize(double min)
{
    _minSize = min;
    // 		DataProperty::ParameterDouble* pd = new DataProperty::ParameterDouble();
    // 		pd->setDescribe("SizeMin");
    // 		pd->setValue(min);
    // 		this->appendParameter(pd);
}

void FCGmshThread::setMaxSize(double max)
{
    _maxSize = max;
    // 		DataProperty::ParameterDouble* pd = new DataProperty::ParameterDouble();
    // 		pd->setDescribe("SizeMax");
    // 		pd->setValue(max);
    // 		this->appendParameter(pd);
}

void FCGmshThread::isCleanGeo(bool c)
{
    _geoclean = c;
    // 		int gc = 0;
    // 		if (_geoclean)  gc = 1;
    
    // 		DataProperty::ParameterInt* pi = new DataProperty::ParameterInt();
    // 		pi->setDescribe("GeoClean");
    // 		pi->setValue(gc);
    // 		this->appendParameter(pi);
}

void FCGmshThread::setSmoothIteration(int it)
{
    _smoothIteration = it;
    // 		DataProperty::ParameterInt* sm = new DataProperty::ParameterInt();
    // 		sm->setDescribe("Smooth");
    // 		sm->setValue(it);
    // 		this->appendParameter(sm);
}

void FCGmshThread::run()
{
    this->mergeGeometry();
    this->initGmshEnvoirment();
    this->generate();
    // 		this->readMesh();
}

void FCGmshThread::mergeGeometry()
{
    QString exelPath = QCoreApplication::applicationDirPath();
    const QString tempDir = exelPath + "/../temp/";
    QDir dir(tempDir);
    if (!dir.exists())
        dir.mkpath(tempDir);
    
    const QString meshfilename = exelPath + "/../temp/mesh.vtk";
    if (QFile::exists(meshfilename))
        QFile::remove(meshfilename);
    
    const QString geofilename = exelPath + "/../temp/geometry.brep";
    if (QFile::exists(geofilename))
        QFile::remove(geofilename);
    
    const QString gmshfilename = exelPath + "/../temp/gmsh.Geo";
    if (QFile::exists(gmshfilename))
        QFile::remove(gmshfilename);
    
    const QString tempPath = tempDir + QString("geometry.brep");
    
    if (_fluidMesh) {
        // _fluidMeshProcess->mergeFluidField(_compounnd, _solidHash);        
    }
    else if (_selectall){
        mergeAllGeo(); 
    }
    else if (_selectvisible) {
        mergeVisibleGeo();
        
    }
    else {
        mergeSelectGeo();
    }
    QByteArray arr = tempPath.toLatin1();
    BRepTools::Write(*_compounnd, arr.data());
}

void FCGmshThread::readMesh()
{
    FCMeshData *data = FCMeshData::getInstance();
    QString exelPath = QCoreApplication::applicationDirPath();
    const QString fileName = exelPath + "/../temp/mesh.vtk";
    
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QByteArray ba = codec->fromUnicode(fileName);
    vtkSmartPointer<vtkDataSetReader> vtkReader = vtkSmartPointer<vtkDataSetReader>::New();
    vtkReader->SetFileName(ba);
    vtkReader->Update();
    vtkDataSet *dataset = vtkReader->GetOutput();
    if (dataset == nullptr)
        return;
    
    if (!_isSaveToKernal)
        emit writeToSolveFileSig(dataset);
    else
    {
        // 			vtkDataSet* vtkset = nullptr;
        // 			if (_cellTypeList.size() > 0)
        // 				vtkset = deleteSpecifiedCells(dataset);
        
        auto k = new FCMeshKernal();
        k->setName(QString("Mesh_%1").arg(k->getID()));
        
        // 			if (vtkset != nullptr)
        // 				k->setMeshData(vtkset);
        // 			else
        k->setMeshData(dataset);
        
        data->appendMeshBody(k);
        
        if (!_fluidMesh)
            setGmshSettingData(k);
        
        // todo
        // emit _gmshModule->updateMeshTree();
        // emit _gmshModule->updateSetTree();
        // emit _gmshModule->updateActions();
        emit updateMeshActor();
    }
}

void FCGmshThread::initGmshEnvoirment()
{
    QString exelPath = QCoreApplication::applicationDirPath();
    const QString tempDir = exelPath + "/../temp/";
    QFile::remove(tempDir + "gmsh.Geo");
    
 
    _scriptWriter->setCompound(_compounnd);
    setGmshScriptData();
    
    if (_fluidMesh)
    {
        // todo
        // QList<int> curve = _fluidMeshProcess->getInerMember(1);
        // QList<int> surface = _fluidMeshProcess->getInerMember(2);
        // _scriptWriter->writeFluidMeshScript(tempDir, _solidHash, curve, surface);
    }
    else
        _scriptWriter->writeGmshScript(tempDir);
}

void FCGmshThread::generate()
{

    QString exelPath = QCoreApplication::applicationDirPath();
    const QString tempDir = exelPath + "/../temp/";
    QString gmshexe = exelPath + "/gmsh";
    
    bool ok = false;
#ifdef Q_OS_WIN
    ok = QFile::exists(gmshexe + ".exe");
#endif
#ifdef Q_OS_LINUX
    ok = QFile::exists(gmshexe);
#endif
    if (!ok)
    {
        // QMessageBox::warning(_mainwindow, QString(tr("Warning")), QString(tr("Gmsh is not exist !")));
        return;
    }
    
    // 		QString oldDir = QDir::currentPath();
    // 		QDir::setCurrent(gmshDir);
    
    QString startProcess = QString("%1 %2 -format vtk -bin -o %3 -%4").arg(gmshexe).arg(tempDir + "gmsh.Geo").arg(tempDir + "mesh.vtk").arg(_dim);
    
    if (gmshexe.contains(" "))
        startProcess = QString("\"%1\"").arg(startProcess);
    qDebug() << startProcess;
    
    _process.start(startProcess);
}

void FCGmshThread::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode)
    switch (exitStatus)
    {
    case QProcess::NormalExit:
        emit sendMessage("************************************");
        emit sendMessage("********* Gmsh finished ************");
        emit sendMessage("************************************");
        
        break;
    case QProcess::CrashExit:
        emit sendMessage("************************************");
        emit sendMessage("********* Gmsh Crashed ************");
        emit sendMessage("************************************");
        break;
    default:
        emit sendMessage("***********************************");
        emit sendMessage("********* Gmsh Stopped ************");
        emit sendMessage("***********************************");
        break;
    }
    
    readMesh();

    emit threadFinished(this);
    // Py::PythonAgent::getInstance()->unLock();
}

void FCGmshThread::readProcessOutput()
{
    QString outputBuffer = QString::fromLocal8Bit(_process.readAll());
    
    emit sendMessage(outputBuffer);
}

void FCGmshThread::stop()
{
    _process.kill();
}

void FCGmshThread::setPara(GMshPara *para)
{
    this->setSolid(para->_solidHash);
    this->setSurface(para->_surfaceHash);
    
    if (_dim == 2)
        this->setSmoothIteration(para->_smoothIteration);
    this->setElementType(para->_elementType);
    this->setElementOrder(para->_elementOrder);
    this->setMethod(para->_method);
    this->setMinSize(para->_minSize);
    this->setMaxSize(para->_maxSize);
    this->setSizeFactor(para->_sizeFactor);
    this->isCleanGeo(para->_geoclean);
    this->setGridCoplanar(para->_isGridCoplanar);
    this->setSizeAtPoint(para->_sizeAtPoints);
    this->setSizeFields(para->_sizeFields);
    this->setSelectedAll(para->_selectall);
    this->setSelectedVisible(para->_selectvisible);
    this->setMeshID(para->_meshID);
    this->setFluidMesh(para->_fluidMesh);

    
    // _fluidMeshProcess->setFluidField(para->_fluidField);
    
}

void FCGmshThread::setSolid(QMultiHash<int, int> s)
{
    _solidHash = s;
}

void FCGmshThread::setSurface(QMultiHash<int, int> s)
{
    _surfaceHash = s;
}


void FCGmshThread::setGridCoplanar(bool gc)
{
    _isGridCoplanar = gc;
}

void FCGmshThread::setSizeAtPoint(QString ps)
{
    _sizeAtPoints = ps;
}

void FCGmshThread::setSizeFields(QString fs)
{
    _sizeFields = fs;
}

void FCGmshThread::setMeshID(int id)
{
    _meshID = id;
}

void FCGmshThread::setSelectedAll(bool al)
{
    _selectall = al;
}

void FCGmshThread::setSelectedVisible(bool sv)
{
    _selectvisible = sv;
}

void FCGmshThread::setFluidMesh(bool fm)
{
    _fluidMesh = fm;
}

void FCGmshThread::setCellTypeList(QString cells)
{
    QStringList celllist = cells.split(",");
    for (QString cell : celllist)
    {
        bool ok = false;
        int type = cell.toInt(&ok);
        if (!ok)
            continue;
        _cellTypeList.append(type);
    }
}

void FCGmshThread::mergeAllGeo()
{
    BRep_Builder aBuilder;
    aBuilder.MakeCompound(*_compounnd);
    
    FCGeometryData *data = FCGeometryData::getInstance();
    const int nset = data->getGeometrySetCount();
    for (int i = 0; i < nset; ++i)
    {
        auto gset = data->getGeometrySetAt(i);
        TopoDS_Shape *shape = gset->getShape();
        if (shape == nullptr)
            continue;
        aBuilder.Add(*_compounnd, *shape);
    }
}

void FCGmshThread::mergeVisibleGeo()
{
    BRep_Builder aBuilder;
    aBuilder.MakeCompound(*_compounnd);
    
    FCGeometryData *data = FCGeometryData::getInstance();
    const int nset = data->getGeometrySetCount();
    for (int i = 0; i < nset; ++i)
    {
        auto gset = data->getGeometrySetAt(i);
        if (!gset->isVisible())
            continue;
        TopoDS_Shape *shape = gset->getShape();
        if (shape == nullptr)
            continue;
        aBuilder.Add(*_compounnd, *shape);
    }
}

void FCGmshThread::mergeSelectGeo()
{
    BRep_Builder aBuilder;
    aBuilder.MakeCompound(*_compounnd);
    
    FCGeometryData *data = FCGeometryData::getInstance();
    QList<int> setList = _surfaceHash.uniqueKeys();
    for (int setid : setList)
    {
        FCGeometrySet *set = data->getGeometrySetByID(setid);
        if (set == nullptr)
            continue;
        TopoDS_Shape *shape = set->getShape();
        if (shape == nullptr)
            continue;
        
        QList<int> indexList = _surfaceHash.values(setid);
        for (int faceindex : indexList)
        {
            TopExp_Explorer faceExp(*shape, TopAbs_FACE);
            for (int index = 0; index < faceindex && faceExp.More(); faceExp.Next(), ++index)
                ;
            
            const TopoDS_Shape &faceShape = faceExp.Current();
            aBuilder.Add(*_compounnd, faceShape);
        }
    }
    
    setList = _solidHash.uniqueKeys();
    for (int setid : setList)
    {
        FCGeometrySet *set = data->getGeometrySetByID(setid);
        if (set == nullptr)
            continue;
        TopoDS_Shape *shape = set->getShape();
        if (shape == nullptr)
            continue;
        
        QList<int> indexList = _solidHash.values(setid);
        for (int solidIndex : indexList)
        {
            TopExp_Explorer solidexp(*shape, TopAbs_SOLID);
            for (int index = 0; index < solidIndex && solidexp.More(); solidexp.Next(), ++index)
                ;
            
            const TopoDS_Shape &solidshape = solidexp.Current();
            aBuilder.Add(*_compounnd, solidshape);
        }
    }
}


QList<itemInfo> FCGmshThread::generateGeoIds(vtkDataSet *dataset)
{
    QList<itemInfo> infoList{};
    // QMultiHash<int, QList<int>> elementHash{};
    if (_surfaceHash.size() < 1 || dataset == nullptr)
        return infoList;
    
    FCGeometryData *data = FCGeometryData::getInstance();
    QMultiHash<int, int>::iterator it = _surfaceHash.begin();
    for (; it != _surfaceHash.end(); it++)
    {
        if (it.key() < 0 || it.value() < 0)
            continue;
        TopoDS_Compound aRes;
        BRep_Builder aBuilder;
        aBuilder.MakeCompound(aRes);
        FCGeometrySet *set = data->getGeometrySetByID(it.key());
        TopoDS_Shape *body = set->getShape();
        
        TopExp_Explorer exper(*body, TopAbs_FACE);
        for (int index = 0; index < it.value() && exper.More(); exper.Next(), ++index)
            ;
        const TopoDS_Shape &s = exper.Current();
        aBuilder.Add(aRes, s);
        QList<int> inids{};
        if (!aRes.IsNull()) {
            // inids = GeoCommon::getD2ElementsInShape(dataset, &aRes);
        }
        
        infoList.append(itemInfo{it.key(), it.value(), inids});
        // elementHash.insert(it.key(), inids);
    }
    return infoList;
    
}

void FCGmshThread::isSaveDataToKernal(bool save)
{
    _isSaveToKernal = save;
}

void FCGmshThread::setGmshSettingData(FCMeshKernal *k)
{
    FCGmshSettingData *setting = new FCGmshSettingData;
    setting->setID(_dim);
    setting->setSolidHash(_solidHash);
    setting->setSurfaceHash(_surfaceHash);
    setting->setElementOrder(_elementOrder);
    setting->setElementType(_elementType);
    setting->setGeoClean(_geoclean);
    setting->setGridCoplanar(_isGridCoplanar);
    setting->setMaxSize(_maxSize);
    setting->setMinSize(_minSize);
    setting->setSizeFactor(_sizeFactor);
    setting->setSelectAll(_selectall);
    setting->setSelectVisiable(_selectvisible);
    setting->setSmoothIteration(_smoothIteration);
    setting->setMethod(_method);
    setting->setSizeAtPoints(_sizeAtPoints);
    setting->setSizeFields(_sizeFields);
    setting->setMeshID(_meshID);
    setting->setCells(_cellTypeList);
    
    k->setGmshSetting(setting);
}

void FCGmshThread::setGmshScriptData()
{
    _scriptWriter->setSmooth(_smoothIteration);
    _scriptWriter->setElementType(_elementType);
    _scriptWriter->setElementOrder(_elementOrder);
    _scriptWriter->setMethod(_method);
    _scriptWriter->setMinSize(_minSize);
    _scriptWriter->setMaxSize(_maxSize);
    _scriptWriter->setFactor(_sizeFactor);
    _scriptWriter->setGeoClean(_geoclean);
    _scriptWriter->setGridCoplanar(_isGridCoplanar);
    _scriptWriter->setSizePoints(_sizeAtPoints);
    _scriptWriter->setSizeFields(_sizeFields);
}

vtkDataSet *FCGmshThread::deleteSpecifiedCells(vtkDataSet *dataset)
{
    if (dataset == nullptr)
        return dataset;
    // int index = 0;
    vtkUnstructuredGrid *ung = vtkUnstructuredGrid::New();
    vtkPoints *points = vtkPoints::New();
    
    const int nNode = dataset->GetNumberOfPoints();
    for (int i = 0; i < nNode; i++)
    {
        double *coor = dataset->GetPoint(i);
        points->InsertNextPoint(coor);
    }
    ung->SetPoints(points);
    
    const int ncell = dataset->GetNumberOfCells();
    for (int i = 0; i < ncell; i++)
    {
        vtkCell *cell = dataset->GetCell(i);
        if (cell == nullptr)
            continue;
        VTKCellType type = (VTKCellType)cell->GetCellType();
        vtkIdList *idlist = vtkIdList::New();
        if (isSpecifiedCell(type))
        {
            idlist = cell->GetPointIds();
            ung->InsertNextCell(type, idlist);
        }
    }
    
    return ung;
}

bool FCGmshThread::isSpecifiedCell(VTKCellType type)
{
    int flag = -1;
    switch (type)
    {
    case VTKCellType::VTK_VERTEX:
    case VTKCellType::VTK_POLY_VERTEX:
        flag = 0;
        break;
    case VTKCellType::VTK_LINE:
    case VTKCellType::VTK_POLY_LINE:
    case VTKCellType::VTK_QUADRATIC_EDGE:
        flag = 1;
        break;
    case VTKCellType::VTK_TRIANGLE:
    case VTKCellType::VTK_QUAD:
    case VTKCellType::VTK_TRIANGLE_STRIP:
    case VTKCellType::VTK_PIXEL:
    case VTKCellType::VTK_POLYGON:
    case VTKCellType::VTK_QUADRATIC_TRIANGLE:
    case VTKCellType::VTK_QUADRATIC_LINEAR_QUAD:
    case VTKCellType::VTK_QUADRATIC_QUAD:
    case VTKCellType::VTK_BIQUADRATIC_QUAD:
        flag = 2;
        break;
    case VTKCellType::VTK_TETRA:
    case VTKCellType::VTK_HEXAHEDRON:
    case VTKCellType::VTK_VOXEL:
    case VTKCellType::VTK_WEDGE:
    case VTKCellType::VTK_PYRAMID:
    case VTKCellType::VTK_PENTAGONAL_PRISM:
    case VTKCellType::VTK_HEXAGONAL_PRISM:
    case VTKCellType::VTK_QUADRATIC_TETRA:
    case VTKCellType::VTK_QUADRATIC_PYRAMID:
    case VTKCellType::VTK_QUADRATIC_HEXAHEDRON:
    case VTKCellType::VTK_BIQUADRATIC_QUADRATIC_HEXAHEDRON:
    case VTKCellType::VTK_TRIQUADRATIC_HEXAHEDRON:
    case VTKCellType::VTK_QUADRATIC_LINEAR_WEDGE:
    case VTKCellType::VTK_QUADRATIC_WEDGE:
    case VTKCellType::VTK_BIQUADRATIC_QUADRATIC_WEDGE:
        flag = 3;
        break;
    default:
        break;
    }
    
    if (_cellTypeList.contains(flag))
        return true;
    
    return false;
}

} // namespace FC
