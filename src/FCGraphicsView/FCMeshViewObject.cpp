/**
 * @file FCMeshViewObject.cpp
 * @brief 网格的显示层对象
 * @date 2025-12-11
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshViewObject.h"
#include "FCMeshData.h"
#include "FCMeshKernal.h"
//vtk
#include <vtkUnstructuredGrid.h>
#include <vtkActor.h>
#include <vtkUnsignedCharArray.h>
#include <vtkUnsignedIntArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkAppendFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkDoubleArray.h>
#include <QThread>

namespace FC 
{
	FCMeshViewObject::FCMeshViewObject(IdType kid)
		: mMeshID(kid), mDisplayData(vtkUnstructuredGrid::New()),
		  mMeshData(FCMeshData::getInstance())
	{
		mActor[0] = vtkActor::New();
		mActor[1] = vtkActor::New();
		mActor[2] = vtkActor::New();
		this->generateIDProp();
		this->init();
	}

	FCMeshViewObject::~FCMeshViewObject()
	{
		//		if (_actor != nullptr) _actor->Delete();
		if (mDisplayData != nullptr)
			mDisplayData->Delete();
	}

	vtkDataSet *FCMeshViewObject::getDisplayData()
	{
		return mDisplayData;
	}

	vtkActor **FCMeshViewObject::getActor()
	{
		return mActor;
	}

	void FCMeshViewObject::setPointColor(const QColor &c, bool disOnly)
	{
		vtkDataArray *dpointColor = mDisplayData->GetPointData()->GetScalars();
		double col[3]{c.red(), c.green(), c.blue()};
		if (nullptr == dpointColor)
		{
			dpointColor = vtkUnsignedCharArray::New();
			dpointColor->SetNumberOfComponents(3);
			mDisplayData->GetPointData()->SetScalars(dpointColor);
		}
		dpointColor->SetNumberOfTuples(mDisplayData->GetNumberOfPoints());
		dpointColor->FillComponent(0, col[0]);
		dpointColor->FillComponent(1, col[1]);
		dpointColor->FillComponent(2, col[2]);
		mDisplayData->Modified();

		if (disOnly)
			return;
        auto dataset = mMeshData->getMeshKernalByID(mMeshID)->getMeshData();//  mMeshKernal->getMeshData();
		vtkDataArray *pointColor = dataset->GetPointData()->GetScalars();
		if (nullptr == pointColor)
		{
			pointColor = vtkUnsignedCharArray::New();
			pointColor->SetNumberOfComponents(3);
			pointColor->SetNumberOfTuples(dataset->GetNumberOfPoints());
			dataset->GetPointData()->SetScalars(pointColor);
		}
		pointColor->FillComponent(0, col[0]);
		pointColor->FillComponent(1, col[1]);
		pointColor->FillComponent(2, col[2]);
	}

	void FCMeshViewObject::setPointDisplayColor(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = mDisplayData->GetPointData()->GetScalars();
		vtkDataArray *indexArray = mDisplayData->GetPointData()->GetArray("IDS");
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		double col[3]{color.red(), color.green(), color.blue()};
		const int nPoint = indexArray->GetNumberOfTuples();
		for (int i = 0; i < nPoint; ++i)
		{
			if (indexs.isEmpty())
				break;
			int pointindex = indexArray->GetComponent(i, 1);
			if (indexs.contains(pointindex))
			{
				colorArray->SetComponent(i, 0, col[0]);
				colorArray->SetComponent(i, 1, col[1]);
				colorArray->SetComponent(i, 2, col[2]);
				indexs.removeOne(pointindex);
			}
		}
		mDisplayData->Modified();
	}

	void FCMeshViewObject::setCellColor(const QColor &c, bool disOnly)
	{
		double col[3]{c.red(), c.green(), c.blue()};
		vtkDataArray *dcellcolor = mDisplayData->GetCellData()->GetScalars();
		if (dcellcolor == nullptr)
		{
			dcellcolor = vtkUnsignedCharArray::New();
			dcellcolor->SetNumberOfComponents(3);
			mDisplayData->GetCellData()->SetScalars(dcellcolor);
		}

		dcellcolor->SetNumberOfTuples(mDisplayData->GetNumberOfCells());
		dcellcolor->FillComponent(0, col[0]);
		dcellcolor->FillComponent(1, col[1]);
		dcellcolor->FillComponent(2, col[2]);
		mDisplayData->Modified();

		if (disOnly)
			return;
		auto dataset = mMeshData->getMeshKernalByID(mMeshID)->getMeshData();//mMeshKernal->getMeshData();
		vtkDataArray *cellcolor = dataset->GetCellData()->GetScalars();
		if (nullptr == cellcolor)
		{
			cellcolor = vtkUnsignedCharArray::New();
			cellcolor->SetNumberOfComponents(3);
			dataset->GetCellData()->SetScalars(cellcolor);
			cellcolor->SetNumberOfTuples(dataset->GetNumberOfCells());
		}
		cellcolor->FillComponent(0, col[0]);
		cellcolor->FillComponent(1, col[1]);
		cellcolor->FillComponent(2, col[2]);
	}

	void FCMeshViewObject::setCellDisplayColor(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = mDisplayData->GetCellData()->GetScalars();
		vtkDataArray *indexArray = mDisplayData->GetCellData()->GetArray("IDS");
		double col[3]{color.red(), color.green(), color.blue()};
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		const int nCell = indexArray->GetNumberOfTuples();

		int nprocess = 1;


		QList<int> spliters{0};
		const int countPart = nCell / nprocess;
		while (spliters.last() < nCell - 1)
		{
			int cu = spliters.last() + countPart;
			if (abs(cu - nCell) < 0.2 * countPart)
				cu = nCell - 1;
			spliters.append(cu);
		}

		auto serial = [=](int beg, int end)
		{
			for (int i = beg; i <= end; ++i)
			{
				int cellid = indexArray->GetComponent(i, 1);
				if (indexs.contains(cellid))
				{
					colorArray->SetComponent(i, 0, col[0]);
					colorArray->SetComponent(i, 1, col[1]);
					colorArray->SetComponent(i, 2, col[2]);
				}
			}
		};

		for (int i = 0; i < nprocess; ++i)
		{
			int beg = spliters[i];
			int end = spliters[i + 1];
			serial(beg, end);
		}

		mDisplayData->Modified();
	}

	void FCMeshViewObject::setPointDisplayColorByDisplayIndex(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = mDisplayData->GetPointData()->GetScalars();
		vtkDataArray *indexArray = mDisplayData->GetPointData()->GetArray("IDS");
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		double col[3]{color.red(), color.green(), color.blue()};
		for (int index : indexs)
		{
			colorArray->SetComponent(index, 0, col[0]);
			colorArray->SetComponent(index, 1, col[1]);
			colorArray->SetComponent(index, 2, col[2]);
		}
		mDisplayData->Modified();
	}

	void FCMeshViewObject::setCellDisplayColorByDisplayIndex(QList<int> &indexs, const QColor &color)
	{
		vtkDataArray *colorArray = mDisplayData->GetCellData()->GetScalars();
		vtkDataArray *indexArray = mDisplayData->GetCellData()->GetArray("IDS");
		if (nullptr == colorArray || nullptr == indexArray)
			return;
		double col[3]{color.red(), color.green(), color.blue()};
		for (int index : indexs)
		{
			colorArray->SetComponent(index, 0, col[0]);
			colorArray->SetComponent(index, 1, col[1]);
			colorArray->SetComponent(index, 2, col[2]);
		}
		mDisplayData->Modified();
	}

	void FCMeshViewObject::showCells(const QList<int> &indexs, bool show)
	{
		auto dataSet = mMeshData->getMeshKernalByID(mMeshID)->getMeshData();//mMeshKernal->getMeshData();
		vtkDataArray *showArray = dataSet->GetCellData()->GetArray("SHOW");
		if (showArray == nullptr)
			return;
		int value = 0;
		if (show)
			value = 1;
		for (int index : indexs)
			showArray->SetComponent(index, 0, value);

		this->updateDisplayMember();
	}

	void FCMeshViewObject::highLight()
	{
		// auto gp = Setting::BusAPI::instance()->getGraphOption();
        QColor color = QColor(0, 30, 254);// gp->getHighLightColor();
		mActor[POINTACTOR]->GetMapper()->SetScalarVisibility(false);
		mActor[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
		mActor[FACEACTOR]->GetMapper()->SetScalarVisibility(false);

		mActor[POINTACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());
		mActor[EDGEACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());
		mActor[FACEACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());

		mIsKernalHighLight = true;
	}

	void FCMeshViewObject::clearHighLight()
	{
		// auto gp = Setting::BusAPI::instance()->getGraphOption();
		// QColor color = gp->getMeshEdgeColor();
		// _actor[POINTACTOR]->GetMapper()->SetScalarVisibility(true);
		// _actor[EDGEACTOR]->GetMapper()->SetScalarVisibility(true);
		// _actor[FACEACTOR]->GetMapper()->SetScalarVisibility(true);
		// if (gp->isShowMeshEdge() && gp->isShowMeshFace())
		// {
		// 	_actor[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
		// 	_actor[EDGEACTOR]->GetProperty()->SetColor(color.red(), color.green(), color.blue());
		// }

		// _isKernalHighLight = false;
	}

	bool FCMeshViewObject::isKernalHighLight()
	{
		return mIsKernalHighLight;
	}
    
    /**
	 * @brief FCMeshViewObject::generateIDProp
	 */
	void FCMeshViewObject::generateIDProp()
	{
        auto dataset = mMeshData->getMeshKernalByID(mMeshID)->getMeshData();// mMeshKernal->getMeshData();
        const int id = mMeshID;// mMeshKernal->getID();
		// cell ID与显示隐藏状态
		vtkSmartPointer<vtkUnsignedIntArray> kcellid_index = vtkSmartPointer<vtkUnsignedIntArray>::New();
		kcellid_index->SetNumberOfComponents(2);
		kcellid_index->SetName("IDS");
		const int ncell = dataset->GetNumberOfCells();
		for (int i = 0; i < ncell; ++i)
			kcellid_index->InsertNextTuple2(id, i);
		dataset->GetCellData()->AddArray(kcellid_index);

		vtkSmartPointer<vtkUnsignedIntArray> cstatesArray = vtkSmartPointer<vtkUnsignedIntArray>::New();
		cstatesArray->SetName("SHOW");
		cstatesArray->SetNumberOfValues(ncell);
		cstatesArray->Fill(1);
		dataset->GetCellData()->AddArray(cstatesArray);

		// point ID与显示隐藏状态
		vtkSmartPointer<vtkUnsignedIntArray> kpointid_index = vtkSmartPointer<vtkUnsignedIntArray>::New();
		kpointid_index->SetNumberOfComponents(2);
		kpointid_index->SetName("IDS");
		const int npoint = dataset->GetNumberOfPoints();
		for (int i = 0; i < npoint; ++i)
			kpointid_index->InsertNextTuple2(id, i);
		dataset->GetPointData()->AddArray(kpointid_index);

		vtkSmartPointer<vtkUnsignedIntArray> pstatesArray = vtkSmartPointer<vtkUnsignedIntArray>::New();
		pstatesArray->SetName("SHOW");
		pstatesArray->SetNumberOfValues(npoint);
		pstatesArray->Fill(1);
		dataset->GetPointData()->AddArray(pstatesArray);
	}
    
    /**
	 * @brief 初始化点，线， 面actor
	 */
	void FCMeshViewObject::init()
	{
		vtkSmartPointer<vtkAppendFilter> filter = vtkSmartPointer<vtkAppendFilter>::New();
        FCMeshKernal* meshKernal = mMeshData->getMeshKernalByID(mMeshID);
		filter->AddInputData(meshKernal->getMeshData());
		filter->Update();
		mDisplayData->DeepCopy(filter->GetOutput());
        
        
        setCellColor(QColor(0, 30, 254));
		setPointColor(QColor(0, 30, 254));

		vtkSmartPointer<vtkDataSetMapper> pointMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		pointMapper->SetInputData(mDisplayData);
		pointMapper->SetScalarModeToUsePointData();
		mActor[POINTACTOR]->SetMapper(pointMapper);
		mActor[POINTACTOR]->GetProperty()->SetRepresentationToPoints();

		vtkSmartPointer<vtkDataSetMapper> edgeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		edgeMapper->SetInputData(mDisplayData);
		edgeMapper->SetScalarModeToUseCellData();
		mActor[EDGEACTOR]->SetMapper(edgeMapper);
		mActor[EDGEACTOR]->GetProperty()->SetRepresentationToWireframe();

		vtkSmartPointer<vtkDataSetMapper> faceMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		faceMapper->SetInputData(mDisplayData);
		faceMapper->SetScalarModeToUseCellData();
		mActor[FACEACTOR]->SetMapper(faceMapper);
		mActor[FACEACTOR]->GetProperty()->SetRepresentationToSurface();
	}

	void FCMeshViewObject::updateDisplayMember()
	{
		auto dataset = mMeshData->getMeshKernalByID(mMeshID)->getMeshData();// mMeshKernal->getMeshData();
		vtkDataArray *array = dataset->GetCellData()->GetArray("SHOW");
		if (array == nullptr)
			return;

		vtkSmartPointer<vtkIdTypeArray> idArray = vtkSmartPointer<vtkIdTypeArray>::New();
		const int n = array->GetNumberOfTuples();
		for (int i = 0; i < n; ++i)
		{
			double v = fabs(array->GetComponent(i, 0));
			if (v > 0.5)
				idArray->InsertNextValue(i);
		}
		vtkSmartPointer<vtkSelectionNode> selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(idArray);
		vtkSmartPointer<vtkSelection> selection = vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		vtkSmartPointer<vtkExtractSelection> extractionSelection = vtkSmartPointer<vtkExtractSelection>::New();
		extractionSelection->SetInputData(0, dataset);
		extractionSelection->SetInputData(1, selection);
		extractionSelection->Update();

		mDisplayData->DeepCopy(extractionSelection->GetOutput());
		mDisplayData->Modified();
	}
} // namespace FC
