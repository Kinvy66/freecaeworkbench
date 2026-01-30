/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "ui_FCGraph3DClipDialog.h"
#include "FCGraph3DClipDialog.h"
#include "FCGraph3DWindowVTK.h"
#include "FCGraph3DWidgetPlane.h"
#include "FCGraphRender.h"
#include "FCGraphObjectVTK.h"

#include "FITK_Kernel/FITKCore/FITKAbstractGraphObject.h"
#include "FITK_Interface/FITKVTKAlgorithm/FITKActorClipTool.h"
#include "FITK_Interface/FITKVTKAlgorithm/FITKGraphActor.h"

#include <vtkProp.h>
#include <vtkPlane.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkExtractGeometry.h>
#include <vtkMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkTableBasedClipDataSet.h>

//自定义类型注册
Q_DECLARE_METATYPE(ClipType)
Q_DECLARE_METATYPE(ClipInside)

namespace Comp
{
    FCGraph3DClipDialog::FCGraph3DClipDialog(FCGraph3DWindowVTK* graph3DWindow, bool clipCreateNewModel)
        : QDialog(graph3DWindow)
    , _graph3DWindow(graph3DWindow)
    , _clipCreateNewModel(clipCreateNewModel)
    {
        //自动析构
        this->setAttribute(Qt::WA_DeleteOnClose, true);
        //ui对象创建
        _ui = new Ui::FCGraph3DClipDialog();
        _ui->setupUi(this);

        _graph3DWidgetPlane = new FCGraph3DWidgetPlane(_graph3DWindow);
        connect(_graph3DWidgetPlane, SIGNAL(sigValueChange(double*, double*)), this, SLOT(slot_ValueChange(double*, double*)));
        init();
    }

    FCGraph3DClipDialog::~FCGraph3DClipDialog()
    {
        //关闭所有裁切
        if (_clipCreateNewModel == true) {
            stopClipCreateNewModel();
        }
        else {
            stopClipInOldModel();
        }

        if (_ui) {
            delete _ui;
            _ui = nullptr;
        }

        if (_graph3DWidgetPlane) {
            delete _graph3DWidgetPlane;
            _graph3DWidgetPlane = nullptr;
        }

        if (_clipObj) {
            delete _clipObj;
            _clipObj = nullptr;
        }

        if (_graph3DWindow) {
            _graph3DWindow->reRender();
        }
    }

    void FCGraph3DClipDialog::init()
    {
        if (_graph3DWidgetPlane == nullptr) {
            return;
        }

        //更新边界
        double bound[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };
        getBound(bound);
        _graph3DWidgetPlane->setBounds(bound);
        //更新方向
        double origin[3] = { 0,0,0 };
        double normal[3] = { 0,0,1 };
        origin[0] = (bound[1] - bound[0]) / 2.0 + bound[0];
        origin[1] = (bound[3] - bound[2]) / 2.0 + bound[2];
        origin[2] = (bound[5] - bound[4]) / 2.0 + bound[4];
        _graph3DWidgetPlane->setValue(origin, normal);
        _graph3DWidgetPlane->setIsShow(true);

        _ui->lineEdit_OriginX->setText(QString::number(origin[0]));
        _ui->lineEdit_OriginY->setText(QString::number(origin[1]));
        _ui->lineEdit_OriginZ->setText(QString::number(origin[2]));
        _ui->lineEdit_NormalX->setText(QString::number(normal[0]));
        _ui->lineEdit_NormalY->setText(QString::number(normal[1]));
        _ui->lineEdit_NormalZ->setText(QString::number(normal[2]));

        //添加裁切类型
        _ui->comboBox_Type->addItem(tr("Extract"), ClipType::ExtractGeometry);
        _ui->comboBox_Type->addItem(tr("Clip"), ClipType::Clip);
        _ui->comboBox_Type->setCurrentIndex(0);

        _ui->comboBox_Inside->addItem(tr("On"), QVariant::fromValue(ClipInside::On));
        _ui->comboBox_Inside->addItem(tr("Off"), QVariant::fromValue(ClipInside::Off));

        this->setWindowTitle(tr("Clip"));
    }

    void FCGraph3DClipDialog::showEvent(QShowEvent * event)
    {
        if (_graph3DWindow) {
            _graph3DWindow->reRender();
        }
        Core::FITKDialog::showEvent(event);
    }

    void FCGraph3DClipDialog::getBound(double * boundValue)
    {
        if (_graph3DWindow == nullptr) {
            return;
        }

        //计算所有演员的
        double bound[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };
        for (FCGraphObjectVTK* obj : _graph3DWindow->getAllGraphObj()) {
            if (obj == nullptr) {
                continue;
            }
            double bds[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };
            obj->getFixedBounds(bds);

            if (bds[0] < bound[0]) bound[0] = bds[0];
            if (bds[1] > bound[1]) bound[1] = bds[1];

            if (bds[2] < bound[2]) bound[2] = bds[2];
            if (bds[3] > bound[3]) bound[3] = bds[3];

            if (bds[4] < bound[4]) bound[4] = bds[4];
            if (bds[5] > bound[5]) bound[5] = bds[5];
        }

        for (int i = 0; i < 6; i++) {
            boundValue[i] = bound[i];
        }
    }

