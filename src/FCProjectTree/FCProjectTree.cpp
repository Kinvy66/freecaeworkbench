/**
 * @file FCProjectTree.cpp
 * @brief 工程树管理
 * @date 2025-11-18
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCProjectTree.h"
#include "FCTreeWidget.h"
#include <QTreeWidgetItem>
#include <QDebug>
// #include "FCAppActions.h"

namespace FC 
{

FCProjectTree::FCProjectTree(QObject *parent)
    : QObject(parent)
{
    mTreeWidget = new FCTreeWidget();
    createDefaultProject();
    mTreeWidget->expandToDepth(1);
    
    connect(mTreeWidget, &QTreeWidget::currentItemChanged,
            this, &FCProjectTree::currentItemChanged);
}

/**
 * @brief 创建空白默认工程
 * @param name
 */
void FCProjectTree::createDefaultProject(const QString &name)
{
    QTreeWidgetItem* projectRoot = new QTreeWidgetItem();
    projectRoot->setData(0, RoleType::ContextActions, FCTreeWidget::MenuProjectRoot);
    projectRoot->setText(0, name);
    projectRoot->setIcon(0,QIcon(":/icon/icon/project.png"));
    mTreeWidget->addTopLevelItem(projectRoot);
    mTreeWidget->setCurrentItem(projectRoot);
    
    createGlobalDefine();
    createComponent();
    createStudy();
    createResult();
    // buildMenuAction();
    
    buildProjectRootActions();
    buildGlobalDefineuActions();
    buildCompnentActions();
    buildStudyActions();
    buildResultActions();
    
    connect(mTreeWidget,&FCTreeWidget::actionTriggered,
            this, &FCProjectTree::onTreeActionTriggered);
}

/**
 * @brief 获取树形结构widget
 * @return 
 */
FCTreeWidget *FCProjectTree::treeWidget() const
{
     return mTreeWidget; 
}

/**
 * @brief 右键菜单slot
 * @param menuType
 * @param action
 * @param item
 */
void FCProjectTree::onTreeActionTriggered(int menuType,
                                          const QString &objectName,
                                          QTreeWidgetItem *item)
{
    
    QString actionName = objectName;
    
    if (actionName == "actionParameter") {
        addNewParameter(item);
    }
    else if (actionName == "actionVariable") {
        addNewVariable(item);
    }
    else if (actionName == "actionFunction") {
        addNewFunction(item);
    }
}

/**
 * @brief 创建全局定义的子树
 */
void FCProjectTree::createGlobalDefine()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* globalDefin = new QTreeWidgetItem(root);
    globalDefin->setText(0, tr("全局定义"));
    globalDefin->setIcon(0,QIcon(":/icon/icon/global_define.png"));
    globalDefin->setData(0, RoleType::ContextActions, FCTreeWidget::MenuGlobalDefine);

    QTreeWidgetItem* parameter = new QTreeWidgetItem(globalDefin);
    parameter->setText(0, tr("参数1"));
    parameter->setIcon(0,QIcon(":/icon/icon/parameter.png"));
    parameter->setData(0, RoleType::ContextActions, FCTreeWidget::MenuParameterGroup);
    
    QTreeWidgetItem* variable = new QTreeWidgetItem(globalDefin);  // 
    variable->setText(0, tr("变量1"));
    variable->setIcon(0,QIcon(":/icon/icon/variable.png"));
    variable->setData(0, RoleType::ContextActions, FCTreeWidget::MenuVariable);
    
    
    QTreeWidgetItem* function = new QTreeWidgetItem(globalDefin);
    function->setText(0, tr("函数1"));
    function->setIcon(0,QIcon(":/icon/icon/funtion.png"));
    function->setData(0, RoleType::ContextActions, FCTreeWidget::MenuFunction);
    
    
    
    // QTreeWidgetItem* material = new QTreeWidgetItem(globalDefin);
    // material->setText(0, tr("材料"));
    // material->setIcon(0,QIcon(":/icon/icon/material.png"));
       
}

/**
 * @brief 创建组件子树
 */
