/******************************************************************************
 * File     : FCAppActions.cpp
 * Brief    : action管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppActions.h"
#include <QActionGroup>
#include "FCRecentFilesManager.h"

//===================================================
// using DA namespace -- 禁止在头文件using！！
//===================================================
using namespace FC;

//===================================================
// FCAppActions
//===================================================
FCAppActions::FCAppActions(FCUIInterface* u) : FCActionsInterface(u)
{
    buildActions();
    // recentFilesManager = new FCRecentFilesManager(this, 10, QStringLiteral("DA"), QStringLiteral("DAWorkBench"));
}

FCAppActions::~FCAppActions()
{
}

void FCAppActions::buildActions()
{
    // 构建主页actions    
    buildMainAction();
    // 构建几何actions
    buildGeometryAction();
    // 构建网格actions
    buildMeshtAction();
    // 构建研究actions
    buildStudyAction();
    // 构建结果actions
    buildResultAction();
    // 构建工具actions
    buildToolsActions();
    // 建立其他的actions
    buildOtherActions();
}

/**
 * @brief 构建主页actions  
 */
void FCAppActions::buildMainAction()
{
    // Main Category
    // 1. file pannel
    actionNew = createAction("actionNew", ":/icon/icon/new.png");
    actionNew->setText(tr("新建"));
    actionOpen = createAction("actionOpen", ":/icon/icon/open_blue.png");
    actionOpen->setText(tr("打开"));
    actionSave = createAction("actionSave", ":/icon/icon/save.png");
    actionSave->setText(tr("保存"));
    actionSaveAs = createAction("actionSaveAs", ":/icon/icon/save_as.png");
    actionSaveAs->setText(tr("另保存为"));
    
    // 2. model pannel
    actionHomeImportGeometry = createAction("actionImportGeometry", ":/icon/icon/import_geometry.png");
    actionHomeImportGeometry->setText(tr("导入几何"));
    actionHomeImportMesh = createAction("actionImportMesh", ":/icon/icon/import_mesh.png");      
    actionHomeImportMesh->setText(tr("导入网格"));
    // 3. layout pannel
    actionWindowViews = createAction("actionWindowViews", ":/icon/icon/windows_view.png");
    actionWindowViews->setText(tr("窗口"));
    actionResetLayout = createAction("actionResetLayout", ":/icon/icon/reset_layout.png");
    actionResetLayout->setText(tr("重置布局"));    
}

/**
 * @brief 构建几何actions  
 */