    void FCGraph3DClipDialog::updateValue()
    {
        if (_graph3DWidgetPlane == nullptr || _graph3DWindow == nullptr) {
            return;
        }

        double origin[3] = { 0,0,0 }, normal[3] = { 0,0,0 };
        origin[0] = _ui->lineEdit_OriginX->text().toDouble();
        origin[1] = _ui->lineEdit_OriginY->text().toDouble();
        origin[2] = _ui->lineEdit_OriginZ->text().toDouble();
        normal[0] = _ui->lineEdit_NormalX->text().toDouble();
        normal[1] = _ui->lineEdit_NormalY->text().toDouble();
        normal[2] = _ui->lineEdit_NormalZ->text().toDouble();
        _graph3DWidgetPlane->setValue(origin, normal);
        _graph3DWindow->reRender();
    }

    void FCGraph3DClipDialog::startClipInOldModel()
    {
        if (_graph3DWindow == nullptr) {
            return;
        }

        //还原原状态
        stopClipInOldModel();

        //获取当前裁切类型
        ClipType type = _ui->comboBox_Type->currentData().value<ClipType>();
        ClipInside insideType = _ui->comboBox_Inside->currentData().value<ClipInside>();
        if (type == ClipType::NoneType || insideType == ClipInside::None) {
            return;
        }

        double origin[3] = { 0,0,0 }, normal[3] = { 0,0,0 };
        origin[0] = _ui->lineEdit_OriginX->text().toDouble();
        origin[1] = _ui->lineEdit_OriginY->text().toDouble();
        origin[2] = _ui->lineEdit_OriginZ->text().toDouble();
        normal[0] = _ui->lineEdit_NormalX->text().toDouble();
        normal[1] = _ui->lineEdit_NormalY->text().toDouble();
        normal[2] = _ui->lineEdit_NormalZ->text().toDouble();

        //获取所有演员的数据
        QList<FITKActorClipTool*> actors = {};
        for (FCGraphObjectVTK* obj : _graph3DWindow->getAllGraphObj()) {
            if (obj == nullptr) {
                continue;
            }
            int vtkObjCount = obj->getActorCount();
            for (int j = 0; j < vtkObjCount; j++) {
                FITKActorClipTool* actor = dynamic_cast<FITKActorClipTool*>(obj->getActor(j));
                if (actor == nullptr) {
                    continue;
                }
                vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
                plane->SetOrigin(origin);
                plane->SetNormal(normal);
                actor->setClipType(type);
                actor->setClipInside(insideType);
                actor->setClipImplicitFunction(plane);
            }
        }

        _graph3DWindow->reRender();
    }
    
    void FCGraph3DClipDialog::startClipCreateNewModel()
    {
        if (_graph3DWindow == nullptr) {
            return;
        }

        //还原原状态
        stopClipCreateNewModel();

        //获取当前裁切类型
        ClipType type = _ui->comboBox_Type->currentData().value<ClipType>();
        ClipInside insideType = _ui->comboBox_Inside->currentData().value<ClipInside>();
        if (type == ClipType::NoneType || insideType == ClipInside::None) {
            return;
        }

        double origin[3] = { 0,0,0 }, normal[3] = { 0,0,0 };
        origin[0] = _ui->lineEdit_OriginX->text().toDouble();
        origin[1] = _ui->lineEdit_OriginY->text().toDouble();
        origin[2] = _ui->lineEdit_OriginZ->text().toDouble();
        normal[0] = _ui->lineEdit_NormalX->text().toDouble();
        normal[1] = _ui->lineEdit_NormalY->text().toDouble();
        normal[2] = _ui->lineEdit_NormalZ->text().toDouble();

        _actionPro.clear();
        if (_clipObj) {
            delete _clipObj;
            _clipObj = nullptr;
        }
        _clipObj = new FCGraphObjectVTK();

        //获取所有演员的数据
        for (FCGraphObjectVTK* obj : _graph3DWindow->getAllGraphObj()) {
            if (obj == nullptr) {
                continue;
            }
            int vtkObjCount = obj->getActorCount();
            for (int j = 0; j < vtkObjCount; j++) {
                vtkActor* FCactor = dynamic_cast<vtkActor*>(obj->getActor(j));
                if (FCactor == nullptr || FCactor->GetVisibility() == false) {
                    continue;
                }
                _actionPro.insert(FCactor, FCactor->GetVisibility());
                FCactor->SetVisibility(false);

                vtkMapper* FCmapper = FCactor->GetMapper();
                if (FCmapper == nullptr) {
                    continue;
                }

                vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
                plane->SetNormal(normal);
                plane->SetOrigin(origin);

                vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();

                switch (type) {
                case Clip: {
                    vtkSmartPointer<vtkTableBasedClipDataSet> clipAlg = vtkSmartPointer<vtkTableBasedClipDataSet>::New();
                    clipAlg->SetInputData(FCmapper->GetInputDataObject(0, 0));
                    clipAlg->SetClipFunction(plane);
                    //设置裁切正、反面
                    switch (insideType) {
                    case ClipInside::Off: clipAlg->InsideOutOff(); break;
                    case ClipInside::On: clipAlg->InsideOutOn(); break;
                    }

                    mapper->SetInputConnection(clipAlg->GetOutputPort());
                    break;
                }
                case ExtractGeometry: {
                    vtkSmartPointer<vtkExtractGeometry> extractGeometry = vtkSmartPointer<vtkExtractGeometry>::New();
                    extractGeometry->SetImplicitFunction(plane);
                    switch (insideType) {
                    case ClipInside::Off:extractGeometry->ExtractInsideOff(); break;
                    case ClipInside::On: extractGeometry->ExtractInsideOn(); break;
                    }
                    extractGeometry->ExtractBoundaryCellsOn();
                    extractGeometry->SetInputDataObject(FCmapper->GetInputDataObject(0, 0));
                    mapper->SetInputConnection(extractGeometry->GetOutputPort());
                    break;
                }
                default: break;
                }

                vtkActor* actor = vtkActor::New();
                actor->SetMapper(mapper);
                actor->GetProperty()->SetEdgeVisibility(true);
                actor->GetProperty()->SetRepresentation(VTK_SURFACE);
                actor->SetPickable(false);
                _clipObj->addActor(actor);
            }
        }
        _graph3DWindow->addObject(0, _clipObj);
        _graph3DWindow->reRender();
    }


