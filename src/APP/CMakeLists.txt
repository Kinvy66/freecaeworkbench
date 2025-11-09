cmake_minimum_required(VERSION 3.12)

fcmacro_app_setting(
    "FCWorkBench"
    "FCWorkBench App"
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
    Concurrent
    PrintSupport
    REQUIRED
)

if(WIN32)
    find_package(Qt${QT_VERSION_MAJOR} ${FC_MIN_QT_VERSION} COMPONENTS
        AxContainer
        REQUIRED
    )
endif()

# qt6,引入Core5Compat
if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} ${FC_MIN_QT_VERSION} COMPONENTS
        Core5Compat
        REQUIRED
    )
endif()


########################################################
# 文件加载 #!!!!** 注意变更 **!!!!
########################################################
file(GLOB FC_APP_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB FC_APP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB FC_APP_QT_UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
file(GLOB FC_APP_QT_RC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)


add_executable(${FC_APP_NAME}
            ${FC_APP_HEADER_FILES}
            ${FC_APP_SOURCE_FILES}
            ${FC_APP_QT_UI_FILES}
            ${FC_APP_QT_RC_FILES}
            #SettingPages
            # ${FC_APP_HEADER_FILES_SettingPages}
            # ${FC_APP_SOURCE_FILES_SettingPages}
            # ${FC_APP_QT_UI_FILES_SettingPages}
            # ${FC_APP_QT_RC_FILES_SettingPages}
            #Dialog
            # ${FC_APP_HEADER_FILES_Dialog}
            # ${FC_APP_SOURCE_FILES_Dialog}
            # ${FC_APP_QT_UI_FILES_Dialog}
            # ${FC_APP_QT_RC_FILES_Dialog}
            # Global
            ${FC_GLOBAL_HEADER}
)	

# Windows 平台下设置为窗口应用程序
if(WIN32)
    set_target_properties(${FC_APP_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# 构建APP定义的宏
target_compile_definitions(${FC_APP_NAME} PRIVATE QT_DEPRECATED_WARNINGS)#!!!!** 注意变更 **!!!!

# 公共宏
target_compile_definitions(${FC_APP_NAME} PUBLIC
    FC_APP_ORGANIZATION="FC"
    FC_APP_APPLICATION_NAME="WorkBench"
)

########################################################
# 依赖链接 #!!!!** 注意变更 **!!!!
########################################################
# -------------link Qt--------------------------
target_link_libraries(${FC_APP_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::AxContainer
)
if(WIN32)
    target_link_libraries(${FC_APP_NAME} PUBLIC
        Qt${QT_VERSION_MAJOR}::AxContainer
    )
endif()


# -------------link 3rdparty SARibbon--------------------------
fcmacro_import_SARibbonBar(${FC_APP_NAME})
# -------------link 3rdparty QtAdvancedDocking--------------------------
fcmacro_import_QtAdvancedDocking(${FC_APP_NAME})
# -------------link 3rdparty qwt--------------------------
fcmacro_import_qwt(${FC_APP_NAME})
# -------------link 3rdparty vtk--------------------------
fcmacro_import_vtk(${FC_APP_NAME})
# -------------link 3rdparty occ--------------------------
fcmacro_import_occ(${FC_APP_NAME})

if(FC_ENABLE_PYTHON)
    # -------------link python--------------------------
    fcmacro_import_Python(${FC_APP_NAME})
endif()

find_package(${FC_PROJECT_NAME} COMPONENTS
    FCInterface
    FCGui
)

if(${FC_PROJECT_NAME}_FOUND)
    message(STATUS "  |-linked ${FC_PROJECT_NAME}::FCInterface")
endif()
target_link_libraries(${FC_APP_NAME} PUBLIC
    ${FC_PROJECT_NAME}::FCInterface
    ${FC_PROJECT_NAME}::FCGui
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${DA_APP_NAME})
endif()
set_target_properties(${DA_APP_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${DA_APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${FC_APP_NAME})
endif()


# -------------link Dbghelp--------------------------
if(WIN32)
    target_link_libraries(${FC_APP_NAME} PRIVATE
        Dbghelp
    )
endif()

fcmacro_import_vtk(${FC_APP_NAME})

fcmacro_import_occ(${FC_APP_NAME})

# target_link_libraries(${PROJECT_NAME} PRIVATE  ${OpenCASCADE_LIBRARIES})


########################################################
# app 属性设置
########################################################
fcmacro_set_app_properties(${FC_APP_NAME} ${FC_APP_VERSION})

########################################################
# 写入rc信息
########################################################
# if(WIN32)
#     create_win32_resource_version(
#         TARGET ${FC_APP_NAME}
#         VERSION ${FC_APP_VERSION}
#         COMPANY_NAME "FC"
#         COPYRIGHT "Copyright @ 2025 FC All rights reserved."
#         DESCRIPTION ${FC_APP_FULL_DESCRIPTION}
#         ICONS "${CMAKE_CURRENT_SOURCE_DIR}/icon.ico"
#         FILE_EXTENSION exe
#     )
# endif()
########################################################
# 安装
########################################################
fcmacro_app_install()


