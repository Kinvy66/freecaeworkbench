cmake_minimum_required(VERSION 3.12)

fcmacro_lib_setting(
    "FCActionManager"
    "FC Action Manager | https://github.com/kinvy66"
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
    Svg
    REQUIRED
)

file(GLOB FC_LIB_GUI_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB FC_LIB_GUI_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB FC_LIB_GUI_QT_UI_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
file(GLOB FC_LIB_GUI_QT_RC_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)


add_library(${FC_LIB_NAME} SHARED   
            ${FC_LIB_GUI_HEADER_FILES}
            ${FC_LIB_GUI_SOURCE_FILES}
            ${FC_LIB_GUI_QT_UI_FILES}
            ${FC_LIB_GUI_QT_RC_FILES}
)

# 构建库定义的宏
target_compile_definitions(${FC_LIB_NAME} PRIVATE FCACTIONMANAGER_BUILDLIB)#!!!!** 注意变更 **!!!!
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
    Qt${QT_VERSION_MAJOR}::Svg
)
if(${QT_VERSION_MAJOR} EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core5Compat)
    target_link_libraries(${FC_LIB_NAME} PRIVATE Qt6::Core5Compat)
endif()

# -------------link FCWorkBench--------------------------
find_package(${FC_PROJECT_NAME} COMPONENTS
    FCInterface
    FCGui
)

if(${FC_PROJECT_NAME}_FOUND)
    message(STATUS "  |-linked ${FC_PROJECT_NAME}::FCInterface")

endif()
target_link_libraries(${FC_LIB_NAME} PUBLIC
    ${FC_PROJECT_NAME}::FCInterface
    ${FC_PROJECT_NAME}::FCGui
    
)


# -------------link 3rdparty--------------------------


########################################################
# 设置通用库属性
########################################################
fcmacro_set_lib_properties(${FC_LIB_NAME} ${FC_LIB_VERSION})


########################################################
# 附加编译选项
########################################################
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # 这里是为 MSVC 编译器设置的选项
    target_link_options(${FC_LIB_NAME} PRIVATE /VERBOSE)
    # 或者设置其他 MSVC 特定的编译或链接选项
else()
    # 这里是为非 MSVC 编译器设置的选项（如果有的话）
endif()
########################################################
# 安装
########################################################
fcmacro_lib_install()

install(FILES
    ${FC_LIB_GUI_HEADER_FILES}
    DESTINATION include/${FC_PROJECT_NAME}/${FC_LIB_NAME}
    COMPONENT headers
)
