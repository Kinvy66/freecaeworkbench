#
# 这个宏是一个通用的模块引入
# find_package(x_packagename)
# target_link_libraries(__target_name x_namespace::x_libname)
#
macro(fcmacro_import_xxx x_packagename x_namespace x_libname __target_name)
    find_package(${x_packagename})
    if(${x_packagename}_FOUND)
        message(STATUS "  |-finded ${x_packagename}")
    else()
        message(STATUS "  |-can not find ${x_packagename}")
        if(DEFINED FC_INSTALL_LIB_CMAKE_PATH)
            file(GLOB _lib_candidate_dirs
                LIST_DIRECTORIES true
                ${FC_INSTALL_LIB_CMAKE_PATH}/${x_packagename}*
            )
            # 检查是否存在匹配项
            if(NOT _lib_candidate_dirs)
                message(FATAL_ERROR "No ${x_packagename} like directories found in: ${FC_INSTALL_LIB_CMAKE_PATH}")
            endif()
            #若存在多个版本，可以通过排序选择最新路径：
            list(SORT _lib_candidate_dirs)
            list(REVERSE _lib_candidate_dirs)  # 按字母逆序排列（假设版本号递增）
            list(GET _lib_candidate_dirs 0 _lib_candidate_dirs)  # 取第一个（最新）
            message(STATUS "  |-try to find in ${_lib_candidate_dirs}")
            find_package(${x_packagename} PATHS ${_lib_candidate_dirs})
        endif()
    endif()
    # 链接的第三方库
    if(${x_packagename}_FOUND)
        target_link_libraries(${__target_name} PRIVATE
            ${x_namespace}::${x_libname}
        )
        message(STATUS "  |-link ${x_namespace}::${x_libname}")
    else()
        message(FATAL_ERROR "  can not find ${x_libname}")
    endif()
endmacro(fcmacro_import_xxx)

#
# 这个宏针对libname和package一样的模块引入
# 例如
# find_package(x_libname)
# target_link_libraries(__target_name x_namespace::x_libname)
#
macro(fcmacro_import_xx x_namespace x_libname __target_name)
    fcmacro_import_xxx(${x_libname} ${x_namespace} ${x_libname} ${__target_name})
endmacro(fcmacro_import_xx)

# 这个宏是引入share/cmake目录的库，例如tsl-ordered-map
macro(fcmacro_import_xx_sharepath x_namespace x_libname __target_name)
    find_package(${x_libname})
    if(${x_libname}_FOUND)
        message(STATUS "  |-finded ${x_libname}")
    else()
        message(STATUS "  |-can not find ${x_libname}")
        if(DEFINED FC_INSTALL_LIB_SHARE_PATH)
            set(_lib_dir ${FC_INSTALL_LIB_SHARE_PATH}/${x_libname})
            message(STATUS "  |-try to find in ${_lib_dir}")
            find_package(${x_libname} PATHS ${_lib_dir})
        endif()
    endif()
    # 链接的第三方库
    if(${x_libname}_FOUND)
        target_link_libraries(${__target_name} PRIVATE
            ${x_namespace}::${x_libname}
        )
        message(STATUS "  |-link ${x_namespace}::${x_libname}")
    else()
        message(FATAL_ERROR "  can not find ${x_libname}")
    endif()
endmacro(fcmacro_import_xx_sharepath)

#
# 这个宏针对libname和namespace一样的模块引入
# 例如
# find_package(x_libname)
# target_link_libraries(__target_name x_libname::x_libname)
#
macro(fcmacro_import_x x_libname __target_name)
    fcmacro_import_xx(${x_libname} ${x_libname} ${__target_name})
endmacro(fcmacro_import_x)

