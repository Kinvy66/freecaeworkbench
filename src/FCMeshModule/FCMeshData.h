/**
 * @file FCMeshData.h
 * @brief 全局网格数据管理类
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHDATA_H
#define FCMESHDATA_H
#include "FCDataBase.h"
#include "FCMeshModuleAPI.h"
#include <QList>

class QDomDocument;
class QDomElement;
class QDomNodeList;
class QDataStream;
class vtkDataSet;

namespace FC 
{

class FCMeshBody;
class FcMeshGroup;

class FCMESHMODULE_API FCMeshData : public FCDataBase
{
public:
    //获取单例指针
    static FCMeshData* getInstance();
    //添加Kernal
    void appendMeshBody(FCMeshBody* keneral);
    //获取Kernal数量
    int getKernalCount();
    //获取第index个Kernal
    FCMeshBody* getKernalAt(const int index);
    //通过ID获取Kernal
    FCMeshBody* getKernalByID(const int id);
    //通过网格的数据表示获取Kernal ID
    int getIDByDataSet(vtkDataSet* datset);
    //移除第index个Kernal
    void removeKernalAt(const int index);
    //移除ID为i的Kernal
    void removeKernalByID(const int id);
    //添加组件
    // void appendMeshSet(MeshSet* s);
    //获取组件数目
    // int getMeshSetCount();
    //获取第index个组件
    // MeshSet* getMeshSetAt(const int index);
    //通过ID获取网格组件
    // MeshSet* getMeshSetByID(const int id);
    //通过名字获取组件，大小写敏感
    // MeshSet* getMeshSetByName(const QString name);
    //移除第index个组件
    // void removeMeshSetAt(const int index);
    //获取与ID为kid的Kernal相关的全部组件ID
    QList<int> getSetIDFromKernal(int kid);
    /**
		 * @brief  判断MeshKernal是否存在
		 * @param  ker   需要判断的Kernal
		 * @return true  存在
		 * @return false 不存在
		 */
    bool isContainsKernal(FCMeshBody* ker);
    /**
		 * @brief 清空全部数据 
		 */
    void clear();
    QString getMD5();
    ///写出到工程文件
    QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* parent) override;
    //写出二进制文件
    void writeBinaryFile(QDataStream* dataStream);
    ///从工程文件读入数据
    void readFromProjectFile(QDomNodeList* nodelist);
    //读入二进制文件
    void readBinaryFile(QDataStream* dataFile);
    ///产生全部组件的显示模型
    void generateDisplayDataSet();
    
private:
    FCMeshData() = default;
    ~FCMeshData();
    
private:
    static FCMeshData* _instance;
    QList<FCMeshBody*> _meshList{};
    // QList<MeshSet*> _setList{};
};
} // namespace FC



#endif // FCMESHDATA_H