    void FCGraph3DClipDialog::stopClipInOldModel()
    {
        if (_graph3DWindow == nullptr) {
            return;
        }

        //获取所有演员的数据
        QList<FITKActorClipTool*> actors = {};
        for (FCGraphObjectVTK* obj : _graph3DWindow->getAllGraphObj()) {
            if (obj == nullptr) {
                continue;
            }
            int vtkObjCount = obj->getActorCount();
            for (int j = 0; j < vtkObjCount; j++) {
                FITKActorClipTool* actor = dynamic_cast<FITKActorClipTool*>(obj->getActor(j));
                if (actor == nullptr) {
                    continue;
                }
                actor->setClipType(NoneType);
            }
        }

        _graph3DWindow->reRender();
    }

    void FCGraph3DClipDialog::stopClipCreateNewModel()
    {
        if (_graph3DWindow == nullptr) {
            return;
        }

        //恢复原数据可见性
        for (int i = 0; i < _actionPro.size(); i++) {
            vtkActor* actor = _actionPro.keys()[i];
            bool visibility = _actionPro.values()[i];
            if (actor == nullptr) {
                continue;
            }
            actor->SetVisibility(visibility);
        }

        //清空当前数据
        if (_clipObj) {
            delete _clipObj;
            _clipObj = nullptr;
        }
        _actionPro.clear();

        //渲染
        _graph3DWindow->reRender();
    }


    void FCGraph3DClipDialog::on_lineEdit_OriginX_editingFinished()
    {
        updateValue();
    }

    void FCGraph3DClipDialog::on_lineEdit_OriginY_editingFinished()
    {
        updateValue();
    }

    void FCGraph3DClipDialog::on_lineEdit_OriginZ_editingFinished()
    {
        updateValue();
    }

    void FCGraph3DClipDialog::on_lineEdit_NormalX_editingFinished()
    {
        updateValue();
    }

    void FCGraph3DClipDialog::on_lineEdit_NormalY_editingFinished()
    {
        updateValue();
    }

    void FCGraph3DClipDialog::on_lineEdit_NormalZ_editingFinished()
    {
        updateValue();
    }

    void FCGraph3DClipDialog::on_pushButton_Apply_clicked()
    {
        if (_graph3DWindow == nullptr) {
            return;
        }

        if (_clipCreateNewModel == true) {
            startClipCreateNewModel();
        }
        else {
            startClipInOldModel();
        }
    }

    void FCGraph3DClipDialog::on_checkBox_PlaneWidget_clicked(bool checked)
    {
        if (_graph3DWidgetPlane == nullptr || _graph3DWindow == nullptr) {
            return;
        }
        _graph3DWidgetPlane->setIsShow(checked);
        _graph3DWindow->reRender();
    }

    void FCGraph3DClipDialog::slot_ValueChange(double * origin, double * normal)
    {
        _ui->lineEdit_OriginX->setText(QString::number(origin[0]));
        _ui->lineEdit_OriginY->setText(QString::number(origin[1]));
        _ui->lineEdit_OriginZ->setText(QString::number(origin[2]));
        _ui->lineEdit_NormalX->setText(QString::number(normal[0]));
        _ui->lineEdit_NormalY->setText(QString::number(normal[1]));
        _ui->lineEdit_NormalZ->setText(QString::number(normal[2]));
    }
}
