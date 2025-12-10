/**
 * @file FCMeshModule.cpp
 * @brief 
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshModule.h"
#include <QDebug>
#include <QList>
#include "gmsh.h"
#include "FCGeometryData.h"
#include "FCGeometrySet.h"
#include "TopoDS_Shape.hxx"
#include <TopoDS_Shape.hxx>          
#include <TopoDS_Compound.hxx>       
#include <TopExp_Explorer.hxx>       
#include <BRepTools.hxx>             
#include <BRep_Builder.hxx>        


namespace FC 
{
FCMeshModule *FCMeshModule::_instance = nullptr;


FCMeshModule::FCMeshModule(QObject *parent)
{
    
}


FCMeshModule *FCMeshModule::getInstance()
{
    if (_instance == nullptr)
        _instance = new FCMeshModule();
    return _instance;
}

void FCMeshModule::exec()
{
    try {
        // 初始化 gmsh（如果你在全局已经 init，则可删除）
        gmsh::initialize();
        gmsh::option::setNumber("General.Terminal", 1);
        
        FCGeometryData* geoDatas = FCGeometryData::getInstance();
        int n = geoDatas->getGeometrySetCount();
        qDebug() << "geometry count: " << n;
        
        if (n == 0) {
            qWarning() << "No geometry found.";
            return;
        }
        
        int meshIndex = 0;
        
        // 遍历所有几何实体（TopoDS_Shape）
        for (auto set : geoDatas->getAllGeometrySet()) {
            
            TopoDS_Shape* shape = set->getShape();
            if (!shape || shape->IsNull()) {
                qWarning() << "Null shape detected, skip...";
                continue;
            }
            
            qDebug() << "Processing Shape id=" << meshIndex;
            
            // 1. 使用 importShapesNativePointer 导入 OCC shape
            gmsh::vectorpair dimTags;
            gmsh::model::occ::importShapesNativePointer(
                (void*)shape,     // TopoDS_Shape*
                dimTags,          // 输出导入后的实体维度-tag
                false             // false = 导入所有维度，不仅仅最高维
                );
            
            // 2. OCC 几何建模同步
            gmsh::model::occ::synchronize();
            
            // 3. 生成 3D 网格
            gmsh::model::mesh::generate(2);
            
            // 4. 保存 msh 网格文件
            std::string outFile = "mesh_" + std::to_string(meshIndex) + ".msh";
            gmsh::write(outFile);
            
            qDebug() << "Mesh saved:" << QString::fromStdString(outFile);
            
            meshIndex++;
        }
        
    } catch (std::exception &e) {
        qWarning() << "Gmsh exception:" << e.what();
    }
    
    // gmsh 不要 finalize()，因为你后续还可能继续调用
    // gmsh::finalize();
}

void FCMeshModule::finalize()
{
    try { gmsh::finalize(); }
    catch(...) {}
}



} // namespace FC
