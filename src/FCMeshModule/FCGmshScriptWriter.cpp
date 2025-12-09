/**
 * @file FCGmshScriptWriter.cpp
 * @brief Gmsh参数文件（geo）写出
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGmshScriptWriter.h"
#include "FCGeometryData.h"
#include "FCGeometrySet.h"
#include <QFile>
#include <QSet>
#include <QDebug>
#include <QString>
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRep_Builder.hxx>


namespace FC 
{

FCGmshScriptWriter::FCGmshScriptWriter()
{
    
}

FCGmshScriptWriter::~FCGmshScriptWriter()
{
    
}

void FCGmshScriptWriter::writeGmshScript(QString dir)
{
    QString path = dir + "gmsh.Geo";
    QString geo = dir + "geometry.brep";
    
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << path << "open failed.";
        return;
    }
    QTextStream out(&file);
    
    out << QString("Merge \"%1\";").arg(geo) << Qt::endl;
    
    writeGeneralSetting(&out);
    
    out << "//+" << Qt::endl;
    out << "SetFactory(\"OpenCASCADE\");" << Qt::endl;
    
    writeSizeAtPoints(&out);
    writeSizeFields(&out);
    // physicalsGroup(&out);
    writeGridCoplanar(&out);
    
    file.close();
}

void FCGmshScriptWriter::writeGeneralSetting(QTextStream *out)
{
    *out << QString("Geometry.OCCFixDegenerated = %1;").arg(_geoclean) << Qt::endl;
    *out << QString("Geometry.OCCFixSmallEdges = %1;").arg(_geoclean) << Qt::endl;
    *out << QString("Geometry.OCCFixSmallFaces = %1;").arg(_geoclean) << Qt::endl;
    *out << QString("Geometry.OCCSewFaces = %1;").arg(_geoclean) << Qt::endl;
    
    *out << QString("Mesh.Algorithm = %1;").arg(_method) << Qt::endl;
    *out << QString("Mesh.Algorithm3D = %1;").arg(_method) << Qt::endl;
    *out << QString("Mesh.CharacteristicLengthFactor = %1;").arg(_sizeFactor) << Qt::endl;
    *out << QString("Mesh.CharacteristicLengthMin = %1;").arg(_minSize) << Qt::endl;
    *out << QString("Mesh.CharacteristicLengthMax = %1;").arg(_maxSize) << Qt::endl;
    *out << QString("Mesh.ElementOrder = %1;").arg(_elementOrder) << Qt::endl;
    *out << QString("Mesh.RecombineAll = %1;").arg(_elementType) << Qt::endl;
    *out << QString("Mesh.Smoothing = %1;").arg(_smoothIteration) << Qt::endl;
    *out << QString("Mesh.SubdivisionAlgorithm = %1;").arg(_elementType) << Qt::endl;
}

void FCGmshScriptWriter::writeGridCoplanar(QTextStream *out)
{
    if (!_isGridCoplanar)
        return;
    
    // 		if (_surfaceHash.size() != 0 || _solidHash.size() != 0)
    // 		{
    // 			QString script = getGridCoplanarScript().join("; ");
    // 			*out << "//+" << Qt::endl;
    // 			*out << "BooleanFragments{ " << script << "; Delete; }{ }" << Qt::endl;
    // 		}
    *out << "//+" << Qt::endl;
    *out << "Coherence;" << Qt::endl;
}

void FCGmshScriptWriter::writeSizeAtPoints(QTextStream *out)
{
    if (_sizeAtPoints.isEmpty())
        return;
    
    int d = 100000;
    
    QStringList points = _sizeAtPoints.split(";");
    for (QString s : points)
    {
        QStringList coors = s.split(",");
        if (coors.size() != 4)
            continue;
        
        bool ok = false;
        for (QString c : coors)
        {
            c.toDouble(&ok);
            if (!ok)
                break;
        }
        
        if (ok)
        {
            *out << "//+" << Qt::endl;
            QString temp = QString("Point(%1) = {").arg(d);
            *out << temp << coors.join(",") << "};" << Qt::endl;
            d++;
        }
    }
}

void FCGmshScriptWriter::writeSizeFields(QTextStream *out)
{
    if (_sizeFields.isEmpty())
        return;
    QStringList solids{};
    QStringList slist = _sizeFields.split(";");
    int index = 1;
    for (QString s : slist)
    {
        QStringList field = s.split(",");
        
        if (field.size() <= 0)
            continue;
        
        bool ok = false;
        int t = field.at(0).toInt(&ok);
        if (!ok)
            continue;
        
        switch (t)
        {
        case 1:
            writeBoxFieldScript(out, field, index);
            break;
        case 2:
            writeBallFieldScript(out, field, index);
            break;
        case 3:
            writeCylinderFieldScript(out, field, index);
            break;
        case 4:
            solids.append(s);
            break;
        case 5:
            writeSolidFrustumScript(out, field, index);
        default:
            break;
        }
    }
    
    if (solids.size() > 0)
        writeSolidsFieldScript(out, solids, index);
}

void FCGmshScriptWriter::writeBoxFieldScript(QTextStream *out, QStringList list, int &index)
{
    const int n = list.size();
    if (n != 11)
        return;
    
    double val[9] = {0};
    bool ok = false;
    for (int i = 1; i < 10; i++)
    {
        double v = list.at(i).toDouble(&ok);
        if (!ok)
            return;
        val[i - 1] = v;
    }
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Box;").arg(index) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Thickness = %2;").arg(index).arg(val[0]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VIn = %2;").arg(index).arg(val[1]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VOut = %2;").arg(index).arg(val[2]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XMax = %2;").arg(index).arg(val[3] + val[6]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XMin = %2;").arg(index).arg(val[3]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YMax = %2;").arg(index).arg(val[4] + val[7]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YMin = %2;").arg(index).arg(val[4]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZMax = %2;").arg(index).arg(val[5] + val[8]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZMin = %2;").arg(index).arg(val[5]) << Qt::endl;
    if (list.at(10).toInt() == 1)
        *out << "//+" << Qt::endl
             << QString("Background Field = %1;").arg(index) << Qt::endl;
    
    index++;
}

void FCGmshScriptWriter::writeBallFieldScript(QTextStream *out, QStringList list, int &index)
{
    const int n = list.size();
    if (n != 9)
        return;
    
    double val[7] = {0};
    bool ok = false;
    for (int i = 1; i < 8; i++)
    {
        double v = list.at(i).toDouble(&ok);
        if (!ok)
            return;
        val[i - 1] = v;
    }
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Ball;").arg(index) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Radius = %2;").arg(index).arg(val[0]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Thickness = %2;").arg(index).arg(val[1]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VIn = %2;").arg(index).arg(val[2]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VOut = %2;").arg(index).arg(val[3]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XCenter = %2;").arg(index).arg(val[4]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YCenter = %2;").arg(index).arg(val[5]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZCenter = %2;").arg(index).arg(val[6]) << Qt::endl;
    
    if (list.at(8).toInt() == 1)
        *out << "//+" << Qt::endl
             << QString("Background Field = %1;").arg(index) << Qt::endl;
    
    index++;
}

void FCGmshScriptWriter::writeCylinderFieldScript(QTextStream *out, QStringList list, int &index)
{
    const int n = list.size();
    if (n != 12)
        return;
    
    double val[10] = {0};
    bool ok = false;
    for (int i = 1; i < 11; i++)
    {
        double v = list.at(i).toDouble(&ok);
        if (!ok)
            return;
        val[i - 1] = v;
    }
    
    double xa = val[5];
    double ya = val[6];
    double za = val[7];
    
    int num = 0;
    if (xa != 0)
        num++;
    if (ya != 0)
        num++;
    if (za != 0)
        num++;
    
    if (num == 1)
    {
        if (xa == 1)
        {
            val[5] = val[1] / 2;
            val[2] += val[1] / 2;
        }
        else if (ya == 1)
        {
            val[6] = val[1] / 2;
            val[3] += val[1] / 2;
        }
        else if (za == 1)
        {
            val[7] = val[1] / 2;
            val[4] += val[1] / 2;
        }
    }
    
    if (num > 1)
    {
        double v = val[1] / 2 / sqrt(num);
        val[5] = xa * v;
        val[6] = ya * v;
        val[7] = za * v;
        
        double xyz = (xa * xa) + (ya * ya) + (za * za);
        if (xyz > 0)
        {
            double ofs = val[1] / 2 / sqrt(xyz);
            
            val[2] += ofs * xa;
            val[3] += ofs * ya;
            val[4] += ofs * za;
        }
    }
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Cylinder;").arg(index) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Radius = %2;").arg(index).arg(val[0]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VIn = %2;").arg(index).arg(val[8]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VOut = %2;").arg(index).arg(val[9]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XAxis = %2;").arg(index).arg(val[5]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XCenter = %2;").arg(index).arg(val[2]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YAxis = %2;").arg(index).arg(val[6]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YCenter = %2;").arg(index).arg(val[3]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZAxis = %2;").arg(index).arg(val[7]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZCenter = %2;").arg(index).arg(val[4]) << Qt::endl;
    
    if (list.at(11).toInt() == 1)
        *out << "//+" << Qt::endl
             << QString("Background Field = %1;").arg(index) << Qt::endl;
    
    index++;
}

void FCGmshScriptWriter::writeSolidsFieldScript(QTextStream *out, QStringList list, int &index)
{
    QMultiHash<int, int> solidHash;
    double val[3] = {0};
    bool back{false};
    
    for (QString s : list)
    {
        QStringList solid = s.split(",");
        const int n = solid.size();
        if (n != 7)
            return;
        
        bool ok = false;
        val[0] = solid.at(1).toDouble(&ok);
        if (!ok)
            continue;
        val[1] = solid.at(2).toDouble(&ok);
        if (!ok)
            continue;
        val[2] = solid.at(3).toDouble(&ok);
        if (!ok)
            continue;
        int setid = solid.at(4).toDouble(&ok);
        if (!ok)
            continue;
        int sindex = solid.at(5).toDouble(&ok);
        if (!ok)
            continue;
        
        solidHash.insert(setid, sindex);
        
        if (solid.at(6).toInt() == 1)
            back = true;
    }
    
    writeSolidFieldScript(out, index, solidHash, val, back);
}

void FCGmshScriptWriter::writeSolidFieldScript(QTextStream *out,
                                               int &index,
                                               QMultiHash<int, int> solidHash,
                                               double *val, bool back)
{
    if (solidHash.size() < 1)
        return;
    
    QList<double> banBox = getSolidBndBox(solidHash);
    if (banBox.size() != 6)
        return;
    QList<int> curve = getShapeIndexListInSolid(solidHash, 2);
    QList<int> surface = getShapeIndexListInSolid(solidHash, 3);
    QList<int> solid = getShapeIndexListInSolid(solidHash, 4);
    
    // QSet<int> curves = QSet<int>::fromList(curve);//.toSet();
    // QSet<int> surfaces = surface.toSet();
    // QSet<int> solids = solid.toSet();
    QSet<int> curves(curve.begin(), curve.end());
    QSet<int> surfaces(surface.begin(), surface.end());
    QSet<int> solids(solid.begin(), solid.end());
    
    QStringList elist, flist, rlist;
    for (int c : curves)
    {
        elist.append(QString::number(c));
    }
    
    for (int s : surfaces)
    {
        flist.append(QString::number(s));
    }
    
    for (int s : solids)
    {
        rlist.append(QString::number(s));
    }
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Box;").arg(index) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Thickness = %2;").arg(index).arg(val[2]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VIn = %2;").arg(index).arg(val[0]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VOut = %2;").arg(index).arg(val[1]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XMax = %2;").arg(index).arg(banBox.at(1)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XMin = %2;").arg(index).arg(banBox.at(0)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YMax = %2;").arg(index).arg(banBox.at(3)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YMin = %2;").arg(index).arg(banBox.at(2)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZMax = %2;").arg(index).arg(banBox.at(5)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZMin = %2;").arg(index).arg(banBox.at(4)) << Qt::endl;
    
    index++;
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Restrict;").arg(index) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].IField = %2;").arg(index).arg(index - 1) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].EdgesList = {%2};").arg(index).arg(elist.join(",")) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].FacesList = {%2};").arg(index).arg(flist.join(",")) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].RegionsList = {%2};").arg(index).arg(rlist.join(",")) << Qt::endl;
    
    if (back)
        *out << "//+" << Qt::endl
             << QString("Background Field = %1;").arg(index) << Qt::endl;
    
    index++;
}

void FCGmshScriptWriter::writeSolidFrustumScript(QTextStream *out, QStringList list, int &index)
{
    const int n = list.size();
    if (n != 15)
        return;
    
    double val[13] = {0};
    bool ok = false;
    for (int i = 1; i < 14; i++)
    {
        double v = list.at(i).toDouble(&ok);
        if (!ok)
            return;
        val[i - 1] = v;
    }
    
    double xa = val[8];
    double ya = val[9];
    double za = val[10];
    
    int num = 0;
    if (xa != 0)
        num++;
    if (ya != 0)
        num++;
    if (za != 0)
        num++;
    
    if (num == 1)
    {
        val[8] = val[5];
        val[9] = val[6];
        val[10] = val[7];
        if (xa == 1)
            val[8] += val[4];
        else if (ya == 1)
            val[9] += val[4];
        else if (za == 1)
            val[10] += val[4];
    }
    
    if (num > 1)
    {
        double xyz = (xa * xa) + (ya * ya) + (za * za);
        if (xyz > 0)
        {
            double ofs = val[4] / sqrt(xyz);
            
            val[8] += ofs * xa;
            val[9] += ofs * ya;
            val[10] += ofs * za;
        }
    }
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Frustum;").arg(index) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].R1_inner = %2;").arg(index).arg(val[0]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].R2_inner = %2;").arg(index).arg(val[2]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].V1_inner = %2;").arg(index).arg(val[11]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].V2_inner = %2;").arg(index).arg(val[11]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].R1_outer = %2;").arg(index).arg(val[1]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].R2_outer = %2;").arg(index).arg(val[3]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].V1_outer = %2;").arg(index).arg(val[12]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].V2_outer = %2;").arg(index).arg(val[12]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].X1 = %2;").arg(index).arg(val[5]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].X2 = %2;").arg(index).arg(val[8]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Y1 = %2;").arg(index).arg(val[6]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Y2 = %2;").arg(index).arg(val[9]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Z1 = %2;").arg(index).arg(val[7]) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Z2 = %2;").arg(index).arg(val[10]) << Qt::endl;
    
    if (list.at(14).toInt() == 1)
        *out << "//+" << Qt::endl
             << QString("Background Field = %1;").arg(index) << Qt::endl;
    
    index++;
}

void FCGmshScriptWriter::writeSpecifiedMeshScript(QTextStream *out)
{
    Q_UNUSED(out)
}

void FCGmshScriptWriter::writeFluidMeshScript(QString dir, QMultiHash<int, int> solid, QList<int> curve, QList<int> surface)
{
    QString path = dir + "gmsh.Geo";
    QString geo = dir + "geometry.brep";
    
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << path << "open failed.";
        return;
    }
    QTextStream out(&file);
    
    out << QString("Merge \"%1\";").arg(geo) << Qt::endl;
    
    out << QString("Geometry.OCCFixDegenerated = %1;").arg(_geoclean) << Qt::endl;
    out << QString("Geometry.OCCFixSmallEdges = %1;").arg(_geoclean) << Qt::endl;
    out << QString("Geometry.OCCFixSmallFaces = %1;").arg(_geoclean) << Qt::endl;
    out << QString("Geometry.OCCSewFaces = %1;").arg(_geoclean) << Qt::endl;
    out << QString("Mesh.Algorithm = %1;").arg(_method) << Qt::endl;
    out << QString("Mesh.Algorithm3D = %1;").arg(_method) << Qt::endl;
    out << QString("Mesh.ElementOrder = %1;").arg(_elementOrder) << Qt::endl;
    out << QString("Mesh.RecombineAll = %1;").arg(_elementType) << Qt::endl;
    out << QString("Mesh.SubdivisionAlgorithm = %1;").arg(_elementType) << Qt::endl;
    out << "//+" << Qt::endl;
    out << "SetFactory(\"OpenCASCADE\");" << Qt::endl;
    
    QList<double> banbox = getSolidBndBox(solid);
    if (banbox.size() != 6)
        return;
    
    writeFluidFieldScript(&out, banbox, curve, surface);
    
    file.close();
}

void FCGmshScriptWriter::writeFluidFieldScript(QTextStream *out, QList<double> banbox, QList<int> curve, QList<int> surface)
{
    // 		QList<double> banbox = getSolidBndBox(_solidHash);
    // 		if (banbox.size() != 6)return;
    
    // 		if (_solidHash.size() < 1)return;
    //
    // 		QList<int> curve = getShapeIndexListInSolid(_solidHash, 2);
    // 		QList<int> surface = getShapeIndexListInSolid(_solidHash, 3);
    
    double xl = banbox[1] - banbox[0];
    double yl = banbox[3] - banbox[2];
    double zl = banbox[5] - banbox[4];
    
    // QSet<int> curves = curve.toSet();
    // QSet<int> surfaces = surface.toSet();
    
    QSet<int> curves(curve.begin(), curve.end());
    QSet<int> surfaces(surface.begin(), surface.end());
    // QSet<int> solids(solid.begin(), solid.end());
    
    QStringList elist, flist;
    for (int c : curves)
    {
        elist.append(QString::number(c));
    }
    
    for (int s : surfaces)
    {
        flist.append(QString::number(s));
    }
    
    double thick = getFluidMeshSize(xl, yl, zl);
    double factor = getShrinkFactor(xl, yl, zl);
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Box;").arg(1) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].Thickness = %2;").arg(1).arg(thick * 5) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VIn = %2;").arg(1).arg(thick) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].VOut = %2;").arg(1).arg(thick * 10) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XMax = %2;").arg(1).arg(banbox.at(1)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].XMin = %2;").arg(1).arg(banbox.at(0)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YMax = %2;").arg(1).arg(banbox.at(3)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].YMin = %2;").arg(1).arg(banbox.at(2)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZMax = %2;").arg(1).arg(banbox.at(5)) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].ZMin = %2;").arg(1).arg(banbox.at(4)) << Qt::endl;
    
    *out << "//+" << Qt::endl
         << QString("Field[%1] = Restrict;").arg(2) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].IField = %2;").arg(2).arg(1) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].EdgesList = {%2};").arg(2).arg(elist.join(",")) << Qt::endl;
    *out << "//+" << Qt::endl
         << QString("Field[%1].FacesList = {%2};").arg(2).arg(flist.join(",")) << Qt::endl;
    
    *out << "//+" << Qt::endl
         << QString("Background Field = %1;").arg(2) << Qt::endl;
    
    *out << "//+" << Qt::endl
         << QString("Extrude {%1,%2,%3} {Surface{ %4 }; Layers{ { 5, 3, 2 }, { 0.3, 0.6, 1 } }; Recombine;}")
                .arg(xl / factor)
                .arg(yl / factor)
                .arg(zl / factor)
                .arg(flist.join(","))
         << Qt::endl;
}

void FCGmshScriptWriter::setCompound(TopoDS_Compound *compound)
{
    _compound = compound;
}

void FCGmshScriptWriter::setElementType(QString type)
{
    if (type.toLower() == "quad")
        _elementType = 1;
    else if (type.toLower() == "hex")
        _elementType = 2;
}

void FCGmshScriptWriter::setElementOrder(int order)
{
    _elementOrder = order;
}

void FCGmshScriptWriter::setMethod(int method)
{
    _method = method;
}

void FCGmshScriptWriter::setFactor(int factor)
{
    _sizeFactor = factor;
}

void FCGmshScriptWriter::setMinSize(double min)
{
    _minSize = min;
}

void FCGmshScriptWriter::setMaxSize(double max)
{
    _maxSize = max;
}

void FCGmshScriptWriter::setSmooth(int smooth)
{
    _smoothIteration = smooth;
}

void FCGmshScriptWriter::setGeoClean(bool clean)
{
    _geoclean = clean;
}

void FCGmshScriptWriter::setGridCoplanar(bool cop)
{
    _isGridCoplanar = cop;
}

void FCGmshScriptWriter::setSizePoints(QString points)
{
    _sizeAtPoints = points;
}

void FCGmshScriptWriter::setSizeFields(QString fields)
{
    _sizeFields = fields;
}

// 	void FCGmshScriptWriter::setFluidField(QList<double*> field)
// 	{
// 		//_fluidField = field;
// 	}

int FCGmshScriptWriter::getShapeIndexInCompound(int setid, int index, int itype)
{
    int resindex = 0;
    TopAbs_ShapeEnum type;
    switch (itype)
    {
    case 1:
        type = TopAbs_VERTEX;
        break;
    case 2:
        type = TopAbs_EDGE;
        break;
    case 3:
        type = TopAbs_FACE;
        break;
    case 4:
        type = TopAbs_SOLID;
        break;
    default:
        break;
    }
    FCGeometryData *data = FCGeometryData::getInstance();
    auto set = data->getGeometrySetByID(setid);
    if (set == nullptr)
        return resindex;
    TopoDS_Shape *shape = set->getShape(itype, index);
    TopTools_IndexedMapOfShape mapper;
    TopExp::MapShapes(*_compound, type, mapper);
    resindex = mapper.FindIndex(*shape);
    
    return resindex;
}

QList<int> FCGmshScriptWriter::getShapeIndexListInSolid(QMultiHash<int, int> setHash, int itype)
{
    QList<int> indexList{};
    TopAbs_ShapeEnum type;
    switch (itype)
    {
    case 1:
        type = TopAbs_VERTEX;
        break;
    case 2:
        type = TopAbs_EDGE;
        break;
    case 3:
        type = TopAbs_FACE;
        break;
    case 4:
        type = TopAbs_SOLID;
        break;
    default:
        break;
    }
    FCGeometryData *data = FCGeometryData::getInstance();
    QMultiHash<int, int>::iterator it = setHash.begin();
    for (; it != setHash.end(); it++)
    {
        auto set = data->getGeometrySetByID(it.key());
        if (set == nullptr)
            continue;
        TopoDS_Shape *shape = set->getShape(4, it.value());
        
        QList<Handle(TopoDS_TShape)> tshapelist;
        
        TopExp_Explorer anExp(*shape, type);
        for (; anExp.More(); anExp.Next())
        {
            const TopoDS_Shape &oneshape = anExp.Current();
            
            Handle(TopoDS_TShape) ts = oneshape.TShape();
            if (tshapelist.contains(ts))
                continue;
            tshapelist.append(ts);
            TopTools_IndexedMapOfShape mapper;
            TopExp::MapShapes(*_compound, type, mapper);
            int resindex = mapper.FindIndex(oneshape);
            indexList.append(resindex);
        }
    }
    return indexList;
}

QList<double> FCGmshScriptWriter::getSolidBndBox(QMultiHash<int, int> setHash)
{
    QList<double> bndboxPara;
    if (setHash.size() < 1)
        return bndboxPara;
    FCGeometryData *data = FCGeometryData::getInstance();
    TopoDS_Compound aRes;
    BRep_Builder aBuilder;
    aBuilder.MakeCompound(aRes);
    QMultiHash<int, int>::iterator it = setHash.begin();
    for (; it != setHash.end(); it++)
    {
        auto set = data->getGeometrySetByID(it.key());
        if (set == nullptr)
            continue;
        TopoDS_Shape *shape = set->getShape(4, it.value());
        if (shape->IsNull())
            continue;
        aBuilder.Add(aRes, *shape);
    }
    if (aRes.IsNull())
        return bndboxPara;
    
    Bnd_Box bndbox;
    BRepBndLib::Add(aRes, bndbox);
    gp_Pnt cormax = bndbox.CornerMax();
    
    gp_Pnt cormin = bndbox.CornerMin();
    bndboxPara.append(cormin.X());
    bndboxPara.append(cormax.X());
    bndboxPara.append(cormin.Y());
    bndboxPara.append(cormax.Y());
    bndboxPara.append(cormin.Z());
    bndboxPara.append(cormax.Z());
    return bndboxPara;
}

double FCGmshScriptWriter::getFluidMeshSize(double xl, double yl, double zl)
{
    double temp = xl;
    if (xl < yl)
        temp = yl;
    if (temp < zl)
        temp = zl;
    
    double size = temp / 100;
    
    return size;
}

double FCGmshScriptWriter::getShrinkFactor(double xl, double yl, double zl)
{
    double temp = xl;
    if (xl < yl)
        temp = yl;
    if (temp < zl)
        temp = zl;
    
    double factor = 1;
    while ((temp / factor) > 1)
    {
        factor = factor * 10;
    }
    
    return factor;
}

} // namespace FC
