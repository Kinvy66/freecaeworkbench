cmake_minimum_required(VERSION 3.12)
fcmacro_lib_setting(
    "FCShared"
    "FC Shared Lib | https://github.com/kinvy66"
    0
    0
    1
)

########################################################
# Qt
########################################################
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} ${DA_MIN_QT_VERSION} COMPONENTS
    Core
    REQUIRED
)
if(Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()


########################################################
# 文件加载
########################################################
file(GLOB FC_LIB_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB FC_LIB_HPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(${FC_LIB_NAME} INTERFACE)

# 添加头文件目录
target_include_directories(${FC_LIB_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${FC_PROJECT_NAME}/${FC_LIB_NAME}>
)
########################################################
# 安装
########################################################

install(FILES
    ${FC_LIB_HEADER_FILES}
    DESTINATION include/${FC_PROJECT_NAME}/${FC_LIB_NAME}
    COMPONENT headers
)

install(FILES
    ${FC_LIB_HPP_FILES}
    DESTINATION include/${FC_PROJECT_NAME}/${FC_LIB_NAME}
    COMPONENT headers
)