void FCProjectTree::createComponent()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* component = new QTreeWidgetItem(root);
    component->setText(0, tr("组件"));
    component->setIcon(0,QIcon(":/icon/icon/component.png"));
    component->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponent);
    
    QTreeWidgetItem* define = new QTreeWidgetItem(component);
    define->setText(0, tr("定义"));
    define->setIcon(0,QIcon(":/icon/icon/define.png"));
    define->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponentDefin);
    
    QTreeWidgetItem* gemometry = new QTreeWidgetItem(component);
    gemometry->setText(0, tr("几何"));
    gemometry->setIcon(0,QIcon(":/icon/icon/geometry.png"));
    gemometry->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponentGeometry);
    mGeoRoot = gemometry;
    
    // QTreeWidgetItem* material = new QTreeWidgetItem(component);
    // material->setText(0, tr("材料"));
    // material->setIcon(0,QIcon(":/icon/icon/material.png"));
    // material->setData(0, Qt::UserRole, FCTreeWidget::MenuComponentGeometry);
    // material->setData(0, Qt::UserRole, FCTreeWidget::MenuComponentMaterial);
    
    QTreeWidgetItem* physic = new QTreeWidgetItem(component);
    physic->setText(0, tr("物理场"));
    physic->setIcon(0,QIcon(":/icon/icon/undefined.png"));
    physic->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponentPhysic);
    
    QTreeWidgetItem* mesh = new QTreeWidgetItem(component);
    mesh->setText(0, tr("网格"));
    mesh->setIcon(0,QIcon(":/icon/icon/mesh.png"));
    mesh->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponentMesh);
    mMeshRoot = mesh;
    
}

/**
 * @brief 创建研究子树
 */
void FCProjectTree::createStudy()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* study = new QTreeWidgetItem(root);
    study->setText(0, tr("研究"));
    study->setIcon(0,QIcon(":/icon/icon/study1.png"));
    study->setData(0, RoleType::ContextActions, FCTreeWidget::MenuStudyGrop);
    
    
    QTreeWidgetItem* step1 = new QTreeWidgetItem(study);
    step1->setText(0, tr("步骤1"));
    step1->setIcon(0,QIcon(":/icon/icon/study1.png"));
    step1->setData(0, RoleType::ContextActions, FCTreeWidget::MenuStudyStep);
    
    QTreeWidgetItem* step2 = new QTreeWidgetItem(study);
    step2->setText(0, tr("步骤2"));
    step2->setIcon(0,QIcon(":/icon/icon/study1.png"));
    step2->setData(0, RoleType::ContextActions, FCTreeWidget::MenuStudyStep);
    
}

/**
 * @brief 创建结果子树
 */
void FCProjectTree::createResult()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* result = new QTreeWidgetItem(root);
    result->setText(0, tr("结果"));
    result->setIcon(0,QIcon(":/icon/icon/result.png"));
    result->setData(0, RoleType::ContextActions, FCTreeWidget::MenuResult);
    
    
    QTreeWidgetItem* plot3d = new QTreeWidgetItem(result);
    plot3d->setText(0, tr("3维绘图组"));
    plot3d->setIcon(0,QIcon(":/icon/icon/3d_plot.png"));
    plot3d->setData(0, RoleType::ContextActions, FCTreeWidget::MenuResult3DPlotGroup);
    mPostProcessingRoot = plot3d;
    
    QTreeWidgetItem* plot2d = new QTreeWidgetItem(result);
    plot2d->setText(0, tr("2维绘图组"));
    plot2d->setIcon(0,QIcon(":/icon/icon/2d_plot.png"));
    plot2d->setData(0, RoleType::ContextActions, FCTreeWidget::MenuResult2DPlotGroup);
    
    QTreeWidgetItem* plot1d = new QTreeWidgetItem(result);
    plot1d->setText(0, tr("1维绘图组"));
    plot1d->setIcon(0,QIcon(":/icon/icon/1d_plot.png"));
    plot1d->setData(0, RoleType::ContextActions, FCTreeWidget::MenuResult1DPlotGroup);
    
}

/**
 * @brief 构建项目根目录右键菜单模板
 */
