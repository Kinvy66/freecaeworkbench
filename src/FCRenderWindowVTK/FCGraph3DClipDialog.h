/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**********************************************************************
 * @file   FCGraph3DClipDialog.h
 * @brief  三维渲染窗口裁切对话框
 * @author BaGuijun (baguijun@163.com)
 * @date   2025-04-09
 *********************************************************************/
#ifndef _FCGraph3DClipDialog_H
#define _FCGraph3DClipDialog_H

// #include "FITK_Kernel/FITKCore/FITKAbstractGUIDialog.h"
#include <QDialog>

namespace Ui {
    class FCGraph3DClipDialog;
}

class vtkActor;

namespace Comp
{
    class FCGraph3DWindowVTK;
    class FCGraph3DWidgetPlane;
    class FCGraphObjectVTK;
    /**
     * @brief  三维渲染窗口裁切对话框
     * @author BaGuijun (baguijun@163.com)
     * @date   2025-04-09
     */
    class FCGraph3DClipDialog : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief    构造函数
         * @param[i] graph3DWindow                三维渲染窗口
         * @param[i] clipCreateNewModel           裁切是否产生新模型
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-09
         */
        FCGraph3DClipDialog(FCGraph3DWindowVTK* graph3DWindow, bool clipCreateNewModel);
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-09
         */
        virtual ~FCGraph3DClipDialog();
        /**
         * @brief    初始化
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        void init();
    protected:
        /**
         * @brief    显示事件重写
         * @param[i] event                 事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        void showEvent(QShowEvent *event) override;
        /**
         * @brief    获取边界
         * @param[i] boundValue                边界(Xmin,Xmax,Ymin,Ymax,Zmin,Zmax)
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void getBound(double* boundValue);
        /**
         * @brief    更新方向与中心点位置
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void updateValue();
        /**
         * @brief    启动裁切(裁切在原模型上进行裁切，不会产生新的模型，原来模型的属性保留)
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void startClipInOldModel();
        /**
         * @brief    启动裁切(裁切会产生新的模型，原来模型的属性不保留)
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void startClipCreateNewModel();
        /**
         * @brief    终止裁切
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void stopClipInOldModel();
        /**
         * @brief    终止裁切
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void stopClipCreateNewModel();
    protected slots:
        ;
        /**
         * @brief    中心点X轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_OriginX_editingFinished();
        /**
         * @brief    中心点Y轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_OriginY_editingFinished();
        /**
         * @brief    中心点Z轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_OriginZ_editingFinished();
        /**
         * @brief    方向X轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_NormalX_editingFinished();
        /**
         * @brief    方向Y轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_NormalY_editingFinished();
        /**
         * @brief    方向Z轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_NormalZ_editingFinished();
        /**
         * @brief    应用按钮点击事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_pushButton_Apply_clicked();
        /**
         * @brief    裁切界面是否显示事件
         * @param[i] checked                       是否显示
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_checkBox_PlaneWidget_clicked(bool checked);
        /**
         * @brief    VTKWidget回调槽函数
         * @param[i] origin                  中心点
         * @param[i] normal                  方向
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void slot_ValueChange(double* origin, double* normal);
    protected:
        /**
         * @brief  ui对象
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-09
         */
        Ui::FCGraph3DClipDialog* _ui = nullptr;
        /**
         * @brief  三维渲染窗口
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-09
         */
        FCGraph3DWindowVTK* _graph3DWindow = nullptr;
        /**
         * @brief  三维渲染平面界面
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-09
         */
        FCGraph3DWidgetPlane* _graph3DWidgetPlane = nullptr;
        /**
         * @brief  裁切演员对象
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-10
         */
        FCGraphObjectVTK* _clipObj = nullptr;
        /**
         * @brief  演员可见性映射表（仅限在模式为产生新模型下有用）
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-18
         */
        QHash<vtkActor*, bool> _actionPro = {};
        /**
         * @brief  裁切是否产生新模型
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-18
         */
        bool _clipCreateNewModel = true;
    };
}

#endif
