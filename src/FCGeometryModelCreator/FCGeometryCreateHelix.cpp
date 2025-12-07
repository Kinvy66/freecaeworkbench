/**
 * @file FCGeometryCreateHelix.cpp
 * @brief 创建螺旋
 * @date 2025-12-04
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryCreateHelix.h"

#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS_Wire.hxx>

#include "FCUniqueIDGenerater.h"
#include "FCGeometrySet.h"
#include "FCGeometryParaHelix.h"

#include <QDebug>

namespace FC 
{

FCGeometryCreateHelix::FCGeometryCreateHelix(QObject *parent)
    : FCGeometryModelBase(parent)
{
    mLocation[0] = mLocation[1] = mLocation[2] = 0.0;
    mNumberOfTurns = 1;
    mMajorRadius = 10.0;
    mMinorRadius = 1.0;
    mRadialPitch = 0.0;
    mAxialPitch = 5.0;
    mChirality = 1;     // 1=右手螺旋，-1=左手螺旋
}

bool FCGeometryCreateHelix::execute()
{
    const int pointCount = mNumberOfTurns * 50;   // 分段数，可调
    const double twoPi = 2.0 * M_PI;
    const double totalAngle = twoPi * mNumberOfTurns;

    TColgp_Array1OfPnt points(1, pointCount + 1);

    for (int i = 0; i <= pointCount; ++i) {
        double t = (double)i / pointCount * totalAngle;

        // 左手 / 右手旋转方向
        double tt = (mChirality > 0) ? t : -t;

        // 半径随 t 的线性变化 (RadialPitch)
        double radius = mMajorRadius + (mRadialPitch / totalAngle) * t;

        double x = radius * cos(tt);
        double y = radius * sin(tt);
        double z = (mAxialPitch / twoPi) * t;

        points(i + 1) = gp_Pnt(
            x + mLocation[0],
            y + mLocation[1],
            z + mLocation[2]
        );
    }

    // 使用 BSpline 曲线拟合
    GeomAPI_PointsToBSpline bspline(points);
    Handle(Geom_BSplineCurve) curve = bspline.Curve();

    // 转成 Edge → Wire → Shape
    BRepBuilderAPI_MakeEdge mkEdge(curve);
    if (!mkEdge.IsDone()) {
        qDebug() << "Helix create edge failed!";
        return false;
    }

    TopoDS_Edge edge = mkEdge.Edge();
    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge);

    TopoDS_Shape* shape = new TopoDS_Shape;
    *shape = wire;

    if (shape->IsNull()) {
        delete shape;
        qDebug() << "Helix shape is null!";
        return false;
    }

    // 创建 FCGeometrySet
    FCGeometrySet* set = new FCGeometrySet(STEP);
    set->setName(mName);
    set->setShape(shape);
    mResult = set;

    IdType id = 0;
    if (mIsEdit) {
        id = mEditSetID;
        mGeoData->replaceSet(id, set);
        emit updateDisplayGeometryActor(id);
    } else {
        id = FCUniqueIDGenerater::id_uint64();
        mGeoData->appendGeometrySet(id, set);
    }

    // 参数保存
    FCGeometryParaHelix* para = new FCGeometryParaHelix;
    para->setName(mName);
    para->setLocation(mLocation);
    para->setNumberOfTurns(mNumberOfTurns);
    para->setMajorRadius(mMajorRadius);
    para->setMinorRadius(mMinorRadius);
    para->setRadialPitch(mRadialPitch);
    para->setAxialPitch(mAxialPitch);
    para->setChirality(static_cast<FCGeometryParaHelix::Chirality>(mChirality));

    mResult->setParameter(para);

    emit showSet(id);
    emit updateGeoTree(id, mName);

    qDebug() << "Create Helix:"
             << " name:" << mName
             << " turns:" << mNumberOfTurns
             << " R_major:" << mMajorRadius
             << " R_minor:" << mMinorRadius
             << " radialPitch:" << mRadialPitch
             << " axialPitch:" << mAxialPitch
             << " chirality:" << mChirality
             << " location:" << mLocation[0] << mLocation[1] << mLocation[2];

    return true;
}

void FCGeometryCreateHelix::undo()
{
}

void FCGeometryCreateHelix::redo()
{
}

void FCGeometryCreateHelix::releaseResult()
{
    if (mResult != nullptr)
        delete mResult;
    mResult = nullptr;
}

void FCGeometryCreateHelix::setName(QString name)
{
    mName = name;
}

void FCGeometryCreateHelix::setLocation(double* loc)
{
    mLocation[0] = loc[0];
    mLocation[1] = loc[1];
    mLocation[2] = loc[2];
}

void FCGeometryCreateHelix::setNumberOfTurns(int n)
{
    mNumberOfTurns = n;
}

void FCGeometryCreateHelix::setMajorRadius(double r)
{
    mMajorRadius = r;
}

void FCGeometryCreateHelix::setMinorRadius(double r)
{
    mMinorRadius = r;
}

void FCGeometryCreateHelix::setRadialPitch(double r)
{
    mRadialPitch = r;
}

void FCGeometryCreateHelix::setAxialPitch(double r)
{
    mAxialPitch = r;
}

void FCGeometryCreateHelix::setChirality(int c)
{
    mChirality = c;
}

} // namespace FC