void FCProjectTree::buildProjectRootActions()
{
    using AT = FCTreeWidget::ActionTemplate;
    
    
    AT settings = AT(tr("设置"), QIcon(":/icon/icon/undefined.png"),"projectSetting");
    AT property = AT(tr("属性"), QIcon(":/icon/icon/undefined.png"),"projectProperty");
    AT help = AT(tr("帮助"), QIcon(":/icon/icon/undefined.png"),"projectHelp");
    
    
    // 工程根菜单
    QList<AT> list;
    list.append(AT(tr("添加组件"), "addComponent"));
    list.append(AT::sep());
    list.append(settings);
    list.append(property);
    list.append(AT::sep());
    list.append(help);
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuProjectRoot, list);
}

/**
 * @brief 构建全局定义及其子项目的右键菜单模板
 */
void FCProjectTree::buildGlobalDefineuActions()
{
    using AT = FCTreeWidget::ActionTemplate;
    
    
    AT moveUp = AT(tr("上移"), QIcon(":/icon/icon/moveup.png"), "moveUp");
    AT moveDown = AT(tr("下移"), QIcon(":/icon/icon/movedown.png"), "moveDown");
    AT copy = AT(tr("复制"), QIcon(":/icon/icon/undefined.png"), "copy");
    AT duplicate = AT(tr("复制粘贴"), QIcon(":/icon/icon/undefined.png"), "duplicate");
    AT disable = AT(tr("禁用"), QIcon(":/icon/icon/undefined.png"), "disable");
    AT rename = AT(tr("重命名"), QIcon(":/icon/icon/undefined.png"), "rename");
    AT delet = AT(tr("删除"), QIcon(":/icon/icon/undefined.png"), "delet");
    AT group = AT(tr("分组"), QIcon(":/icon/icon/undefined.png"), "group");
    AT settings = AT(tr("设置"), QIcon(":/icon/icon/undefined.png"), "settings");
    AT property = AT(tr("属性"), QIcon(":/icon/icon/undefined.png"), "property");
    AT help = AT(tr("帮助"), QIcon(":/icon/icon/help.png"), "help");
    
    // 全局定义
    QList<AT> globalDefinActions;  
    AT actionParameter = AT(tr("参数"), QIcon(":/icon/icon/global_define.png"), "actionParameter");
    AT actionVariable = AT(tr("变量"), QIcon(":/icon/icon/global_define.png"), "actionVariable");
    AT actionFunction = AT(tr("函数"), QIcon(":/icon/icon/global_define.png"), "actionFunction");
    globalDefinActions.append(actionParameter);
    globalDefinActions.append(actionVariable);
    globalDefinActions.append(actionFunction);
    globalDefinActions.append(AT::sep());
    globalDefinActions.append(help);
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuGlobalDefine, globalDefinActions);
    
    // 全局定义-参数
    QList<AT> parameterGroupActions;
    AT actionParameterCase = AT(tr("参数实例"), QIcon(":/icon/icon/global_define.png"));
    parameterGroupActions.append(actionParameterCase);
    parameterGroupActions.append(AT::sep());
    parameterGroupActions.append(copy);
    parameterGroupActions.append(group);
    parameterGroupActions.append(delet);
    parameterGroupActions.append(rename);
    parameterGroupActions.append(AT::sep());
    parameterGroupActions.append(settings);
    parameterGroupActions.append(property);
    parameterGroupActions.append(AT::sep());
    parameterGroupActions.append(help);
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuParameterGroup, parameterGroupActions);
    
    // 全局定义-变量
    QList<AT> variableGroupActions;
    variableGroupActions.append(copy);
    variableGroupActions.append(duplicate);
    variableGroupActions.append(group);
    variableGroupActions.append(delet);
    variableGroupActions.append(disable);
    variableGroupActions.append(rename);
    variableGroupActions.append(AT::sep());
    variableGroupActions.append(settings);
    variableGroupActions.append(property);
    variableGroupActions.append(AT::sep());
    variableGroupActions.append(help);
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuVariable, variableGroupActions);
    
    // 全局定义-函数
    QList<AT> functionGroupActions;
    functionGroupActions.append(copy);
    functionGroupActions.append(duplicate);
    functionGroupActions.append(group);
    functionGroupActions.append(delet);
    functionGroupActions.append(disable);
    functionGroupActions.append(rename);
    functionGroupActions.append(AT::sep());
    functionGroupActions.append(settings);
    functionGroupActions.append(property);
    functionGroupActions.append(AT::sep());
    functionGroupActions.append(help);
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuFunction,
                                       functionGroupActions);
}

