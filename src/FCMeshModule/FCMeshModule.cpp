/**
 * @file FCMeshModule.cpp
 * @brief 网格模块对外接口类实现
 * @date 2025-12-10
 * @version V0.0.1
 * @details FCMeshModule 对外接口实现框架
 */
#include "FCMeshModule.h"
#include "FCMeshData.h"
#include "FCMeshKernal.h"
#include "FCGmshSettingData.h"
#include "FCGmshThreadManager.h"

#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDataStream>
#include "FCUniqueIDGenerater.h"
#include "FCGeometryData.h"

#include "vtkDataSet.h"

namespace FC
{

FCMeshModule::FCMeshModule(QObject* parent)
    : QObject(parent)
{
    mThreadManager = FCGmshThreadManager::getInstance();
    connect(mThreadManager, &FCGmshThreadManager::meshProgress,
            this, &FCMeshModule::meshGenerationProgress);
    connect(mThreadManager, &FCGmshThreadManager::meshReady,
            this, &FCMeshModule::onMeshReady);
    
}

FCMeshModule::~FCMeshModule()
{
    stopAllMeshGeneration();
}

/****************************
 * 网格管理接口（CRUD）
 ****************************/
FCMeshModule::IdType FCMeshModule::createMesh(const QString& name, FCGmshSettingData* para)
{
    FCMeshKernal* kernal = new FCMeshKernal();
    // settingData->setMaxSize();
    kernal->setGmshSetting(para);
    kernal->setName(name);
    
    int n = kernal->bindGeometry(FCGeometryData::getInstance()->getAllGeometrySetID());
    
    qDebug().noquote() << name << " bind " << n << " geometrys";
    
    IdType id = FCUniqueIDGenerater::id_uint64();
    FCMeshData::getInstance()->appendMeshKernal(id, kernal);
    return id;
}

bool FCMeshModule::deleteMeshByID(IdType id)
{
    FCMeshData* data = FCMeshData::getInstance();
    FCMeshKernal* kernal = data->getMeshKernalByID(id);
    if (!kernal) return false;

    data->removeKernalByID(id);
    emit meshDeleted(id);
    delete kernal;
    return true;
}

bool FCMeshModule::deleteMeshAt(int index)
{
    FCMeshData* data = FCMeshData::getInstance();
    FCMeshKernal* kernal = data->getKernalAt(index);
    if (!kernal) return false;

    int id = kernal->getID();
    data->removeKernalAt(index);
    emit meshDeleted(id);
    delete kernal;
    return true;
}

int FCMeshModule::getMeshCount() const
{
    return FCMeshData::getInstance()->getKernalCount();
}

FCMeshKernal* FCMeshModule::getMeshByID(IdType id) const
{
    return FCMeshData::getInstance()->getMeshKernalByID(id);
}

FCMeshKernal* FCMeshModule::getMeshAt(int index) const
{
    return FCMeshData::getInstance()->getKernalAt(index);
}

bool FCMeshModule::isMeshExist(IdType id) const
{
    return getMeshByID(id) != nullptr;
}

void FCMeshModule::clearAllMeshes()
{
    FCMeshData::getInstance()->clear();
    emit allMeshesCleared();
}

/****************************
 * 网格生成接口
 ****************************/
void FCMeshModule::generateMesh(IdType meshID, FCGmshSettingData* setting)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (!kernal || !setting) return;

    // TODO: 同步调用 gmsh API 生成 vtkDataSet
    // kernal->setMeshData(...);

    emit meshGenerated(meshID);
}

void FCMeshModule::generateMesh(IdType meshID)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (!kernal)
    {
        qWarning() << "generateMesh: invalid meshID" << meshID;
        return;
    }
    
    FCDataBase* settingData = kernal->getGmshSetting();
    FCGmshSettingData* setting = nullptr;
    if (settingData)
        setting = static_cast<FCGmshSettingData*>(settingData);
    
    // dispatch to thread manager
    if (!mThreadManager->addTask(meshID, setting))
    {
        qWarning() << "Failed to add mesh generation task for id" << meshID;
    }
}

void FCMeshModule::generateMeshesAsync(const QList<IdType>& meshIDs,
                                       const QList<FCGmshSettingData*>& settings)
{
    if (meshIDs.size() != settings.size()) return;

    for (int i = 0; i < meshIDs.size(); ++i)
    {
        FCMeshKernal* kernal = getMeshByID(meshIDs[i]);
        if (!kernal) continue;

        // _threadManager->addTask(kernal, settings[i]);
        // 线程内部会在完成时发射 meshGenerated 信号
    }
}

void FCMeshModule::stopAllMeshGeneration()
{
    if (mThreadManager)
        mThreadManager->stopAll();
}

bool FCMeshModule::isGenerating(IdType meshID) const
{
    // TODO: 调用 _threadManager 查询线程状态
    return false;
}

/****************************
 * 网格显示接口（VTK）
 ****************************/
void FCMeshModule::generateDisplayData(IdType meshID)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (!kernal) return;

    // kernal->generateDisplayDataSet(); // FCMeshKernal 内部生成 vtk 可视化数据
}

void FCMeshModule::generateDisplayAll()
{
    FCMeshData* data = FCMeshData::getInstance();
    for (int i = 0; i < data->getKernalCount(); ++i)
    {
        // data->getKernalAt(i)->generateDisplayDataSet();
    }
}

void FCMeshModule::setMeshVisible(IdType meshID, bool visible)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (kernal) kernal->setVisible(visible);
}

bool FCMeshModule::isMeshVisible(IdType meshID) const
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    return kernal ? kernal->isVisible() : false;
}

void FCMeshModule::setMeshColor(IdType meshID, const QColor& color)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (kernal) kernal->setSpecificColor(true, color);
}

QColor FCMeshModule::getMeshColor(IdType meshID) const
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    bool enable = false;
    if (kernal) return kernal->getSpecificColor(enable);
    return QColor();
}

/****************************
 * 工程文件 / 二进制接口
 ****************************/
void FCMeshModule::writeToProject(QDomDocument* doc, QDomElement* parent)
{
    FCMeshData::getInstance()->writeToProjectFile(doc, parent);
}

void FCMeshModule::readFromProject(QDomNodeList* nodelist)
{
    FCMeshData::getInstance()->readFromProjectFile(nodelist);
}

void FCMeshModule::writeBinary(QDataStream* stream)
{
    FCMeshData::getInstance()->writeBinaryFile(stream);
}

void FCMeshModule::readBinary(QDataStream* stream)
{
    FCMeshData::getInstance()->readBinaryFile(stream);
}

/****************************
 * GMSH参数接口
 ****************************/
void FCMeshModule::setGmshSetting(IdType meshID, FCGmshSettingData* setting)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (kernal) kernal->setGmshSetting(setting);
}

FCGmshSettingData* FCMeshModule::getGmshSetting(int meshID) const
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    return kernal ? static_cast<FCGmshSettingData*>(kernal->getGmshSetting()) : nullptr;
}

/**
 * @brief 网格生成完成
 * @param meshID
 * @param dataset
 */
void FCMeshModule::onMeshReady(IdType meshID, vtkDataSet *dataset)
{
    // Called when a thread manager notifies a finished mesh
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (!kernal)
    {
        qWarning() << "onMeshReady: kernal not found for id" << meshID;
        if (dataset) dataset->Delete(); // avoid leak if created raw
        return;
    }
    
    kernal->setMeshData(dataset);
    qInfo() << "mesh " << meshID << " generate OK!";
    
    emit meshGenerated(meshID);
}

} // namespace FC
