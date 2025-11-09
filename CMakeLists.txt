
# Cmake的命令不区分打下写，例如message，set等命令；但Cmake的变量区分大小写
# 为统一风格，本项目的Cmake命令全部采用小写，变量全部采用大写加下划线组合。
# DA WorkBench 顶层Cmake文件
# 在运行次CMakeLists.txt之前，请确保3rdparty已经运行并进行了install，3rdparty位于./3rdparty/CMakeLists.txt
# 请先单独编译第三方库后，安装，并把安装目录设置到和此安装目录一致

#3.16是qt6要求的最低版本
cmake_minimum_required(VERSION 3.12)

########################################################
# 版本定义
########################################################
set(FC_VERSION_MAJOR 0)
set(FC_VERSION_MINOR 0)
set(FC_VERSION_PATCH 1)
set(FC_VERSION "${FC_VERSION_MAJOR}.${FC_VERSION_MINOR}.${FC_VERSION_PATCH}")
string(TIMESTAMP FC_COMPILE_DATETIME %y%m%d)
string(TIMESTAMP FC_COMPILE_DATETIME_YEAR %y)
string(TIMESTAMP FC_COMPILE_DATETIME_MONTH %m)
string(TIMESTAMP FC_COMPILE_DATETIME_DAY %d)
message(STATUS "FreeCAEWorkbench Version is ${FC_VERSION}")

########################################################
# 定义工程
########################################################
set(FC_PROJECT_NAME "FCWorkbench")

# set(ZLIB_DIR "C:/opt/zlib")
# set(ZLIB_INCLUDE_DIR "C:/opt/zlib/include")
# set(ZLIB_LIBRARY "C:/opt/zlib/lib/zlib.lib")

project(${FC_PROJECT_NAME}
        VERSION ${FC_VERSION}
        LANGUAGES CXX
        DESCRIPTION "FreeCAEWorkBench : A Workflow Integration Workbench"
        )

########################################################
# include
########################################################
include(${CMAKE_CURRENT_LIST_DIR}/cmake/fcworkbench_utils.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/fcworkbench_3rdparty.cmake)


########################################################
# 可选的变量
########################################################
# 此选项将设置是否开启python
option(FC_ENABLE_PYTHON
    "enable python|if ON will add FCPythonBind FCPyScript FCPyCommonWidgets COMPONENTS"
    OFF)
option(FC_ENABLE_AUTO_INSTALL_PYTHON_ENV
    "This parameter allows cmake to automatically search for the Python environment and copy the necessary DLLs from the Python environment to the bin directory without manual deployment. It is recommended to enable this option for Windows users who have not set the Python directory as a system environment variable"
    OFF)
# 此选项将自动调用Linguist工具对翻译文件进行翻译
option(FC_ENABLE_AUTO_TRANSLATE
    "This option will automatically call the Linguist tool to translate the ts file"
    OFF)
# 此选项将自动调用Linguist工具对翻译文件进行update,此参数建议仅对翻译时开启
option(FC_ENABLE_UPDATE_TRANSLATE
    "This option will automatically call the Linguist tool to update ts file"
    OFF)
# 此选项将让fc自动把结果安装到本地目录下
option(FC_AUTO_INSTALL_PREFIX
    "This option will allow FC to automatically install the results to the local directory"
    ON)
# 此选项将让fc自动生成FCConfig.h文件，此选项仅库开发者需要设置为ON，库使用者默认应该为OFF
option(FC_AUTO_GENERATE_CONFIG_INFO
    "This option will allow FC to automatically generate FCConfig.h, This option only needs to be set to ON by library developers, and library users should default to OFF"
    OFF)
# 此选项将让fc自动生成构建plugin
option(FC_BUILD_PLUGINS
    "This option will build plugin"
    OFF)