/**
 * @brief 构建组件及其子项目的右键菜单模板
 */
void FCProjectTree::buildCompnentActions()
{
    using AT = FCTreeWidget::ActionTemplate;
    
    
    AT moveUp = AT(tr("上移"), QIcon(":/icon/icon/moveup.png"), "moveUp");
    AT moveDown = AT(tr("下移"), QIcon(":/icon/icon/movedown.png"), "moveDown");
    AT copy = AT(tr("复制"), QIcon(":/icon/icon/undefined.png"), "copy");
    AT duplicate = AT(tr("复制粘贴"), QIcon(":/icon/icon/undefined.png"), "duplicate");
    AT disable = AT(tr("禁用"), QIcon(":/icon/icon/undefined.png"), "disable");
    AT rename = AT(tr("重命名"), QIcon(":/icon/icon/undefined.png"), "rename");
    AT delet = AT(tr("删除"), QIcon(":/icon/icon/undefined.png"), "delet");
    AT group = AT(tr("分组"), QIcon(":/icon/icon/undefined.png"), "group");
    AT settings = AT(tr("设置"), QIcon(":/icon/icon/undefined.png"), "settings");
    AT property = AT(tr("属性"), QIcon(":/icon/icon/undefined.png"), "property");
    AT help = AT(tr("帮助"), QIcon(":/icon/icon/help.png"), "help");
    
    // 组件
    QList<AT> componentGroupActions;
    componentGroupActions.append(copy);
    componentGroupActions.append(duplicate);
    componentGroupActions.append(delet);
    componentGroupActions.append(AT::sep());
    componentGroupActions.append(settings);
    componentGroupActions.append(property);
    componentGroupActions.append(AT::sep());
    componentGroupActions.append(help);
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuComponent,
                                    componentGroupActions);
    
    
    // 组件-几何
    QList<AT> componentGeometryActions;
    
    componentGeometryActions.append(AT(tr("全部构建"),
                                       QIcon(":/icon/icon/geometry/buil_all.png"),
                                       "build_all"));
    componentGeometryActions.append(AT::sep());
    componentGeometryActions.append(AT(tr("导入"),
                                       QIcon(":/icon/icon/geometry/import_geometry.png"),
                                       "import_geometry"));
    componentGeometryActions.append(AT(tr("虚拟操作"),
                                       "virtual_opt"));
    componentGeometryActions.append(AT::sep());
    componentGeometryActions.append(AT(tr("圆柱体"),
                                       QIcon(":/icon/icon/geometry/cylinder.png"),
                                       "cylinder"));
    componentGeometryActions.append(AT(tr("圆锥体"),
                                       QIcon(":/icon/icon/geometry/cone.png"),
                                       "cone"));
    componentGeometryActions.append(AT(tr("球体"),
                                       QIcon(":/icon/icon/geometry/sphere.png"),
                                       "sphere"));
    componentGeometryActions.append(AT(tr("长方体"),
                                       QIcon(":/icon/icon/geometry/cube.png"),
                                       "cube"));
    AT moreModel = AT(tr("更多体素"),"moreModel");
    moreModel.add(AT(tr("圆环"), QIcon(":/icon/icon/geometry/torus.png"), "torus"));
    moreModel.add(AT(tr("螺旋"), QIcon(":/icon/icon/geometry/helix.png"), "helix"));
    componentGeometryActions.append(moreModel);
    componentGeometryActions.append(AT::sep());
    componentGeometryActions.append(AT(tr("工作平面"),
                                       QIcon(":/icon/icon/geometry/workplane.png"),
                                       "workplane"));
    componentGeometryActions.append(AT(tr("回旋"),
                                       QIcon(":/icon/icon/geometry/revolve.png"),
                                       "revolve"));
    componentGeometryActions.append(AT(tr("拉伸"),
                                       QIcon(":/icon/icon/geometry/extrude.png"),
                                       "extrude"));
    componentGeometryActions.append(AT(tr("扫掠"),
                                       QIcon(":/icon/icon/geometry/sweep.png"),
                                       "sweep"));
    componentGeometryActions.append(AT::sep());
    
    AT booleanOpt = AT(tr("布尔操作"),"moreModel");
    booleanOpt.add(AT(tr("并集"), QIcon(":/icon/icon/geometry/boolean_opt.png"), "union"));
    booleanOpt.add(AT(tr("交集"), QIcon(":/icon/icon/geometry/boolean_opt.png"), "intersection"));
    booleanOpt.add(AT(tr("求差"), QIcon(":/icon/icon/geometry/boolean_opt.png"), "difference"));
    booleanOpt.add(AT(tr("组合"), QIcon(":/icon/icon/geometry/boolean_opt.png"), "compose"));
    componentGeometryActions.append(booleanOpt);
    AT transformOpt = AT(tr("变化操作"),"moreModel");
    transformOpt.add(AT(tr("刚性变换"), QIcon(":/icon/icon/geometry/transform.png"), "transform_rigid"));
    transformOpt.add(AT(tr("复制"), QIcon(":/icon/icon/geometry/transform.png"), "transform_copy"));
    transformOpt.add(AT(tr("比例因子"), QIcon(":/icon/icon/geometry/transform.png"), "transform_scale"));
    transformOpt.add(AT(tr("移动"), QIcon(":/icon/icon/geometry/transform.png"), "transform_move"));
    transformOpt.add(AT(tr("镜像"), QIcon(":/icon/icon/geometry/transform.png"), "transform_mirror"));
    transformOpt.add(AT(tr("阵列"), QIcon(":/icon/icon/geometry/transform.png"), "transform_array"));
    componentGeometryActions.append(transformOpt);
    componentGeometryActions.append(AT::sep());
    
    componentGeometryActions.append(AT(tr("测量"),
                                       QIcon(":/icon/icon/geometry/measure.png"),
                                       "measure"));
    componentGeometryActions.append(AT(tr("插入序列"),
                                       QIcon(":/icon/icon/geometry/insert_seq.png"),
                                       "insert_seq"));
    componentGeometryActions.append(AT(tr("导出"),
                                       QIcon(":/icon/icon/geometry/export_geometry.png"),
                                       "export_geometry"));
    componentGeometryActions.append(AT(tr("删除序列"),
                                       QIcon(":/icon/icon/geometry/delete_seq.png"),
                                       "delete_seq"));
    componentGeometryActions.append(AT::sep());
    componentGeometryActions.append(settings);
    componentGeometryActions.append(property);
    componentGeometryActions.append(AT::sep());
    componentGeometryActions.append(help);
    
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuComponentGeometry,
                                    componentGeometryActions);
    
    // 几何体实体
    QList<AT> geometryEntityActions;
    
    geometryEntityActions.append(moveUp);
    geometryEntityActions.append(moveDown);
    geometryEntityActions.append(copy);
    geometryEntityActions.append(duplicate);
    geometryEntityActions.append(delet);
    geometryEntityActions.append(disable);
    geometryEntityActions.append(rename);
    geometryEntityActions.append(AT::sep());
    geometryEntityActions.append(settings);
    geometryEntityActions.append(property);
    geometryEntityActions.append(AT::sep());
    geometryEntityActions.append(help);
    
    mTreeWidget->setActionTemplates(FCTreeWidget::MenuComponentGeometryEntity,
                                    geometryEntityActions);
    
}

