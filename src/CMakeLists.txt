
# Cmake的命令不区分大小写，例如message，set等命令；但Cmake的变量区分大小写
# 为统一风格，本项目的Cmake命令全部采用小写，变量全部采用大写加下划线组合。
# FC WorkBench 源码目录Cmake文件

cmake_minimum_required(VERSION 3.12)

########################################################
# 加载库
########################################################


add_subdirectory(FCGui)

add_subdirectory(FCInterface)
add_dependencies(FCInterface FCGui)


# add_subdirectory(FCPluginSupport)
# add_dependencies(FCPluginSupport FCInterface)

add_subdirectory(APP)