if(FC_AUTO_INSTALL_PREFIX)
    message(STATUS "FC Auto Install")
    set(FC_BIN_DIR_NAME)
    fcfun_set_bin_name(FC_BIN_DIR_NAME)
    set(FCWorkbench_INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/${FC_BIN_DIR_NAME}")
    set(CMAKE_INSTALL_PREFIX ${FCWorkbench_INSTALL_DIR} CACHE PATH "Installation prefix" FORCE)
    message(STATUS "FC_BIN_DIR_NAME=${FC_BIN_DIR_NAME}")
    message(STATUS "FCWorkbench_INSTALL_DIR=${FCWorkbench_INSTALL_DIR}")
endif()


########################################################
# 一些常规设置
########################################################
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")

# c++标准，要求为17
set(CMAKE_CXX_STANDARD 17)
# 强制要求
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)


########################################################
# MSVC设置
########################################################
if(MSVC)
# msvc utf-8
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    # make sure __cplusplus is defined when using msvc and enable parallel build
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /MP")

    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 1)
    set(CMAKE_CXX_RESPONSE_FILE_PREFIX "@")
    set(CMAKE_CXX_RESPONSE_FILE_EXTENSION ".rsp")
endif()

if(CMAKE_GENERATOR STREQUAL "Ninja")
    # 针对Ninja生成器
    set(CMAKE_NINJA_FORCE_RESPONSE_FILE "1")
endif()
########################################################
# MSVC设置
# 如果不添加会出现
# Qt5AxContainerd.lib(qaxbase.obj) : error LNK2038  MDd_DynamicDebug MTd_StaticDebug等提示
# Qt5AxBased.lib(qaxtypefunctions.obj) : error LNK2038:
# 可以通过下面方式设置
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
########################################################
if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MD>
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Release>:/MD>
    )
endif()


########################################################
# Qt
########################################################
set(FC_MIN_QT_VERSION 5.14)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)


