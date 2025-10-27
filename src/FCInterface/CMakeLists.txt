cmake_minimum_required(VERSION 3.12)

fcmacro_lib_setting(
    "FCInterface"
    "Interface Of FCWorkbench | https://github.com/kinvy66"
    0
    0
    1
)

########################################################
# Qt
########################################################
set(FC_MIN_QT_VERSION 5.14)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} ${FC_MIN_QT_VERSION} COMPONENTS
    Core
    Gui
    Widgets
    Xml
    REQUIRED
)


########################################################
# 文件加载 #!!!!** 注意变更 **!!!!
########################################################
file(GLOB FC_LIB_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB FC_LIB_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${FC_LIB_NAME} SHARED
            ${FC_LIB_HEADER_FILES}
            ${FC_LIB_SOURCE_FILES}
            ${FC_GLOBAL_HEADER}
)

# 构建库定义的宏
target_compile_definitions(${FC_LIB_NAME} PRIVATE FCINTERFACE_BUILDLIB)#!!!!** 注意变更 **!!!!
add_library(${FC_PROJECT_NAME}::${FC_LIB_NAME} ALIAS ${FC_LIB_NAME})
########################################################
# 依赖链接 #!!!!** 注意变更 **!!!!
########################################################
# -------------link Qt--------------------------
target_link_libraries(${FC_LIB_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)



# -------------link SARibbon--------------------------
fcmacro_import_SARibbonBar(${FC_LIB_NAME})

# -------------link QtAdvancedDockingSystem--------------------------
fcmacro_import_QtAdvancedDocking(${FC_LIB_NAME})

# -------------link qwt--------------------------
fcmacro_import_qwt(${FC_LIB_NAME})



if(FC_ENABLE_PYTHON)
    # -------------link python--------------------------
    fcmacro_import_Python(${FC_LIB_NAME})
endif()


find_package(${FC_PROJECT_NAME} COMPONENTS
    # FCGui
)

if(${FC_PROJECT_NAME}_FOUND)
    message(STATUS "  |-linked ${FC_PROJECT_NAME}::FCGui")
endif()
target_link_libraries(${FC_LIB_NAME} PUBLIC
    # ${FC_PROJECT_NAME}::FCGui
)
if(FC_ENABLE_PYTHON)
    # -------------link python--------------------------
    fcmacro_import_Python(${FC_LIB_NAME})
    # -------------link 3rdparty pybind11--------------------------
    fcmacro_import_pybind11(${FC_LIB_NAME})
endif()
########################################################
# 设置通用库属性
########################################################
fcmacro_set_lib_properties(${FC_LIB_NAME} ${FC_LIB_VERSION})

########################################################
# 安装
########################################################
fcmacro_lib_install()

install(FILES
    ${FC_LIB_HEADER_FILES}
    DESTINATION include/${FC_PROJECT_NAME}/${FC_LIB_NAME}
    COMPONENT headers
)