/**
 * @brief 构建研究及其子项目的右键菜单模板
 */
void FCProjectTree::buildStudyActions()
{
    
}

/**
 * @brief 构建结果及其子项目的右键菜单模板
 */
void FCProjectTree::buildResultActions()
{
    
}

/**
 * @brief 添加参数item
 * @param parent
 */
void FCProjectTree::addNewParameter(QTreeWidgetItem *parent)
{
    QString name = nextChildName(parent, tr("参数"));
    QTreeWidgetItem* item = new QTreeWidgetItem();
    
    // 找到同类型（ParameterGroup）的最后位置
    int insertPos = findInsertIndexByType(parent, FCTreeWidget::MenuParameterGroup);
    
    item->setText(0, name);
    item->setIcon(0, QIcon(":/icon/icon/parameter.png"));
    item->setData(0, RoleType::ContextActions, FCTreeWidget::MenuParameterGroup);
    
    parent->insertChild(insertPos, item);
    
    mTreeWidget->expandItem(parent);
}

/**
 * @brief 添加变量item
 * @param parent
 */
void FCProjectTree::addNewVariable(QTreeWidgetItem *parent)
{
    QString name = nextChildName(parent, tr("变量"));
    
    // 找到同类型（ParameterGroup）的最后位置
    int insertPos = findInsertIndexByType(parent, FCTreeWidget::MenuVariable);
    
    QTreeWidgetItem* item = new QTreeWidgetItem();
    
    item->setText(0, name);
    item->setIcon(0, QIcon(":/icon/icon/variable.png"));
    item->setData(0, RoleType::ContextActions, FCTreeWidget::MenuVariable);
    
    parent->insertChild(insertPos, item);
    
    mTreeWidget->expandItem(parent);
}

