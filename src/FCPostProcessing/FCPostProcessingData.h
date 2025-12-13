/**
 * @file FCPostProcessingData.h
 * @brief 全局后处理数据管理类
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGDATA_H
#define FCPOSTPROCESSINGDATA_H
#include "FCDataBase.h"
#include "FCPostProcessingAPI.h"
#include <QList>
#include <QHash>

class QDomDocument;
class QDomElement;
class QDomNodeList;
class QDataStream;
class vtkDataSet;

namespace FC 
{

class FCPostProcessingKernal;

class FCPOSTPROCESSING_API FCPostProcessingData : public FCDataBase
{
public:
    // 获取单例指针
    static FCPostProcessingData* getInstance();
    
    // 添加Kernal
    void appendPostProcessingKernal(FCPostProcessingKernal* keneral);
    
    void appendPostProcessingKernal(IdType id, FCPostProcessingKernal* keneral);
    
    // 获取Kernal数量
    int getKernalCount();
    
    // 获取第index个Kernal
    FCPostProcessingKernal* getKernalAt(const int index);
    
    // 通过ID获取Kernal
    FCPostProcessingKernal* getPostProcessingKernalByID(const IdType id);
    
    QList<IdType> getAllPostProcessingID();
    
    // 通过后处理的数据表示获取Kernal ID
    int getIDByDataSet(vtkDataSet* datset);
    
    // 移除第index个Kernal
    void removeKernalAt(const int index);
    
    // 移除ID为i的Kernal
    void removeKernalByID(const IdType id);
    
    // 判断PostProcessingKernal是否存在
    bool isContainsKernal(const IdType id);
    
    // 清空全部数据
    void clear();
    
    QString getMD5();
    
    /// 写出到工程文件
    QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* parent) override;
    
    // 写出二进制文件
    void writeBinaryFile(QDataStream* dataStream);
    
    /// 从工程文件读入数据
    void readFromProjectFile(QDomNodeList* nodelist);
    
    // 读入二进制文件
    void readBinaryFile(QDataStream* dataFile);
    
private:
    FCPostProcessingData() = default;
    ~FCPostProcessingData();
    
private:
    static FCPostProcessingData* mInstance;
    QList<FCPostProcessingKernal*> mPostProcessingList{};
    QHash<IdType, FCPostProcessingKernal*> mPostProcessingKernals{};

};

} // namespace FC

#endif // FCPOSTPROCESSINGDATA_H

