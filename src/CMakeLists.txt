
# Cmake的命令不区分打下写，例如message，set等命令；但Cmake的变量区分大小写
# 为统一风格，本项目的Cmake命令全部采用小写，变量全部采用大写加下划线组合。
# FC WorkBench 源码目录Cmake文件

cmake_minimum_required(VERSION 3.12)

########################################################
# 加载库
########################################################
# add_subdirectory(FCShared)
# add_subdirectory(FCUtils)

# if(WIN32)
#     # DAAxOfficeWrapper基于Axcontainer是windows独有的技术
#     add_subdirectory(DAAxOfficeWrapper)
#     add_dependencies(DAAxOfficeWrapper DAUtils)
# endif()

# add_subdirectory(FCMessageHandler)
# add_dependencies(FCMessageHandler FCUtils)

# 添加Python支持
# if(FC_ENABLE_PYTHON)
#     add_subdirectory(FCPyBindQt)

#     add_subdirectory(FCPyScripts)
#     add_dependencies(FCPyScripts FCPyBindQt)

#     add_subdirectory(FCPyCommonWidgets)
#     add_dependencies(FCPyCommonWidgets FCPyBindQt)

#     add_subdirectory(FCData)
#     add_dependencies(FCData FCUtils FCPyBindQt FCPyScripts)
# else()
#     add_subdirectory(FCData)
# endif()


# add_subdirectory(FCCommonWidgets)
# add_dependencies(FCCommonWidgets FCUtils)

# add_subdirectory(FCGraphicsView)
# add_dependencies(FCGraphicsView FCUtils)

# add_subdirectory(FCWorkFlow)
# add_dependencies(FCWorkFlow FCGraphicsView)

# add_subdirectory(FCGui)

add_subdirectory(FCInterface)
# add_dependencies(FCInterface FCGui)

# add_subdirectory(FCPluginSupport)
# add_dependencies(FCPluginSupport FCInterface)

add_subdirectory(APP)