/**
 * @brief 添加函数item
 * @param parent
 */
void FCProjectTree::addNewFunction(QTreeWidgetItem *parent)
{
    QString name = nextChildName(parent, tr("函数"));
    
    // 找到同类型（ParameterGroup）的最后位置
    int insertPos = findInsertIndexByType(parent, FCTreeWidget::MenuFunction);
    
    QTreeWidgetItem* item = new QTreeWidgetItem();
    
    item->setText(0, name);
    item->setIcon(0, QIcon(":/icon/icon/funtion.png"));
    item->setData(0, RoleType::ContextActions, FCTreeWidget::MenuFunction);
    
    parent->insertChild(insertPos, item);
    
    mTreeWidget->expandItem(parent);
}

/**
 * @brief 查找插入位置
 * @param parent
 * @param typeValue
 * @return 
 */
int FCProjectTree::findInsertIndexByType(QTreeWidgetItem *parent, int typeValue)
{
    int insertPos = 0;
    int childCount = parent->childCount();
    
    for (int i = 0; i < childCount; i++) {
        QTreeWidgetItem* child = parent->child(i);
        int t = child->data(0, RoleType::ContextActions).toInt();
        
        if (t == typeValue)
            insertPos = i + 1;   // 插入在最后一个同类型 item 后面
    }
    
    return insertPos;  // 如果不存在同类型，则插入到第一个同类型出现的位置（可能为 0）
}

QString  FCProjectTree::nextChildName(QTreeWidgetItem *parent, const QString &prefix)
{
    int maxIndex = 0;
    
    for (int i = 0; i < parent->childCount(); ++i) {
        QString text = parent->child(i)->text(0);
        
        if (text.startsWith(prefix)) {
            QString num = text.mid(prefix.length());
            bool ok;
            int index = num.toInt(&ok);
            if (ok && index > maxIndex) {
                maxIndex = index;
            }
        }
    }
    return prefix + QString::number(maxIndex + 1);
}

/**
 * @brief 更新/添加几何体节点
 * @param id
 * @param name
 */
void FCProjectTree::updateGeometryTree(const IdType id, const QString& name)
{
   
    // 遍历 GeoRoot 的所有子节点
    for (int i = 0; i < mGeoRoot->childCount(); ++i) {
        QTreeWidgetItem* child = mGeoRoot->child(i);
        
        QVariant var = child->data(0, RoleType::EntityItmeID);
        if (var.canConvert<IdType>()) {
            IdType itemId = var.value<IdType>();
            
            if (itemId == id) {
                // 找到，更新名字
                child->setText(0, name);
                return;
            }
        }
    }
    
    // 添加新 item
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setIcon(0, QIcon(":/icon/icon/geometry/cube.png"));
    item->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponentGeometryEntity);
    item->setData(0, RoleType::EntityItmeID, QVariant::fromValue(id));
    item->setData(0, RoleType::EntityItmeType, QVariant::fromValue(EntityType::GeometryEntity));
    
    mGeoRoot->addChild(item);
    mTreeWidget->expandItem(mGeoRoot);
    mTreeWidget->setCurrentItem(item);
}

