/**
 * @file FCGeometryParaBox.h
 * @brief 立方体参数
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYPARABOX_H
#define FCGEOMETRYPARABOX_H
#include "FCGeometryParaAPI.h"
#include "FCGeometryModelParaBase.h"
#include <QDomDocument>

namespace FC 
{
class FCGEOMETRYPARA_API FCGeometryParaBox : public FCGeometryModelParaBase
{
public:
    /**
     * @brief 构造函数
     */
    FCGeometryParaBox();
    
    /**
     * @brief 析构函数
     */
    ~FCGeometryParaBox() = default;
    
    /**
     * @brief 设置名称
     * @param name 名称
     */
    void setName(QString name);
    
    /**
     * @brief 获取名称
     * @return QString 返回名称
     */
    QString getName();
    
    /**
     * @brief 设置位置
     * @param loc 位置
     */
    void setLocation(double *loc);
    
    /**
     * @brief 获取位置
     * @param loc 返回位置
     */
    void getLocation(double *loc);
    
    /**
     * @brief 设置定形尺寸
     * @param para 定形尺寸
     */
    void setGeoPara(double *para);
    
    /**
     * @brief 获取定形尺寸
     * @param para 返回定形尺寸
     */
    void getGeoPara(double *para);
    
    QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *parent) override;
    virtual void readDataFromProjectFile(QDomElement *e) override;
    
private:
    /**
     * @brief 名称
     */
    QString mName{};
    
    /**
     * @brief 位置
     */
    double mLocation[3];
    /**
     * @brief 定形尺寸
     */
    double mGeoPara[3];
};
} // namespace FC



#endif // FCGEOMETRYPARABOX_H
