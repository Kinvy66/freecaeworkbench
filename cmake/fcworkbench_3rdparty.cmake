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
        # 优先从ThirdLib文件夹查找
        if(DEFINED FC_THIRDLIB_DIR)
            # 尝试从ThirdLib查找，根据库名映射到ThirdLib中的目录
            set(_thirdlib_search_paths)
            # 根据常见的库名映射
            if(${x_packagename} MATCHES "SARibbonBar")
                list(APPEND _thirdlib_search_paths ${FC_THIRDLIB_DIR}/SARibbon/lib/cmake/SARibbonBar)
            elseif(${x_packagename} MATCHES "QuaZip")
                list(APPEND _thirdlib_search_paths ${FC_THIRDLIB_DIR}/quazip/lib/cmake/QuaZip-Qt${QT_VERSION_MAJOR})
            elseif(${x_packagename} MATCHES "qtadvanceddocking")
                list(APPEND _thirdlib_search_paths ${FC_THIRDLIB_DIR}/QtADS/lib/cmake/qtadvanceddocking-qt${QT_VERSION_MAJOR})
            else()
                # 通用查找：在ThirdLib下查找匹配的目录
                file(GLOB _lib_candidate_dirs
                    LIST_DIRECTORIES true
                    ${FC_THIRDLIB_DIR}/*/lib/cmake/${x_packagename}*
                )
                list(APPEND _thirdlib_search_paths ${_lib_candidate_dirs})
            endif()
            # 尝试从ThirdLib查找
            foreach(_search_path IN LISTS _thirdlib_search_paths)
                if(EXISTS ${_search_path})
                    message(STATUS "  |-try to find in ${_search_path}")
                    find_package(${x_packagename} PATHS ${_search_path})
                    if(${x_packagename}_FOUND)
                        break()
                    endif()
                endif()
            endforeach()
        endif()
        # 如果ThirdLib中没找到，再从原来的安装路径查找
        if(NOT ${x_packagename}_FOUND AND DEFINED FC_INSTALL_LIB_CMAKE_PATH)
            file(GLOB _lib_candidate_dirs
                LIST_DIRECTORIES true
                ${FC_INSTALL_LIB_CMAKE_PATH}/${x_packagename}*
            )
            # 检查是否存在匹配项
            if(_lib_candidate_dirs)
                #若存在多个版本，可以通过排序选择最新路径：
                list(SORT _lib_candidate_dirs)
                list(REVERSE _lib_candidate_dirs)  # 按字母逆序排列（假设版本号递增）
                list(GET _lib_candidate_dirs 0 _lib_candidate_dirs)  # 取第一个（最新）
                message(STATUS "  |-try to find in ${_lib_candidate_dirs}")
                find_package(${x_packagename} PATHS ${_lib_candidate_dirs})
            endif()
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
        # 优先从ThirdLib文件夹查找
        if(DEFINED FC_THIRDLIB_DIR)
            file(GLOB _lib_candidate_dirs
                LIST_DIRECTORIES true
                ${FC_THIRDLIB_DIR}/*/share/cmake/${x_libname}
            )
            foreach(_search_path IN LISTS _lib_candidate_dirs)
                if(EXISTS ${_search_path})
                    message(STATUS "  |-try to find in ${_search_path}")
                    find_package(${x_libname} PATHS ${_search_path})
                    if(${x_libname}_FOUND)
                        break()
                    endif()
                endif()
            endforeach()
        endif()
        # 如果ThirdLib中没找到，再从原来的安装路径查找
        if(NOT ${x_libname}_FOUND AND DEFINED FC_INSTALL_LIB_SHARE_PATH)
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

# VTK
macro(fcmacro_import_vtk __target_name)
    find_package(VTK)
    if(VTK_FOUND)
        message(STATUS "  |-finded VTK")
        message(STATUS "  |-Found VTK version: ${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}.${VTK_BUILD_VERSION}")
    else()
        message(STATUS "  |-can not find VTK")
        # 优先从ThirdLib文件夹查找
        if(DEFINED FC_THIRDLIB_DIR)
            set(_lib_dir ${FC_THIRDLIB_DIR}/VTK/lib/cmake/vtk-9.4)
            if(EXISTS ${_lib_dir})
                message(STATUS "  |-try to find in ${_lib_dir}")
                find_package(VTK PATHS ${_lib_dir})
            endif()
        endif()
        # 如果ThirdLib中没找到，再从原来的安装路径查找
        if(NOT VTK_FOUND AND DEFINED FC_INSTALL_LIB_CMAKE_PATH)
            set(_lib_dir ${FC_INSTALL_LIB_CMAKE_PATH}/vtk-9.4)
            message(STATUS "  |-try to find in ${_lib_dir}")
            find_package(VTK PATHS ${_lib_dir})
        endif()
    endif()
    # 链接的第三方库
    if(VTK_FOUND)
        target_link_libraries(${__target_name} PRIVATE
            ${VTK_LIBRARIES}
        )
        message(STATUS "  |-link ${VTK_LIBRARIES}")
    else()
        message(ERROR "  can not find VTK")
    endif()
