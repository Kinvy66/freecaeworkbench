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

namespace FC
{

FCMeshModule::FCMeshModule(QObject* parent)
    : QObject(parent)
{
    _threadManager = FCGmshThreadManager::getInstance();
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
    IdType id = FCUniqueIDGenerater::id_uint64();
    FCMeshData::getInstance()->appendMeshKernal(id, kernal);
    return id;
}

bool FCMeshModule::deleteMeshByID(int id)
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

FCMeshKernal* FCMeshModule::getMeshByID(int id) const
{
    return FCMeshData::getInstance()->getMeshKernalByID(id);
}

FCMeshKernal* FCMeshModule::getMeshAt(int index) const
{
    return FCMeshData::getInstance()->getKernalAt(index);
}

bool FCMeshModule::isMeshExist(int id) const
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
void FCMeshModule::generateMesh(int meshID, FCGmshSettingData* setting)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (!kernal || !setting) return;

    // TODO: 同步调用 gmsh API 生成 vtkDataSet
    // kernal->setMeshData(...);

    emit meshGenerated(meshID);
}

void FCMeshModule::generateMeshesAsync(const QList<int>& meshIDs,
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
    if (_threadManager)
        _threadManager->stopAll();
}

bool FCMeshModule::isGenerating(int meshID) const
{
    // TODO: 调用 _threadManager 查询线程状态
    return false;
}

/****************************
 * 网格显示接口（VTK）
 ****************************/
void FCMeshModule::generateDisplayData(int meshID)
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

void FCMeshModule::setMeshVisible(int meshID, bool visible)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (kernal) kernal->setVisible(visible);
}

bool FCMeshModule::isMeshVisible(int meshID) const
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    return kernal ? kernal->isVisible() : false;
}

void FCMeshModule::setMeshColor(int meshID, const QColor& color)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (kernal) kernal->setSpecificColor(true, color);
}

QColor FCMeshModule::getMeshColor(int meshID) const
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
void FCMeshModule::setGmshSetting(int meshID, FCGmshSettingData* setting)
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    if (kernal) kernal->setGmshSetting(setting);
}

FCGmshSettingData* FCMeshModule::getGmshSetting(int meshID) const
{
    FCMeshKernal* kernal = getMeshByID(meshID);
    return kernal ? static_cast<FCGmshSettingData*>(kernal->getGmshSetting()) : nullptr;
}

} // namespace FC
