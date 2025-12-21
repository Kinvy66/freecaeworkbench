/**
 * @file FCPostProcessingModule.cpp
 * @brief 后处理模块对外接口类实现
 * @date 2025-12-15
 * @version V0.0.1
 * @details FCPostProcessingModule 对外接口实现框架
 */
#include "FCPostProcessingModule.h"
#include "FCPostProcessingData.h"
#include "FCPostProcessingKernal.h"
#include "FCMeshModule.h"
#include "FCMeshKernal.h"

// 前向声明
namespace FC {
class FCMeshModule;
}

#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDataStream>
#include <QDir>
#include "FCUniqueIDGenerater.h"

#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkCell.h>
#include <vtkIdList.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetWriter.h>
#include <random>

namespace FC
{

FCPostProcessingModule::FCPostProcessingModule(QObject* parent)
    : QObject(parent)
{
}

FCPostProcessingModule::~FCPostProcessingModule()
{
}

/****************************
 * 后处理管理接口（CRUD）
 ****************************/
FCPostProcessingModule::IdType FCPostProcessingModule::createPostProcessing(const QString& name, IdType meshID)
{
    FCPostProcessingKernal* kernal = new FCPostProcessingKernal();
    kernal->setName(name);
    kernal->bindMesh(meshID);
    
    IdType id = FCUniqueIDGenerater::id_uint64();
    FCPostProcessingData::getInstance()->appendPostProcessingKernal(id, kernal);
    return id;
}

bool FCPostProcessingModule::deletePostProcessingByID(IdType id)
{
    FCPostProcessingData* data = FCPostProcessingData::getInstance();
    FCPostProcessingKernal* kernal = data->getPostProcessingKernalByID(id);
    if (!kernal) return false;

    data->removeKernalByID(id);
    emit postProcessingDeleted(id);
    delete kernal;
    return true;
}

bool FCPostProcessingModule::deletePostProcessingAt(int index)
{
    FCPostProcessingData* data = FCPostProcessingData::getInstance();
    FCPostProcessingKernal* kernal = data->getKernalAt(index);
    if (!kernal) return false;

    int id = kernal->getID();
    data->removeKernalAt(index);
    emit postProcessingDeleted(id);
    delete kernal;
    return true;
}

int FCPostProcessingModule::getPostProcessingCount() const
{
    return FCPostProcessingData::getInstance()->getKernalCount();
}

FCPostProcessingKernal* FCPostProcessingModule::getPostProcessingByID(IdType id) const
{
    return FCPostProcessingData::getInstance()->getPostProcessingKernalByID(id);
}

FCPostProcessingKernal* FCPostProcessingModule::getPostProcessingAt(int index) const
{
    return FCPostProcessingData::getInstance()->getKernalAt(index);
}

bool FCPostProcessingModule::isPostProcessingExist(IdType id) const
{
    return getPostProcessingByID(id) != nullptr;
}

void FCPostProcessingModule::clearAllPostProcessing()
{
    FCPostProcessingData::getInstance()->clear();
    emit allPostProcessingCleared();
}

/****************************
 * 后处理数据生成接口
 ****************************/
void FCPostProcessingModule::generatePostProcessingData(IdType postID, IdType meshID, FCMeshModule* meshModule)
{
    FCPostProcessingKernal* postKernal = getPostProcessingByID(postID);
    if (!postKernal) {
        qWarning() << "generatePostProcessingData: invalid postID" << postID;
        return;
    }
    
    if (!meshModule) {
        qWarning() << "generatePostProcessingData: FCMeshModule is null";
        emit postProcessingError(postID, "Mesh module not available");
        return;
    }
    
    FCMeshKernal* meshKernal = meshModule->getMeshByID(meshID);
    if (!meshKernal) {
        qWarning() << "generatePostProcessingData: invalid meshID" << meshID;
        emit postProcessingError(postID, "Invalid mesh ID");
        return;
    }
    
    vtkDataSet* meshData = meshKernal->getMeshData();
    if (!meshData) {
        qWarning() << "generatePostProcessingData: mesh data is null";
        emit postProcessingError(postID, "Mesh data is null");
        return;
    }
    
    // 生成随机标量场数据
    qDebug() << "generatePostProcessingData: generating random scalar field for postID" << postID;
    vtkDataSet* postData = generateRandomScalarField(meshData);
    if (postData) {
        qDebug() << "generatePostProcessingData: random scalar field generated successfully, points:" 
                 << postData->GetNumberOfPoints() << "cells:" << postData->GetNumberOfCells();
        
        postKernal->setPostProcessingData(postData);
        
        // 保存为vtk文件用于调试
        // QString fileName = QString("post_%1.vtk").arg(postID);
        // QString filePath = QDir::current().filePath(fileName);
        // vtkDataSetWriter* writer = vtkDataSetWriter::New();
        // writer->SetFileName(filePath.toLocal8Bit().constData());
        // writer->SetInputData(postData);
        // writer->SetFileTypeToBinary();
        // int writeResult = writer->Write();
        // writer->Delete();
        // if (writeResult) {
        //     qDebug() << "generatePostProcessingData: saved post processing data to" << filePath;
        // } else {
        //     qWarning() << "generatePostProcessingData: failed to save post processing data to" << filePath;
        // }
        
        emit postProcessingGenerated(postID, true);
    } else {
        qWarning() << "generatePostProcessingData: failed to generate post processing data";
        emit postProcessingError(postID, "Failed to generate post processing data");
    }
}

/****************************
 * 后处理显示接口（VTK）
 ****************************/
void FCPostProcessingModule::generateDisplayData(IdType postID)
{
    FCPostProcessingKernal* kernal = getPostProcessingByID(postID);
    if (!kernal) return;
    // 显示数据生成在ViewProvider中完成
}

void FCPostProcessingModule::generateDisplayAll()
{
    FCPostProcessingData* data = FCPostProcessingData::getInstance();
    for (int i = 0; i < data->getKernalCount(); ++i)
    {
        // 显示数据生成在ViewProvider中完成
    }
}

void FCPostProcessingModule::setPostProcessingVisible(IdType postID, bool visible)
{
    FCPostProcessingKernal* kernal = getPostProcessingByID(postID);
    if (kernal) kernal->setVisible(visible);
}

bool FCPostProcessingModule::isPostProcessingVisible(IdType postID) const
{
    FCPostProcessingKernal* kernal = getPostProcessingByID(postID);
    return kernal ? kernal->isVisible() : false;
}

void FCPostProcessingModule::setPostProcessingColor(IdType postID, const QColor& color)
{
    FCPostProcessingKernal* kernal = getPostProcessingByID(postID);
    if (kernal) {
        kernal->setColorMap(true, color, color);
    }
}

QColor FCPostProcessingModule::getPostProcessingColor(IdType postID) const
{
    FCPostProcessingKernal* kernal = getPostProcessingByID(postID);
    if (kernal) {
        auto colorMap = kernal->getColorMap();
        if (colorMap.first) {
            return colorMap.second.first;
        }
    }
    return QColor();
}

/****************************
 * 工程文件 / 二进制接口
 ****************************/
void FCPostProcessingModule::writeToProject(QDomDocument* doc, QDomElement* parent)
{
    FCPostProcessingData::getInstance()->writeToProjectFile(doc, parent);
}

void FCPostProcessingModule::readFromProject(QDomNodeList* nodelist)
{
    FCPostProcessingData::getInstance()->readFromProjectFile(nodelist);
}

void FCPostProcessingModule::writeBinary(QDataStream* stream)
{
    FCPostProcessingData::getInstance()->writeBinaryFile(stream);
}

void FCPostProcessingModule::readBinary(QDataStream* stream)
{
    FCPostProcessingData::getInstance()->readBinaryFile(stream);
}

/**
 * @brief 后处理生成完成
 * @param postID
 * @param dataset
 */
void FCPostProcessingModule::onPostProcessingReady(IdType postID, vtkDataSet *dataset)
{
    FCPostProcessingKernal* kernal = getPostProcessingByID(postID);
    if (!kernal)
    {
        qWarning() << "onPostProcessingReady: kernal not found for id" << postID;
        if (dataset) dataset->Delete();
        return;
    }
    
    kernal->setPostProcessingData(dataset);
    qInfo() << "post processing " << postID << " generate OK!";
    
    emit postProcessingGenerated(postID);
}

/**
 * @brief 在网格上生成随机标量场数据
 * @param meshData 网格数据
 * @return 包含标量场的后处理数据
 */
vtkDataSet* FCPostProcessingModule::generateRandomScalarField(vtkDataSet* meshData)
{
    if (!meshData) {
        qWarning() << "generateRandomScalarField: meshData is null";
        return nullptr;
    }
    
    int numPoints = meshData->GetNumberOfPoints();
    int numCells = meshData->GetNumberOfCells();
    
    if (numPoints <= 0 || numCells <= 0) {
        qWarning() << "generateRandomScalarField: invalid mesh data, points:" << numPoints << "cells:" << numCells;
        return nullptr;
    }
    
    // 创建新的数据集，复制网格结构
    vtkSmartPointer<vtkUnstructuredGrid> postData = vtkSmartPointer<vtkUnstructuredGrid>::New();
    
    // 复制点
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->SetNumberOfPoints(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        double pt[3];
        meshData->GetPoint(i, pt);
        points->SetPoint(i, pt);
    }
    postData->SetPoints(points);
    
    // 复制单元
    for (int i = 0; i < numCells; ++i) {
        vtkCell* cell = meshData->GetCell(i);
        if (!cell) {
            qWarning() << "generateRandomScalarField: cell" << i << "is null";
            continue;
        }
        vtkIdList* pointIds = cell->GetPointIds();
        if (!pointIds || pointIds->GetNumberOfIds() == 0) {
            qWarning() << "generateRandomScalarField: cell" << i << "has invalid point ids";
            continue;
        }
        postData->InsertNextCell(cell->GetCellType(), pointIds);
    }
    
    // 生成随机标量场数据（在节点上）
    vtkSmartPointer<vtkDoubleArray> scalarArray = vtkSmartPointer<vtkDoubleArray>::New();
    scalarArray->SetName("ScalarField");
    scalarArray->SetNumberOfComponents(1);
    scalarArray->SetNumberOfTuples(numPoints);
    
    // 使用随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 100.0);
    
    for (int i = 0; i < numPoints; ++i) {
        double value = dis(gen);
        scalarArray->SetTuple1(i, value);
    }
    
    postData->GetPointData()->SetScalars(scalarArray);
    
    // 在单元中心也生成数据
    vtkSmartPointer<vtkDoubleArray> cellScalarArray = vtkSmartPointer<vtkDoubleArray>::New();
    cellScalarArray->SetName("CellScalarField");
    cellScalarArray->SetNumberOfComponents(1);
    cellScalarArray->SetNumberOfTuples(numCells);
    
    for (int i = 0; i < numCells; ++i) {
        double value = dis(gen);
        cellScalarArray->SetTuple1(i, value);
    }
    
    postData->GetCellData()->SetScalars(cellScalarArray);
    
    // 增加引用计数，防止智能指针析构时删除对象
    postData->Register(nullptr);
    return postData;
}

} // namespace FC

