/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraph3DWindowInterface.h"
#include "FCGraph3DWindowVTK.h"
#include "FCGraphInteractionStyle.h"

// #include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
// #include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
// #include "FITK_Kernel/FITKAppFramework/FITKRunTimeSetting.h"

#ifdef Q_OS_WIN
#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QFile>
#include <QDebug>
#endif

#include <vtkMapper.h>

#define OpenGL_Version_Major 3
#define OpenGL_Version_minor 2

namespace FC
{
    QString FCGraph3DWindowInterface::CheckSystem()
    {
#ifdef Q_OS_WIN
        
        // 获取当前可执行程序所在路径
        QString exePath = QCoreApplication::applicationDirPath();
        QString glewInfoPath = QDir(exePath).filePath("glewinfo.exe");
        //拷贝文件
        QFile::copy("://OpenGL/glew/glew32.dll", QDir(exePath).filePath("glew32.dll"));
        QFile::copy("://OpenGL/glew/glewinfo.exe", glewInfoPath);

        // 保存当前工作目录
        QString currentPath = QDir::currentPath();
        // 设置工作目录为可执行文件所在路径
        QDir::setCurrent(exePath);
        // 删除 glewinfo.txt 文件
        QFile::remove(QDir(exePath).filePath("glewinfo.txt"));

        // 启动 glewinfo.exe 并获取输出
        QProcess process;
        process.setProgram(glewInfoPath);
//        process.setArguments({ "-version", "5.2" });
        process.start();
        if (!process.waitForFinished())
        {
            // 恢复工作目录
            QDir::setCurrent(currentPath);
            return QString("Failed to start glewinfo.exe");
        }
        // 恢复工作目录
        QDir::setCurrent(currentPath);

        // 读取 glewinfo.txt 文件的第六行和第七行
        QFile file(QDir(exePath).filePath("glewinfo.txt"));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // 恢复工作目录
            QDir::setCurrent(currentPath);
            return QString("Failed to open glewinfo.txt");
        }
        
        while (!file.atEnd())
        {
            QString line = file.readLine();
            //版本信息
            if (line.startsWith("OpenGL version"))
            {
                QString version = line.split(" ")[2].trimmed();
                qDebug() << "OpenGL version: " << version;
                if (version.split(".").size() < 2)
                {
                    file.close();
                    return QString("Failed to get OpenGL version");
                }
                //版本号
                int major = version.split(".")[0].toInt();
                int minor = version.split(".")[1].toInt();

                if (major < OpenGL_Version_Major || 
                    (major == OpenGL_Version_Major && minor < OpenGL_Version_minor))
                {
                    file.close();
                    return QString("OpenGL version must be %1.%2 or higher, but got %3 ")
                        .arg(OpenGL_Version_Major).arg(OpenGL_Version_minor).arg(version);
                }
                break;

            }
            //输出硬件信息
            else if (line.startsWith("Running on a"))
            {
                qDebug() << line;
            }
        }

        file.close(); 
#endif //  Q_OS_Win
        return QString();
    }


    FCGraph3DWindowInterface::~FCGraph3DWindowInterface()
    {
        //释放初始化器
        QList <Graph3DWindowInitializer*> inis = _initilizerList.values();
        for (auto iner : inis)
        {
            delete iner;
        }
        _initilizerList.clear();
    }

  

    QWidget* FCGraph3DWindowInterface::getWidget(const int indexPort)
    {
        //获取初始化器
        auto initer = _initilizerList.value(indexPort);
        if (initer == nullptr)
            initer = new Graph3DWindowInitializer;
        //创建三维渲染窗口
        auto w = new FCGraph3DWindowVTK(initer);

        //获取
        // AppFrame::FITKRunTimeSetting* runTimeSetting = FITKAPP->getGlobalData()->getRunTimeSetting();
        // QVariant vtc = runTimeSetting->getValue(BackGroundColorTop);
        // QVariant vbc = runTimeSetting->getValue(BackGroundColorButtom);
        // //程序运行参数获取不到，则获取默认颜色
        // if ((!vbc.isValid()) && (!vtc.isValid()))
        // {
        //     //设置背景色
        //     vtc = initer->getValue(BackGroundColorTop);
        //     vbc = initer->getValue(BackGroundColorButtom);
        // }
        // //无效值不操作
        // if (vbc.isValid() && vtc.isValid())
        // {
        //     //top
        //     QColor c = vtc.value<QColor>();
        //     float t[3] = { c.redF(),c.greenF(),c.blueF() };
        //     //buttom
        //     c = vbc.value<QColor>();
        //     float b[3] = { c.redF(),c.greenF(),c.blueF() };
        //     if (w)
        //         w->setBackgroundColor(t, b);
        // }
        return w;
    }

    QString FCGraph3DWindowInterface::getComponentName()
    {
        //返回三维渲染组件在组件管理类中的标识
        return "Graph3DWindowVTK";
    }

    void FCGraph3DWindowInterface::addInitializer(int key, Graph3DWindowInitializer* info)
    {
        //添加初始化器
        if(_initilizerList.contains(key))
        {
            auto iner = _initilizerList.value(key);
            //释放旧的初始化器
            if (iner)
                delete iner;
        }
        _initilizerList[key] = info;
    }


  

    FCGraphInteractionStyle* Graph3DWindowInitializer::getStyle()
    {
        //创建默认交互样式
        return  FCGraphInteractionStyle::New();
    }

    void Graph3DWindowInitializer::setLayerCount(const int nc)
    {
        _layerCount = nc;
    }

    int Graph3DWindowInitializer::getLayerCount() const
    {
        return _layerCount;
    }

    void FCGraph3DWindowInterface::SetResolveCoincidentType(ResolveCoincidentType type)
    {
        // 解决Z-fighting问题。
        switch (type)
        {
        case FC::RCT_Off:
            vtkMapper::SetResolveCoincidentTopologyToOff();
            break;
        case FC::RCT_Default:
            vtkMapper::SetResolveCoincidentTopologyToDefault();
            break;
        case FC::RCT_PolygonOffset:
            vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();
            break;
        case FC::RCT_ShiftZBuffer:
            vtkMapper::SetResolveCoincidentTopologyToShiftZBuffer();
            break;
        default:
            break;
        }
    }
}