void FCProjectTree::updateMeshTree(const IdType id, const QString &name)
{
    // 遍历 GeoRoot 的所有子节点
    for (int i = 0; i < mMeshRoot->childCount(); ++i) {
        QTreeWidgetItem* child = mMeshRoot->child(i);
        
        QVariant var = child->data(0, RoleType::EntityItmeID);
        if (var.canConvert<IdType>()) {
            IdType itemId = var.value<IdType>();
            
            if (itemId == id) {
                // 找到，更新名字
                child->setText(0, name);
                return;
            }
        }
    }
    
    // 添加新 item
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setIcon(0, QIcon(":/icon/icon/mesh.png"));
    item->setData(0, RoleType::ContextActions, FCTreeWidget::MenuComponentMeshEntity);
    item->setData(0, RoleType::EntityItmeID, QVariant::fromValue(id));
    item->setData(0, RoleType::EntityItmeType, QVariant::fromValue(EntityType::MeshEmtity));
    
    mMeshRoot->addChild(item);
    mTreeWidget->expandItem(mMeshRoot);
    mTreeWidget->setCurrentItem(item);
}

void FCProjectTree::updatePostProcessingTree(const IdType id, const QString &name)
{
    if (!mPostProcessingRoot) {
        qWarning() << "PostProcessing root not initialized";
        return;
    }
    
    // 遍历 PostProcessingRoot 的所有子节点
    for (int i = 0; i < mPostProcessingRoot->childCount(); ++i) {
        QTreeWidgetItem* child = mPostProcessingRoot->child(i);
        
        QVariant var = child->data(0, RoleType::EntityItmeID);
        if (var.canConvert<IdType>()) {
            IdType itemId = var.value<IdType>();
            
            if (itemId == id) {
                // 找到，更新名字
                child->setText(0, name);
                return;
            }
        }
    }
    
    // 添加新 item
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setIcon(0, QIcon(":/icon/icon/3d_plot.png"));
    item->setData(0, RoleType::ContextActions, FCTreeWidget::MenuResult3DPlot);
    item->setData(0, RoleType::EntityItmeID, QVariant::fromValue(id));
    item->setData(0, RoleType::EntityItmeType, QVariant::fromValue(EntityType::PostProcessingEntity));
    
    mPostProcessingRoot->addChild(item);
    mTreeWidget->expandItem(mPostProcessingRoot);
    mTreeWidget->setCurrentItem(item);
}

/**
 * @brief 删除当前选中的几何体
 */
void FCProjectTree::deleteEntityItem()
{
    QTreeWidgetItem* item = mTreeWidget->currentItem();
    if (!item) return;
    
    // 获取 item 的父节点或顶层节点管理器
    QTreeWidgetItem* parent = item->parent();
    
    // 删除几何实体（你的工程逻辑）
    QVariant var = item->data(0, RoleType::EntityItmeID);
    QVariant typeVar = item->data(0, RoleType::EntityItmeType);
    EntityType type = EntityType::EntityTypeNone;
    
    if (var.canConvert<IdType>()) {
        IdType itemId = var.value<IdType>();
        if (itemId != 0) {
            QString name = item->text(0);
            type = typeVar.value<EntityType>();
            if(type == GeometryEntity ) {
                emit deleteGeometryEntity(itemId, name);
            } else if (type == MeshEmtity) {
                emit deleteMeshEntity(itemId, name);
            } 
        }
    }
    
    // 计算删除后的新选中项
    QTreeWidgetItem* newSelected = nullptr;
    
    if (parent) {
        // 子节点情况
        int index = parent->indexOfChild(item);
        
        // 1. 优先选中“下一项”
        if (index + 1 < parent->childCount()) {
            newSelected = parent->child(index + 1);
        }
        // 2. 无下一项 → 选中“上一项”
        else if (index - 1 >= 0) {
            newSelected = parent->child(index - 1);
        }
    }
    else {
        // 顶层节点情况
        int index = mTreeWidget->indexOfTopLevelItem(item);
        
        if (index + 1 < mTreeWidget->topLevelItemCount()) {
            newSelected = mTreeWidget->topLevelItem(index + 1);
        }
        else if (index - 1 >= 0) {
            newSelected = mTreeWidget->topLevelItem(index - 1);
        }
    }
    
    // 真正删除节点
    delete item;
    item = nullptr;
    
    // 设置新的选中项
    if (newSelected) {
        mTreeWidget->setCurrentItem(newSelected);
    } else {
        // 删除完后树空了，则发出空选中信号
        mTreeWidget->setCurrentItem(nullptr);
    }
}


} // namespace FC

