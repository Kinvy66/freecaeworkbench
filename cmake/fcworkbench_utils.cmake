# 获取默认安装目录
function(fcfun_set_bin_name _var)
    set(_MIN_QT_VERSION 5.14)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
    ########################################################
    # 平台判断
    ########################################################
    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        set(_platform_name "x86")
    else()
        set(_platform_name "x64")
    endif()
    if(NOT DEFINED CMAKE_CXX_COMPILER_ID OR CMAKE_CXX_COMPILER_ID STREQUAL "")
        message(WARNING "CMAKE_CXX_COMPILER_ID is NULL,maybe your cmake env error")
        set(_CXX_COMPILER_ID "MSVC")
    else()
        set(_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})
    endif()
    ########################################################
    # 安装路径设置 设置变量值，并传递到父作用域
    ########################################################
    set(${_var} "bin_${CMAKE_BUILD_TYPE}_qt${QT_VERSION}_${_CXX_COMPILER_ID}_${_platform_name}" PARENT_SCOPE)
endfunction()



# 定义FC_LIB的宏
# _lib_name lib的名字，决定变量FC_LIB_NAME
# _lib_description lib的描述，决定变量FC_LIB_DESCRIPTION
# _lib_ver_major lib的主版本号，决定变量FC_LIB_VERSION_MAJOR
# _lib_ver_minor lib的次版本号，决定变量FC_LIB_VERSION_MINOR
# _lib_ver_path lib的末版本号，决定变量FC_LIB_VERSION_PATCH
# 生成：FC_LIB_VERSION，完整的版本名
# 生成：FC_LIB_FULL_DESCRIPTION，完整的描述
# 生成：FC_MIN_QT_VERSION 最低qt版本要求
macro(fcmacro_lib_setting _lib_name _lib_description _lib_ver_major _lib_ver_minor _lib_ver_path)
    set(FC_MIN_QT_VERSION 5.14)
    set(FC_LIB_NAME ${_lib_name})
    set(FC_LIB_DESCRIPTION ${_lib_description})
    set(FC_LIB_VERSION_MAJOR ${_lib_ver_major})
    set(FC_LIB_VERSION_MINOR ${_lib_ver_minor})
    set(FC_LIB_VERSION_PATCH ${_lib_ver_path})
    set(FC_LIB_VERSION "${FC_LIB_VERSION_MAJOR}.${FC_LIB_VERSION_MINOR}.${FC_LIB_VERSION_PATCH}")
    set(FC_LIB_FULL_DESCRIPTION "${FC_PROJECT_NAME}::${FC_LIB_NAME} ${FC_LIB_VERSION} | ${FC_LIB_DESCRIPTION}")

    project(${FC_LIB_NAME}
        VERSION ${FC_LIB_VERSION}
        LANGUAGES CXX
        DESCRIPTION ${FC_LIB_FULL_DESCRIPTION}
    )
    ########################################################
    # 通用常规设置
    ########################################################
    # C++标准要求最低C++17
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
        endif(MSVC)
    # 编译选项
    set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
    set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    set(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    ########################################################
    # MSVC设置
    ########################################################
    if(MSVC)
    # msvc utf-8
        add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
        add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    endif()
    ########################################################
    # 目录包含
    ########################################################
    # 包含自身目录
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # 默认的CMAKE_INSTALL_PREFIX
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../../${FC_BIN_DIR_NAME}")
    set(FC_GLOBAL_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/../FCGlobals.h)
    # FCShared目录
    set(FC_SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../FCShared)
    set(${FC_PROJECT_NAME}_DIR "${CMAKE_BINARY_DIR}")
    ########################################################
    # 打印信息
    ########################################################
    message("")
    message("${FC_LIB_FULL_DESCRIPTION}")
    message(STATUS "  | => FC_LIB_NAME=${FC_LIB_NAME}")
    message(STATUS "  | => FC_GLOBAL_HEADER=${FC_GLOBAL_HEADER}")
    message(STATUS "  | => FC_SHARED_DIR=${FC_SHARED_DIR}")
    message(STATUS "  | => CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
    message(STATUS "  | => CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
    message(STATUS "  | => CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
endmacro(fcmacro_lib_setting)

macro(fcmacro_set_lib_properties _target_name _version_str)
    set_target_properties(${_target_name} PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
        CXX_EXTENSIONS OFF
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
        VERSION ${_version_str}
        EXPORT_NAME ${_target_name}
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endmacro(fcmacro_set_lib_properties)

macro(fcmacro_set_app_properties _target_name _version_str)
    if(${QT_VERSION} VERSION_LESS 6.1.0)
      set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${_target_name})
    endif()
    set_target_properties(${_target_name} PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
        WIN32_EXECUTABLE TRUE
        CXX_EXTENSIONS OFF
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
        VERSION ${_version_str}
        EXPORT_NAME ${_target_name}
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
    if(MSVC)
        target_compile_options(${_target_name} PRIVATE "/utf-8")
        target_compile_definitions(${_target_name} PRIVATE "_UNICODE" "UNICODE")
        # 为 MSVC 设置链接器标志以禁止生成清单文件
        # 这是因为某些操作系统下会遇到general error c101008d: Failed to write the updated manifest to the resource of file "bin\DAWorkBench.exe的错误
        # 主要是操作系统杀毒软件的原因，某些生产环节下是无法禁用杀毒软件的
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
    endif()
endmacro(fcmacro_set_app_properties)

# 通用的安装
macro(fcmacro_lib_install_no_rc)
    include(GNUInstallDirs)
    target_compile_definitions(${FC_LIB_NAME} PRIVATE QT_MESSAGELOGCONTEXT)
    ######################################################
    # 目标依赖目录
    ########################################################
    target_include_directories(${FC_LIB_NAME} PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${FC_PROJECT_NAME}/${FC_LIB_NAME}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    )
    # 这个主要是FCGlobal.h
    target_include_directories(${FC_LIB_NAME} PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${FC_PROJECT_NAME}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
    )
    # 这个主要是FCShared
    target_include_directories(${FC_LIB_NAME} PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${FC_PROJECT_NAME}/FCShared>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../FCShared>
    )
    # FCConfig.cmake.in中，会让此变量和“${PACKAGE_PREFIX_DIR}/”进行拼接，也就是${PACKAGE_PREFIX_DIR}/@FC_LIB_INCLUDE_INSTALL_DIR@
    # PACKAGE_PREFIX_DIR = ${CMAKE_CURRENT_LIST_DIR}/../..
    # 最终变为${CMAKE_CURRENT_LIST_DIR}/../../include/${FC_PROJECT_NAME}/${FC_LIB_NAME}
    set(FC_LIB_INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${FC_PROJECT_NAME}/${FC_LIB_NAME})

    include(CMakePackageConfigHelpers)
    # Generate library version info which will generate xxxConfigVersion.cmake,
    # the ${PACKAGE_VERSION} is the version defined in project()
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${FC_LIB_NAME}ConfigVersion.cmake
        VERSION ${FC_LIB_VERSION}
        COMPATIBILITY SameMajorVersion
    )
    configure_package_config_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/../FCLibConfig.cmake.in"
      "${CMAKE_CURRENT_BINARY_DIR}/${FC_LIB_NAME}Config.cmake"
      INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${FC_PROJECT_NAME}
      PATH_VARS FC_LIB_INCLUDE_INSTALL_DIR
    )
    # 声明导出target的名称
    install(TARGETS ${FC_LIB_NAME}
        EXPORT ${FC_LIB_NAME}Targets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${FC_PROJECT_NAME}/${FC_LIB_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
    install(EXPORT "${FC_LIB_NAME}Targets"
        FILE ${FC_LIB_NAME}Targets.cmake # 导出的文件基准名。
        NAMESPACE ${FC_PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${FC_PROJECT_NAME}
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${FC_LIB_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${FC_LIB_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${FC_PROJECT_NAME}
    )

    export(EXPORT ${FC_LIB_NAME}Targets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/${FC_LIB_NAME}Targets.cmake
       NAMESPACE ${FC_PROJECT_NAME}::
    )
    message(STATUS "${FC_LIB_NAME} install dir is : ${CMAKE_INSTALL_PREFIX}")
endmacro(fcmacro_lib_install_no_rc)

# 通用的安装
macro(fcmacro_lib_install)
    ########################################################
    # dll资源信息添加到 target_sources中
    ########################################################
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/create_win32_resource_version.cmake)
    if(WIN32)
            create_win32_resource_version(
                    TARGET ${FC_LIB_NAME}
                    FILENAME ${FC_LIB_NAME}
                    VERSION ${FC_LIB_VERSION}
                    EXT "dll"
                    DESCRIPTION ${FC_LIB_DESCRIPTION}
            )

            # set(__rc_path "${CMAKE_CURRENT_BINARY_DIR}/${FC_LIB_NAME}.rc")
            # if(NOT EXISTS "${__rc_path}")
            #     generate_win32_rc_file(
            #         PATH "${__rc_path}"
            #         VERSION "${FC_LIB_VERSION}"
            #         COMPANY "czy"
            #         DESCRIPTION "${FC_LIB_DESCRIPTION}"
            #         COPYRIGHT "LGPL License"
            #         PRODUCT "${FC_LIB_NAME}"
            #     )
            # endif()
            # target_sources(${FC_LIB_NAME} PRIVATE "${__rc_path}")
    endif()
    fcmacro_lib_install_no_rc()
endmacro(fcmacro_lib_install)



# 定义FC_APP的宏
# _app_name lib的名字，决定变量FC_APP_NAME
# _app_description lib的描述，决定变量FC_APP_DESCRIPTION
# _app_ver_major lib的主版本号，决定变量FC_APP_VERSION_MAJOR
# _app_ver_minor lib的次版本号，决定变量FC_APP_VERSION_MINOR
# _app_ver_path lib的末版本号，决定变量FC_APP_VERSION_PATCH
# 生成：FC_APP_VERSION，完整的版本名
# 生成：FC_APP_FULL_DESCRIPTION，完整的描述
# 生成：FC_MIN_QT_VERSION 最低qt版本要求
macro(fcmacro_app_setting _app_name _app_description _app_ver_major _app_ver_minor _app_ver_path)
    set(FC_MIN_QT_VERSION 5.14)
    set(FC_APP_NAME ${_app_name})
    set(FC_APP_DESCRIPTION ${_app_description})
    set(FC_APP_VERSION_MAJOR ${_app_ver_major})
    set(FC_APP_VERSION_MINOR ${_app_ver_minor})
    set(FC_APP_VERSION_PATCH ${_app_ver_path})
    set(FC_APP_VERSION "${FC_APP_VERSION_MAJOR}.${FC_APP_VERSION_MINOR}.${FC_APP_VERSION_PATCH}")
    set(FC_APP_FULL_DESCRIPTION "${FC_APP_DESCRIPTION}")

    project(${FC_APP_NAME}
        VERSION ${FC_APP_VERSION}
        LANGUAGES CXX
        DESCRIPTION ${FC_APP_NAME}
        HOMEPAGE_URL "https://github.com/kinvy66"
    )
    ########################################################
    # 通用常规设置
    ########################################################
    # C++标准要求最低C++17
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    # 编译选项
    set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
    set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    set(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    ########################################################
    # MSVC设置
    ########################################################
    if(MSVC)
    # msvc utf-8
        add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
        add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    endif()
    ########################################################
    # 目录包含
    ########################################################
    # 包含自身目录
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # 默认的CMAKE_INSTALL_PREFIX
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../../${FC_BIN_DIR_NAME}")
    set(FC_GLOBAL_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/../FCGlobals.h)
    set(${FC_PROJECT_NAME}_DIR "${CMAKE_BINARY_DIR}")
    ########################################################
    # 打印信息
    ########################################################
    message("")
    message("${FC_APP_FULL_DESCRIPTION}")
    message(STATUS "  | => FC_APP_NAME=${FC_APP_NAME}")
    message(STATUS "  | => FC_GLOBAL_HEADER=${FC_GLOBAL_HEADER}")
    message(STATUS "  | => CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
    message(STATUS "  | => CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
    message(STATUS "  | => CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")
endmacro(fcmacro_app_setting)

# 通用的安装
macro(fcmacro_app_install)
    ########################################################
    # 目标依赖目录
    ########################################################
    # 声明导出target的名称
    install(TARGETS ${FC_APP_NAME} RUNTIME DESTINATION bin)
    message(STATUS "${FC_APP_NAME} install dir is : ${CMAKE_INSTALL_PREFIX}")
endmacro(fcmacro_app_install)