# fcmacro_import_SARibbonBar(${FC_LIB_NAME})
#macro(fcmacro_import_SARibbonBar __target_name)
#    find_package(SARibbonBar)
#    if(SARibbonBar_FOUND)
#        message(STATUS "  |-finded SARibbonBar")
#        message(STATUS "  | |-include dir:${SARibbonBar_INCLUDE_DIR}")
#    else()
#        message(STATUS "  |-can not find SARibbonBar")
#        if(DEFINED DA_INSTALL_LIB_CMAKE_PATH)
#            set(_lib_dir ${DA_INSTALL_LIB_CMAKE_PATH}/SARibbonBar)
#            message(STATUS "  |-try to find in ${_lib_dir}")
#            find_package(SARibbonBar PATHS ${_lib_dir})
#        endif()
#    endif()
#    # 链接的第三方库
#    if(SARibbonBar_FOUND)
#        target_link_libraries(${__target_name} PRIVATE
#            SARibbonBar::SARibbonBar
#        )
#        message(STATUS "  |-link SARibbonBar::SARibbonBar")
#    else()
#        message(ERROR "  can not find SARibbonBar")
#    endif()
#endmacro(fcmacro_import_SARibbonBar)

macro(fcmacro_import_SARibbonBar __target_name)
    fcmacro_import_x(SARibbonBar ${__target_name})
endmacro(fcmacro_import_SARibbonBar)


macro(fcmacro_import_QtAdvancedDocking __target_name)
    set(_lib_name qtadvanceddocking-qt${QT_VERSION_MAJOR})
    fcmacro_import_xx(ads ${_lib_name} ${__target_name})
endmacro(fcmacro_import_QtAdvancedDocking)

macro(fcmacro_import_qwt __target_name)
    fcmacro_import_x(qwt ${__target_name})
endmacro(fcmacro_import_qwt)

macro(fcmacro_import_spdlog __target_name)
    fcmacro_import_x(spdlog ${__target_name})
endmacro(fcmacro_import_spdlog)

macro(fcmacro_import_quazip __target_name)
    set(_package_name QuaZip-Qt${QT_VERSION_MAJOR})
    fcmacro_import_xxx(${_package_name} QuaZip QuaZip ${__target_name})
endmacro(fcmacro_import_quazip)

macro(fcmacro_import_Python __target_name)
    # Python
    # https://zhuanlan.zhihu.com/p/666367728
    # https://blog.csdn.net/weixin_40448140/article/details/112005184
    # 如果使用的是非系统目录下的 Python 可以通过指定 Python3_ROOT_DIR 改变查找路径
    find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
    if(${Python3_FOUND})
        message(STATUS "  |-find python")
        message(STATUS "  | |-Python3_VERSION = ${Python3_VERSION}")
        message(STATUS "  | |-Python3_VERSION_MAJOR = ${Python3_VERSION_MAJOR}")
        message(STATUS "  | |-Python3_VERSION_MINOR = ${Python3_VERSION_MINOR}")
        message(STATUS "  | |-Python3_ROOT_DIR = ${Python3_ROOT_DIR}")
        message(STATUS "  | |-Python3_INCLUDE_DIRS = ${Python3_INCLUDE_DIRS}")
        message(STATUS "  | |-Python3_LIBRARY_DIRS = ${Python3_LIBRARY_DIRS}")
        message(STATUS "  | |-Python3_LIBRARY = ${Python3_LIBRARY}")
        message(STATUS "  | |-Python3_LIBRARIES = ${Python3_LIBRARIES}")
        message(STATUS "  | |-Python3_RUNTIME_LIBRARY_DIRS = ${Python3_RUNTIME_LIBRARY_DIRS}")
        message(STATUS "  | |-Python3_EXECUTABLE = ${Python3_EXECUTABLE}")
        message(STATUS "  | |-Python3_COMPILER = ${Python3_COMPILER}")
        message(STATUS "  | |-Python3_STDARCH = ${Python3_STDARCH}")
        message(STATUS "  | |-Python3_STDLIB = ${Python3_STDLIB}")
    endif()
    target_link_libraries(${__target_name} PRIVATE ${Python3_LIBRARIES})
    target_include_directories(${__target_name} PRIVATE ${Python3_INCLUDE_DIRS})
endmacro(fcmacro_import_Python)

macro(fcmacro_import_pybind11 __target_name)
    # pybind11
    # pybind11是header only
    if(DEFINED FC_SRC_DIR)
        set(_src_dir ${FC_SRC_DIR})
    else()
        set(_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/..)
    endif()
    target_include_directories(${FC_LIB_NAME} PUBLIC
        $<INSTALL_INTERFACE:include/pybind11>
        $<BUILD_INTERFACE:${_src_dir}/../3rdparty/pybind11/include>
    )
endmacro(fcmacro_import_pybind11)


