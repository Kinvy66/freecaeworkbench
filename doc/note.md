## 模块依赖关系

| 模块名                     | 模块简述                                       | 依赖模块                                                     |
| -------------------------- | ---------------------------------------------- | ------------------------------------------------------------ |
| **FCShared**               | 共享头文件模块，提供基础的模板类和共享定义     | Qt::Core                                                     |
| **FCUtils**                | 核心工具模块，提供通用工具函数和基础类         | **FCShared**, Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml        |
| **FCMessageHandler**       | 日志处理模块，基于spdlog实现                   | **FCUtils**, Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml, spdlog |
| **FCGraphicsView**         | 图形视图模块，vtk渲染窗口和交互器封装          | **FCUtils**, Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml, Qt::Svg，vtk, occ |
| **FCData**                 | 数据处理模块，管理数据对象和操作               | **FCUtils**, Qt::Core, Qt::Gui, Qt::Widgets                  |
| **FCGui**                  | GUI界面模块，整合所有UI功能                    | **FCUtils**, **FCMessageHandler**, **FCData**,  **FCGraphicsView**，**FCProjectTree**,Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml, Qt::Svg, Qt6::Core5Compat (Qt6), SARibbonBar, QtAdvancedDocking, qwt |
| **FCInterface**            | 接口模块，提供插件和扩展接口                   | Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml, SARibbonBar, QtAdvancedDocking, |
| **FCGeometryParameter**    | 几何模型参数模块，封装不同几何模型的参数       | **FCData**,Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml           |
| **FCGeometryModelCreator** | 几何模型创建模块                               | **FCGeometryParameter**,Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml，vtk， occ |
| **FCProjectTree**          | 工程树形目录模块，提供工程树结构增删改查的操作 | **FCInterface**,Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml,Qt::svg |
| **FCProjectArchive**       | 工程归档模块，工程文件打包和压缩               | Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml, quazip              |
| **APP**                    | 主应用程序                                     | Qt::Core, Qt::Gui, Qt::Widgets, Qt::Xml, Qt::Svg, Qt::Concurrent, Qt::PrintSupport, Qt::AxContainer (Windows), Qt6::Core5Compat (Qt6),  SARibbonBar, QtAdvancedDocking, qwt,  Dbghelp (Windows) |