void FCAppActions::buildGeometryAction()
{
    // 1. import/export panel
    actionGeometryModelBuildAll = createAction("actionGeometryModelBuildAll", ":/icon/icon/geometry/build_all.png"); ///< 导入几何模型
    actionGeometryModelBuildAll->setText(tr("构建所有"));
    actionImportGeometryModel = createAction("actionImportGeometryModel", ":/icon/icon/geometry/import_geometry.png"); ///< 导入几何模型
    actionImportGeometryModel->setText(tr("导入"));
    actionExportGeometryModel = createAction("actionExportGeometryModel", ":/icon/icon/geometry/export_geometry.png");     ///< 导出几何模型
    actionExportGeometryModel->setText(tr("导出"));
    actionInsertSequenen = createAction("actionInsertSequenen", ":/icon/icon/geometry/insert_seq.png");      ///< 插入序列
    actionInsertSequenen->setText(tr("插入序列"));
    
    // 2. create geometry panel
    actionCreateCUbe = createAction("actionCreateCUbe", ":/icon/icon/geometry/cube.png");              ///< 立方体
    actionCreateCUbe->setText(tr("立方体"));
    actionCreateCone = createAction("actionCreateCone", ":/icon/icon/geometry/cone.png");              ///< 圆锥体
    actionCreateCone->setText(tr("圆锥体"));
    actionCreateCylinder = createAction("actionCreateCylinder", ":/icon/icon/geometry/cylinder.png");          ///< 圆柱体
    actionCreateCylinder->setText(tr("圆柱体"));
    actionCreateSphere = createAction("actionCreateSphere", ":/icon/icon/geometry/sphere.png");            ///< 球体
    actionCreateSphere->setText(tr("球体"));
    actionCreateTorus = createAction("actionCreateTorus", ":/icon/icon/geometry/torus.png");             ///< 圆环
    actionCreateTorus->setText(tr("圆环"));
    actionCreateHelix = createAction("actionCreateHelix", ":/icon/icon/geometry/helix.png");             ///< 螺旋
    actionCreateHelix->setText(tr("螺旋"));
    actionMenuCreateMoreGemetryModel = createAction("actionMenuCreateMoreGemetryModel", ":/icon/icon/geometry/more_model.png");  ///<< 更多Menu
    actionMenuCreateMoreGemetryModel->setText(tr("更多\n模型"));
    actionCreatorBezierCurve = createAction("actionCreatorBezierCurve", ":/icon/icon/geometry/bezier.png");      ///<< 贝塞尔曲线
    actionCreatorBezierCurve->setText(tr("贝塞尔曲线"));
    actionCreatorTetrahedron = createAction("actionCreatorTetrahedron", ":/icon/icon/geometry/tetrahedron.png");      ///<< 四面体
    actionCreatorTetrahedron->setText(tr("四面体"));
    
    // 3. work plane panel
    actionMenuSelectWorkPlane = createAction("actionMenuSelectWorkPlane", ":/icon/icon/geometry/workplane.png");     ///< 选择工作平面
    actionMenuSelectWorkPlane->setText(tr("选择工作平面"));
    actionWorkPlane = createAction("actionWorkPlane", ":/icon/icon/geometry/workplane.png");           ///< 工作平面
    actionWorkPlane->setText(tr("工作平面"));
    actionExtrude = createAction("actionExtrude", ":/icon/icon/geometry/extrude.png");             ///< 拉伸
    actionExtrude->setText(tr("拉伸"));
    actionRevolve = createAction("actionRevolve", ":/icon/icon/geometry/revolve.png");             ///< 回旋
    actionRevolve->setText(tr("回旋"));
    actionSweep = createAction("actionSweep", ":/icon/icon/geometry/sweep.png");               ///< 扫掠
    actionSweep->setText(tr("扫掠"));
    actionLoft = createAction("actionLoft", ":/icon/icon/geometry/loft.png");                ///< 放样
    actionLoft->setText(tr("放样"));
    
    // 4. geometry operator panel
    actionMenuGeometryBooleanOpt = createAction("actionMenuGeometryBooleanOpt", ":/icon/icon/geometry/boolean_opt.png");          ///< 布尔操作Menu
    actionMenuGeometryBooleanOpt->setText(tr("布尔\n操作"));
    actionBooleanUnion = createAction("actionBooleanUnion", ":/icon/icon/geometry/boolean_opt.png");                ///< 并集
    actionBooleanUnion->setText(tr("并集"));
    actionBooleanIntersection = createAction("actionBooleanIntersection", ":/icon/icon/geometry/boolean_opt.png");         ///< 交集
    actionBooleanIntersection->setText(tr("交集"));
    actionBooleanDifference = createAction("actionBooleanDifference", ":/icon/icon/geometry/boolean_opt.png");           ///< 求差
    actionBooleanDifference->setText(tr("求差"));
    actionBooleanCompose = createAction("actionBooleanCompose", ":/icon/icon/geometry/boolean_opt.png");              ///< 组合
    actionBooleanCompose->setText(tr("组合"));
    actionMenuGeometryTransformOpt = createAction("actionMenuGeometryTransformOpt", ":/icon/icon/geometry/transform.png");          ///< 变换操作Menu
    actionMenuGeometryTransformOpt->setText(tr("变换\n操作"));
    actionTransformRigid = createAction("actionTransformRigid", ":/icon/icon/geometry/transform.png");                ///< 刚性变换
    actionTransformRigid->setText(tr("刚性变换"));
    actionTransformCopy = createAction("actionTransformCopy", ":/icon/icon/geometry/transform.png");         ///< 复制
    actionTransformCopy->setText(tr("复制"));
    actionTransformScale = createAction("actionTransformScale", ":/icon/icon/geometry/transform.png");           ///< 比例因子
    actionTransformScale->setText(tr("比例因子"));
    actionTransformMove = createAction("actionTransformMove", ":/icon/icon/geometry/transform.png");              ///< 移动
    actionTransformMove->setText(tr("移动"));
    actionTransformMirror = createAction("actionactionTransformMirrorTransformMirror", ":/icon/icon/geometry/transform.png");              ///< 镜像
    actionTransformMirror->setText(tr("镜像"));
    actionTransformArray = createAction("actionTransformArray", ":/icon/icon/geometry/transform.pngg");              ///< 阵列
    actionTransformArray->setText(tr("阵列"));
    actionChamferOpt = createAction("actionChamferOpt", ":/icon/icon/geometry/chamfer.png");          ///< 倒斜角
    actionChamferOpt->setText(tr("倒斜角"));
    actionFilletOpt = createAction("actionFilletOpt", ":/icon/icon/geometry/fillet.png");          ///< 倒圆角
    actionFilletOpt->setText(tr("倒圆角"));
    actionGeometryDelete = createAction("actionGeometryDelet", ":/icon/icon/geometry/delete.png");       ///< 删除
    actionGeometryDelete->setText(tr("删除"));
    
    // 5. other panel
    actionGeometryMeasure = createAction("actionGeometryMeasure", ":/icon/icon/geometry/measure.png");     ///< 测量
    actionGeometryMeasure->setText(tr("测量"));
    actionGeometryDeletSequence = createAction("actionGeometryDeletSequence", ":/icon/icon/geometry/delete_seq.png");     ///< 删除序列
    actionGeometryDeletSequence->setText(tr("删除序列"));
}

