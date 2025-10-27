
# Cmake的命令不区分打下写，例如message，set等命令；但Cmake的变量区分大小写
# 为统一风格，本项目的Cmake命令全部采用小写，变量全部采用大写加下划线组合。

cmake_minimum_required(VERSION 3.12)
project(FCWorkBench-3rdparty-build
        DESCRIPTION "FreeCAEWorkBench : 3rdparty build"
)
message(STATUS "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
# 编译选项
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
########################################################
# 安装路径设置
########################################################
include(GNUInstallDirs)

set(FC_MIN_QT_VERSION 5.14)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(FC_PLATFORM_NAME "x86")
else()
    set(FC_PLATFORM_NAME "x64")
endif()

set(FC_BIN_DIR_NAME bin_${CMAKE_BUILD_TYPE}_qt${QT_VERSION}_${CMAKE_CXX_COMPILER_ID}_${FC_PLATFORM_NAME})
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../${FC_BIN_DIR_NAME}" CACHE PATH "Install all third-party libraries into the default installation directory of the current build." FORCE)
########################################################
# 第三方库参数设置
########################################################
#spdlog
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "force set SPDLOG_BUILD_EXAMPLE off" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "force set SPDLOG_BUILD_TESTS off" FORCE)
set(SPDLOG_INSTALL ON CACHE BOOL "force set SPDLOG_INSTALL ON" FORCE)
if(WIN32)
    set(SPDLOG_WCHAR_FILENAMES ON CACHE BOOL "force set SPDLOG_WCHAR_FILENAMES ON enable chinese file path" FORCE)
endif()

#ADS
set(BUILD_EXAMPLES OFF CACHE BOOL "force set BUILD_EXAMPLES OFF" FORCE)

#QWT
set(QWT_CONFIG_BUILD_EXAMPLE OFF CACHE BOOL "force set QWT_CONFIG_BUILD_EXAMPLE OFF" FORCE)
set(QWT_CONFIG_BUILD_PLAYGROUND OFF CACHE BOOL "force set QWT_CONFIG_BUILD_PLAYGROUND OFF" FORCE)

#SARibbon
set(SARIBBON_BUILD_EXAMPLES OFF CACHE BOOL "force set SARIBBON_BUILD_EXAMPLES off" FORCE)
set(SARIBBON_INSTALL_IN_CURRENT_DIR OFF CACHE BOOL "force set SARIBBON_INSTALL_IN_CURRENT_DIR off" FORCE)

#zlib
set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "force set ZLIB_BUILD_EXAMPLES off" FORCE)

#quazip
set(QUAZIP_INSTALL ON CACHE BOOL "force set QUAZIP_INSTALL on" FORCE)
set(QUAZIP_USE_QT_ZLIB OFF CACHE BOOL "force set QUAZIP_USE_QT_ZLIB oFF" FORCE)
set(QUAZIP_ENABLE_TESTS OFF CACHE BOOL "force set QUAZIP_ENABLE_TESTS oFF" FORCE)

# 设置zlib的路径
# set(ZLIB_DIR "C:/opt/zlib")
# set(ZLIB_INCLUDE_DIR "C:/opt/zlib/include")
# set(ZLIB_LIBRARY "C:/opt/zlib/lib/zlib.lib")
# quazip依赖zlib，先看看zlib是否安装
find_package(ZLIB QUIET)
if(NOT ZLIB_FOUND)
    message(ERROR "Unable to find the zlib library. If you have already installed the zlib library, "
        "you need to set ZLIB_DIR to point to the installation directory of zlib. "
        "If you have not installed the zlib library, you need to compile it first and then execute the installation command")
else()
    get_target_property(ZLIB_LOCATION ZLIB::ZLIB LOCATION)
    # 获取 DLL 的目录
    get_filename_component(ZLIB_LIB_DIR "${ZLIB_LOCATION}" DIRECTORY)
    get_filename_component(ZLIB_BIN_DIR "${ZLIB_LIB_DIR}/../${CMAKE_INSTALL_BINDIR}" ABSOLUTE)
    message(STATUS "finded zlib,ZLIB_INCLUDE_DIRS=${ZLIB_INCLUDE_DIRS}")
    message(STATUS "finded zlib,ZLIB_LIBRARIES=${ZLIB_LIBRARIES}")
    message(STATUS "finded zlib,ZLIB_BIN_DIR=${ZLIB_BIN_DIR}")
endif()

#vtk参数配置
# set(VTK_GROUP_ENABLE_Qt YES CACHE STRING "enable vtk qt support" FORCE)
# set(VTK_QT_VERSION 6 CACHE STRING "enable vtk qt support" FORCE)
# set(Qt6_DIR "C:/Qt/6.5.2/msvc2019_64/lib/cmake/Qt6" CACHE PATH "Qt6 cmake path for VTK" FORCE)
# set(VTK_MODULE_ENABLE_VTK_GUISupportQt YES CACHE STRING "enable vtk qt support" FORCE)
# set(VTK_MODULE_ENABLE_VTK_GUISupportQtQuick YES CACHE STRING "enable vtk qt support" FORCE)
# set(VTK_MODULE_ENABLE_VTK_GUISupportQtSQL YES CACHE STRING "enable vtk qt support" FORCE)
# set(VTK_MODULE_ENABLE_VTK_RenderingQt YES CACHE STRING "enable vtk qt support" FORCE)


########################################################
# 安装第三方库
########################################################
# include(GNUInstallDirs)

# 这是用于高效绘图的库，原版 不支持cmake，这里进行了cmake化
add_subdirectory(qwt)

# 这是ribbon界面的支持库
add_subdirectory(SARibbon)

# 这是docking界面的支持库
add_subdirectory(ADS)

# 这是高效的日志库
add_subdirectory(spdlog)

# quazip依赖zlib库，zlib库要单独安装
add_subdirectory(quazip)

# add_subdirectory(vtk)

# pybind11直接把文件夹复制过去
file(COPY "${CMAKE_CURRENT_LIST_DIR}/pybind11/include/pybind11" DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

########################################################
# install
########################################################