endmacro(fcmacro_import_vtk)


#-----------------------------------------
# fcmacro_import_occ
# 完全通用版本：支持 Debug/Release
# 参数：
#   __target_name - 要链接 OpenCASCADE 的目标
# 前提：
#   优先从ThirdLib/OCC查找，如果没有则使用FC_OCC_INSTALL_LIB_CMAKE_PATH
#-----------------------------------------
macro(fcmacro_import_occ __target_name)
    # 优先从ThirdLib查找
    if(DEFINED FC_THIRDLIB_DIR)
        set(_occ_cmake_path ${FC_THIRDLIB_DIR}/OCC/cmake)
        if(EXISTS ${_occ_cmake_path})
            set(FC_OCC_INSTALL_LIB_CMAKE_PATH ${_occ_cmake_path})
        endif()
    endif()
    
    if(NOT DEFINED FC_OCC_INSTALL_LIB_CMAKE_PATH)
        message(FATAL_ERROR "FC_OCC_INSTALL_LIB_CMAKE_PATH is not defined. Set it to your OpenCASCADE install cmake path.")
    endif()

    # 设置 OpenCASCADE_DIR，保证 Multi-Config 构建正确
    set(OpenCASCADE_DIR "${FC_OCC_INSTALL_LIB_CMAKE_PATH}" CACHE PATH "Path to OpenCASCADE CMake config" FORCE)
    message(STATUS "  |-Searching OpenCASCADE in: ${OpenCASCADE_DIR}")

    # 使用 CONFIG 模式查找
    find_package(OpenCASCADE REQUIRED CONFIG)

    # 输出信息
    message(STATUS "  |-Found OpenCASCADE version: ${OpenCASCADE_VERSION}")
    message(STATUS "  |-OpenCASCADE include dirs: ${OpenCASCADE_INCLUDE_DIRS}")
    message(STATUS "  |-OpenCASCADE libraries: ${OpenCASCADE_LIBRARIES}")

    # 链接库
    target_link_libraries(${__target_name} PRIVATE ${OpenCASCADE_LIBRARIES})

    # 包含头文件（可选，如果 OpenCASCADE_INCLUDE_DIRS 没自动添加）
    if(DEFINED OpenCASCADE_INCLUDE_DIRS)
        target_include_directories(${__target_name} PRIVATE ${OpenCASCADE_INCLUDE_DIRS})
    endif()
endmacro()

# Gmsh
macro(fcmacro_import_gmsh __target_name)
    find_package(gmsh)
    if(gmsh_FOUND)
        message(STATUS "  |-finded Gmsh")
        message(STATUS "  |-Found Gmsh version: ${PACKAGE_VERSION}")
    else()
        message(STATUS "  |-can not find Gmsh")
        # 优先从ThirdLib文件夹查找
        if(DEFINED FC_THIRDLIB_DIR)
            set(_lib_dir ${FC_THIRDLIB_DIR}/Gmsh/share/gmsh)
            if(EXISTS ${_lib_dir})
                message(STATUS "  |-try to find in ${_lib_dir}")
                find_package(gmsh PATHS ${_lib_dir})
            endif()
        endif()
        # 如果ThirdLib中没找到，再从原来的安装路径查找
        if(NOT gmsh_FOUND AND DEFINED FC_GMSH_INSTALL_LIB_CMAKE_PATH)
            set(_lib_dir ${FC_GMSH_INSTALL_LIB_CMAKE_PATH})
            message(STATUS "  |-try to find in ${_lib_dir}")
            find_package(gmsh PATHS ${_lib_dir})
        endif()
    endif()
    # 链接的第三方库
    if(gmsh_FOUND)
        target_link_libraries(${__target_name} PRIVATE
            gmsh::shared
        )
        message(STATUS "  |-link gmsh::shared")
    else()
        message(ERROR "  can not find gmsh")
    endif()
endmacro(fcmacro_import_gmsh)


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