/**
 * @brief 构建网格actions  
 */
void FCAppActions::buildMeshtAction()
{
    // 1.  mesh panel
    actionMeshBuild = createAction("actionMeshBuild", ":/icon/icon/mesh/build_all_mesh.png");       ///< 构建网格
    actionMeshBuild->setText(tr("构建网格"));
    actionMenuSelectMesh = createAction("actionMenuSelectMesh", ":/icon/icon/mesh/mesh.png");      ///< 选择网格
    actionMenuSelectMesh->setText(tr("选择网格"));
    actionAddMesh = createAction("actionAddMesh", ":/icon/icon/mesh/mesh.png");         ///< 添加网格
    actionAddMesh->setText(tr("添加网格"));
    
    // 2. import/export panel
    actionMeshImportMesh = createAction("actionImportMesh", ":/icon/icon/mesh/import_mesh.png");      ///< 导入网格
    actionMeshImportMesh->setText(tr("导入网格"));
    actionMeshExportMesh = createAction("actionExportMesh", ":/icon/icon/mesh/export_mesh.png");      ///< 导出网格
    actionMeshExportMesh->setText(tr("导出网格"));
    
    // 2. clear panel
    actionClearMesh = createAction("actionClearMesh", ":/icon/icon/mesh/clear.png");       ///< 清除网格
    actionClearMesh->setText(tr("清除网格"));
    actionClearAllMesh = createAction("actionClearAllMesh", ":/icon/icon/mesh/clear_all.png");      ///< 清除所有网格
    actionClearAllMesh->setText(tr("清除所有网格"));
    actionDeletMeshSequenen = createAction("actionDeletMeshSequenen", ":/icon/icon/mesh/delete_seq.png");  ///< 删除网格序列
    actionDeletMeshSequenen->setText(tr("删除序列"));
    
    // 4. Evaluate panel
    actionMeshMeasure = createAction("actionMeshMeasure", ":/icon/icon/mesh/measure.png");     ///< 测量
    actionMeshMeasure->setText(tr("测量"));
    actionMeshStatictic = createAction("actionMeshStatictic", ":/icon/icon/mesh/statistics.png");   ///< 统计
    actionMeshStatictic->setText(tr("统计信息"));
    actionMeshPlot = createAction("actionMeshPlot", ":/icon/icon/mesh/mesh.png");        ///< 绘图
    actionMeshPlot->setText(tr("绘制"));
}

/**
 * @brief 构建研究actions  
 */
void FCAppActions::buildStudyAction()
{
    //1. solver panel
    actionSolverManager = createAction("actionSolverManager", ":/icon/icon/solver/solver.png");       ///< 求解器管理
    actionSolverManager->setText(tr("求解器\n管理"));
    actionCompute= createAction("actionCompute", ":/icon/icon/solver/compute.png");            ///< 计算
    actionCompute->setText(tr("计算"));
}

/**
 * @brief 构建结果actions  
 */