########################################################
# 默认路径设置
########################################################
set(FC_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(FC_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(FC_INSTALL_LIB_CMAKE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake)
set(FC_OCC_INSTALL_LIB_CMAKE_PATH ${CMAKE_INSTALL_PREFIX}/occ/cmake)
set(FC_INSTALL_LIB_SHARE_PATH ${CMAKE_INSTALL_PREFIX}/share/cmake)
list(APPEND CMAKE_MODULE_PATH ${FC_CMAKE_DIR} ${FC_INSTALL_LIB_CMAKE_PATH})

########################################################
# 定义第三方库路径
########################################################
set(SARibbonBar_DIR ${FC_INSTALL_LIB_CMAKE_PATH}/SARibbonBar)
message(STATUS "SARibbonBar_DIR=${SARibbonBar_DIR}")

set(VTK_DIR ${FC_INSTALL_LIB_CMAKE_PATH}/vtk-9.4)
message(STATUS "VTK_DIR=${VTK_DIR}")

set(qwt_DIR ${FC_INSTALL_LIB_CMAKE_PATH}/qwt)
message(STATUS "qwt_DIR=${qwt_DIR}")

set(spdlog_DIR ${FC_INSTALL_LIB_CMAKE_PATH}/spdlog)
message(STATUS "spdlog_DIR=${spdlog_DIR}")

set(occ_DIR ${CMAKE_INSTALL_PREFIX}/occ/cmake)
message(STATUS "occ_DIR=${occ_DIR}")

set(qt${QT_VERSION_MAJOR}advanceddocking_DIR  ${FC_INSTALL_LIB_CMAKE_PATH}/qtadvanceddocking-qt${QT_VERSION_MAJOR})
message(STATUS "qt${QT_VERSION_MAJOR}advanceddocking_DIR=${qt${QT_VERSION_MAJOR}advanceddocking_DIR}")


##################################
# 初步安装 install 通用内容
##################################
message(STATUS "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "${FC_PROJECT_NAME} install dir is : ${CMAKE_INSTALL_PREFIX}")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${DA_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${DA_PROJECT_NAME}
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    DESTINATION lib/cmake/${DA_PROJECT_NAME}
)


########################################################
# 自动化生成配置头文件
########################################################
if(FC_AUTO_UPDATE_CONFIG_INFO)
    configure_file (
      "${CMAKE_CURRENT_LIST_DIR}/src/FCConfigs.h.in"
      "${CMAKE_CURRENT_LIST_DIR}/src/FCConfigs.h"
    )
endif()
#FCGlobal.h
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/FCGlobals.h
    DESTINATION include/${FC_PROJECT_NAME}
    COMPONENT headers
)
#FCConfigs.h
install(FILES
        ${CMAKE_CURRENT_LIST_DIR}/src/FCConfigs.h
        DESTINATION include/${FC_PROJECT_NAME}
        COMPONENT headers
 )

########################################################
# 添加预定义宏NOMINMAX,windows系统会定义max和min宏，这个宏和std::max冲突,因此在高版本的c++，应该取消minmax宏
########################################################
if(WIN32)
    ADD_COMPILE_DEFINITIONS(NOMINMAX)
endif()

########################################################
# 源码路径
########################################################
add_subdirectory(src)

# 插件
if(FC_BUILD_PLUGINS)
    add_subdirectory(plugins)
endif()

##################################
# 最终安装 install
##################################
include(GNUInstallDirs)
if(FC_ENABLE_PYTHON)
    # 把PyScripts文件夹复制过去
    install(DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR}/src/PyScripts
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    # 为了能调试的时候运行，需要把src/PyScripts文件夹复制到${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
    file(COPY "${CMAKE_CURRENT_LIST_DIR}/src/PyScripts" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
    message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/src/PyScripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
    if(FC_ENABLE_AUTO_INSTALL_PYTHON_ENV)
        # 如果使用的是非系统目录下的 Python 可以通过指定 Python3_ROOT_DIR 改变查找路径
        find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
        if(${Python3_FOUND})
            if(WIN32)
                set(FC_PYTHON_DLL_PATH ${Python3_RUNTIME_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}.dll)
                # 把dll复制到bin中否则无法运行
                file(COPY ${FC_PYTHON_DLL_PATH} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
                install(FILES
                        ${FC_PYTHON_DLL_PATH}
                        DESTINATION
                        ${CMAKE_INSTALL_BINDIR}
                 )
            endif()
        endif()
    endif()
endif()


install(FILES
    # "${CMAKE_CURRENT_LIST_DIR}/cmake/fcworkbench_plugin_utils.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/cmake/create_win32_resource_version.cmake"
    DESTINATION lib/cmake/${FC_PROJECT_NAME}
)



##################################
# 翻译
##################################
if(FC_ENABLE_AUTO_TRANSLATE)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS LinguistTools REQUIRED)

    # 如果你有新的翻译需求，你需要在此添加新的ts文件，qt会自动生成新的翻译文件
    set(FC_TS_FILES
        ${CMAKE_CURRENT_LIST_DIR}/src/i18n/fc_zh_CN.ts
        ${CMAKE_CURRENT_LIST_DIR}/src/i18n/fc_en_US.ts
    )

    # 扫描的源码目录（按需增删）
    set(FC_LUPDATE_SOURCE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/APP
    )

    # 自动 update + release → 生成 FC_QM_FILES
    if(QT_VERSION_MAJOR EQUAL 5)
        qt5_create_translation(FC_QM_FILES ${FC_LUPDATE_SOURCE_DIRS} ${FC_TS_FILES}
            OPTIONS -locations relative -no-obsolete)
    elseif(QT_VERSION_MAJOR EQUAL 6)
        qt6_create_translation(FC_QM_FILES ${FC_LUPDATE_SOURCE_DIRS} ${FC_TS_FILES}
            OPTIONS -locations relative -no-obsolete)
    endif()

    add_custom_target(fc_translations ALL DEPENDS ${FC_QM_FILES})
    install(FILES ${FC_QM_FILES}
                DESTINATION ${CMAKE_INSTALL_BINDIR}/translations
                COMPONENT translations)
    message(STATUS "Translation enabled,qm files is ${FC_QM_FILES}")
endif()

