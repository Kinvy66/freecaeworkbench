/******************************************************************************
 * File     : FCAppActions.cpp
 * Brief    : action管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCAPPACTIONS_H
#define FCAPPACTIONS_H

#include "FCActionsInterface.h"
#include "FCActionManagerAPI.h"

namespace FC 
{

class FCRecentFilesManager;
class FCACTIONMANAGER_API FCAppActions : public FCActionsInterface
{
    Q_OBJECT
public:
    FCAppActions(FCUIInterface* u);
    ~FCAppActions();
    // 发生语言变更时会调用此函数
    void retranslateUi() override;
    
    
protected:
    void buildActions();
    // 构建主页actions
    void buildMainAction();
    // 构建几何actions
    void buildGeometryAction();
    // 构建网格actions
    void buildMeshtAction();
    // 构建研究actions
    void buildStudyAction();
    // 构建结果actions
    void buildResultAction();
    // 构建工具actions
    void buildToolsActions();
    // 建立其他的actions
    void buildOtherActions();
    
public:
    //===================================================
    // 主页标签 Main Category
    //===================================================
    // 1. file pannel
    QAction* actionNew;             ///< 打开
    QAction* actionOpen;           ///< 打开
    QAction* actionSave;           ///< 保存
    QAction* actionSaveAs;         ///< 另存为
    // QAction* actionAppendProject;  ///< 追加工程
    
    // 2. model pannel
    QAction* actionHomeImportGeometry;     ///< 导入几何
    QAction* actionHomeImportMesh;          ///< 导入网格
    
    // 3. layout pannel
    QAction* actionWindowViews;          ///< 窗口
    QAction* actionResetLayout;          ///< 重置布局
    
    
    //===================================================
    // 几何标签 Geometry Category
    //===================================================
    // 1. import/export pannel
    QAction* actionGeometryModelBuildAll; ///< 导入几何模型
    QAction* actionImportGeometryModel; ///< 导入几何模型
    QAction* actionExportGeometryModel;     ///< 导出几何模型
    QAction* actionInsertSequenen;      ///< 导出几何模型
    
    // 2. create geometry pannel
    QAction* actionCreateCUbe;              ///< 立方体
    QAction* actionCreateCone;              ///< 圆锥体
    QAction* actionCreateCylinder;          ///< 圆柱体
    QAction* actionCreateSphere;            ///< 球体
    QAction* actionCreateTorus;             ///< 圆环
    QAction* actionCreateHelix;             ///< 螺旋
    QAction* actionMenuCreateMoreGemetryModel;  ///<< 更多Menu
    QAction* actionCreatorBezierCurve;      ///<< 贝塞尔曲线
    QAction* actionCreatorTetrahedron;      ///<< 四面体
    
    // 3. work plane pannel
    QAction* actionMenuSelectWorkPlane;     ///< 选择工作平面
    QAction* actionWorkPlane;           ///< 工作平面
    QAction* actionExtrude;             ///< 拉伸
    QAction* actionRevolve;             ///< 回旋
    QAction* actionSweep;               ///< 扫掠
    QAction* actionLoft;                ///< 放样
    
    // 4. geometry operator pannel
    QAction* actionMenuGeometryBooleanOpt;          ///< 布尔操作Menu
    QAction* actionBooleanUnion;                ///< 并集
    QAction* actionBooleanIntersection;         ///< 交集
    QAction* actionBooleanDifference;           ///< 求差
    QAction* actionBooleanCompose;              ///< 组合
    QAction* actionMenuGeometryTransformOpt;          ///< 变换操作Menu
    QAction* actionTransformRigid;                ///< 刚性变换
    QAction* actionTransformCopy;         ///< 复制
    QAction* actionTransformScale;           ///< 比例因子
    QAction* actionTransformMove;              ///< 移动
    QAction* actionTransformMirror;              ///< 镜像
    QAction* actionTransformArray;              ///< 阵列
    QAction* actionChamferOpt;          ///< 倒斜角
    QAction* actionFilletOpt;          ///< 倒圆角
    QAction* actionGeometryDelete;       ///< 删除
    
    // 5. other pannel
    QAction* actionGeometryMeasure;     ///< 测量
    QAction* actionGeometryDeletSequence;     ///< 测量
    
    //===================================================
    // 网格标签 Mesh Category
    //===================================================
    // 1.  mesh pannel
    QAction* actionMeshBuild;       ///< 构建网格
    QAction* actionMenuSelectMesh;      ///< 选择网格
    QAction* actionAddMesh;         ///< 添加网格
    
    // 2. import/export pannel
    QAction* actionMeshImportMesh;      ///< 导入网格
    QAction* actionMeshExportMesh;      ///< 导出网格
    
    
    // 2. clear pannel
    QAction* actionClearMesh;       ///< 清除网格
    QAction* actionClearAllMesh;      ///< 清除所有网格
    QAction* actionDeletMeshSequenen;  ///< 删除网格序列
    
    // 3. other pannel
    QAction* actionMeshMeasure;     ///< 测量
    QAction* actionMeshStatictic;   ///< 统计
    QAction* actionMeshPlot;        ///< 绘图
    
    
    //===================================================
    // 研究标签 Study Category
    //===================================================
    //1. solver pannel
    QAction* actionSolverManager;       ///< 求解器管理
    QAction* actionCompute;             ///< 计算
    
    
    //===================================================
    // 结果标签 Result Category
    //===================================================
    //1. plot pannel
    QAction* action3DPlot;          ///< 三维绘图
    QAction* action2DPlot;          ///< 二维绘图
    QAction* action1DPlot;          ///< 一维绘图
    
    //2. export pannel
    QAction* actionMenuDataExport;  ///< 数据导出菜单
    QAction* actionNumericalDataExport;     ///< 数值数据导出
    QAction* actionPlotDataExport;          ///< 绘图数据导出
    QAction* actionMeshDataExport;          ///< 网格数据导出
    QAction* actionTableDataExport;          ///< 表格数据导出
    
    QAction* actionImageExport;         ///< 图片导出
    QAction* actionAnimationExport;         ///< 动画导出
    
    
    //3. Clear pannel
    QAction* actionClearPlotData;  ///< 清除绘图数据 
    
    
    //===================================================
    // 工具标签 Tools Category
    //===================================================
    QAction* actionPlugin;      ///< 插件
    QAction* actionAbout;       ///< 关于
    
    
    //===================================================
    // 其他action
    //===================================================
    QAction* actionPreferences;        ///< 首选项
    QAction* actionExit;               ///< 退出
    QAction* actionGlobalUndo;         
    QAction* actionGlobalRedo;
    QAction* actionGlobalCopy;
    QAction* actionGlobalPaste;
    QAction* actionGlobalDuplicate;
    QAction* actionGlobalDelete;
    QAction* actionGlobalSelectAll;
    QAction* actionGlobalClearSelect;
    QAction* actionGlobaFind;
    
    
    //===================================================
    // 主题
    //===================================================
    QAction* actionRibbonThemeOffice2013;      ///< office2013主题
    QAction* actionRibbonThemeOffice2016Blue;  ///< office2016主题
    QAction* actionRibbonThemeOffice2021Blue;  ///< office2021主题
    QAction* actionRibbonThemeDark;            ///< dark主题
    QActionGroup* actionGroupRibbonTheme;      ///< actionRibbonTheme* 的actionGroup
    
    // 最近打开的文件
    FCRecentFilesManager* recentFilesManager { nullptr };
    
};
} // namespace FC

#ifndef FC_APP_ACTIONS
/**
 * @def 获取@sa FCAppCore 实例
 * @note 使用此宏需要以下两个头文件：
 * -# FCAppCore.h
 * -# FCAppUI.h
 */
#define FC_APP_ACTIONS FC::FCAppCore::getInstance().getUi()->getActions()
#endif

#endif // FCAPPACTIONS_H