void FCAppActions::buildResultAction()
{
    //1. plot panel
    action3DPlot = createAction("action3DPlot", ":/icon/icon/result/3d_plot.png");          ///< 三维绘图
    action3DPlot->setText(tr("三维绘图"));
    action2DPlot = createAction("action2DPlot", ":/icon/icon/result/2d_plot.png");          ///< 二维绘图
    action2DPlot->setText(tr("二维绘图"));
    action1DPlot = createAction("action1DPlot", ":/icon/icon/result/1d_plot.png");          ///< 一维绘图
    action1DPlot->setText(tr("一维绘图"));
    
    //2. export panel
    actionMenuDataExport = createAction("actionMenuDataExport", ":/icon/icon/result/data.png");  ///< 数据导出菜单
    actionMenuDataExport->setText(tr("数据"));
    actionNumericalDataExport = createAction("actionNumericalDataExport", ":/icon/icon/result/data.png");     ///< 数值数据导出
    actionNumericalDataExport->setText(tr("数值"));
    actionPlotDataExport = createAction("actionPlotDataExport", ":/icon/icon/result/data.png");          ///< 绘图数据导出
    actionPlotDataExport->setText(tr("绘图"));
    actionMeshDataExport = createAction("actionMeshDataExport", ":/icon/icon/result/data.png");          ///< 网格数据导出
    actionMeshDataExport->setText(tr("网格"));
    actionTableDataExport = createAction("actionTableDataExport", ":/icon/icon/result/data.png");          ///< 表格数据导出
    actionTableDataExport->setText(tr("表格"));
    
    actionImageExport = createAction("actionImageExport", ":/icon/icon/result/image.png");         ///< 图片导出
    actionImageExport->setText(tr("图像"));
    actionAnimationExport = createAction("actionAnimationExport", ":/icon/icon/result/animation.png");         ///< 动画导出
    actionAnimationExport->setText(tr("动画"));
    
    //3. Clear panel
    actionClearPlotData = createAction("actionClearPlotData", ":/icon/icon/result/clear.png");  ///< 清除绘图数据
    actionClearPlotData->setText(tr("清除绘\n图数据"));
}

/**
 * @brief 构建工具actions  
 */
void FCAppActions::buildToolsActions()
{
    actionPlugin = createAction("actionPlugin", ":/icon/icon/tools/plugings.png");      ///< 插件
    actionPlugin->setText(tr("插件管理"));
    actionAbout = createAction("actionAbout", ":/icon/icon/tools/about.png");       ///< 关于
    actionAbout->setText(tr("关于"));    
}

/**
 * @brief 构建其他actions  
 */
void FCAppActions::buildOtherActions()
{
    actionPreferences = createAction("actionPreferences", ":/icon/icon/preferences.png");      ///< 插件
    actionPreferences->setText(tr("首选项"));
    actionExit = createAction("actionExit", ":/icon/icon/exit.png");      
    actionExit->setText(tr("退出"));
    actionGlobalUndo = createAction("actionGlobalUndo", ":/icon/icon/undo.png");       
    actionGlobalUndo->setText(tr("撤销"));
    actionGlobalRedo = createAction("actionGlobalRedo", ":/icon/icon/redo.png");      
    actionGlobalRedo->setText(tr("重做"));
    actionGlobalCopy = createAction("actionGlobalCopy", ":/icon/icon/copy.png");      
    actionGlobalCopy->setText(tr("复制"));
    actionGlobalPaste = createAction("actionGlobalPaste", ":/icon/icon/paste.png");       
    actionGlobalPaste->setText(tr("粘贴"));
    actionGlobalDuplicate = createAction("actionGlobalDuplicate", ":/icon/icon/duplicate.png");       
    actionGlobalDuplicate->setText(tr("复制粘贴"));
    actionGlobalDelete = createAction("actionGlobalDelete", ":/icon/icon/delete.png");      
    actionGlobalDelete->setText(tr("删除"));
    actionGlobalSelectAll = createAction("actionGlobalSelectAll", ":/icon/icon/select_all.png");       
    actionGlobalSelectAll->setText(tr("选择所有"));
    actionGlobalClearSelect = createAction("actionGlobalClearSelect", ":/icon/icon/clear_selected.png");    
    actionGlobalClearSelect->setText(tr("清除选择"));
    actionGlobaFind = createAction("actionGlobaFind", ":/icon/icon/find.png");      
    actionGlobaFind->setText(tr("查找"));
}

/**
 * @brief todo:翻译
 */
void FCAppActions::retranslateUi()
{
    //todo
}

