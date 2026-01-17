# 拷贝第三方库DLL到构建目录
# 用于在构建时将依赖的DLL拷贝到build/bin目录下

########################################################
# 拷贝Qt DLL到目标目录（使用windeployqt）
# 参数：
#   _target_exe - 目标可执行文件路径
#   _target_dir - 目标目录（通常是bin目录）
#   _windeployqt_exe - windeployqt可执行文件路径
########################################################
function(fcfun_copy_qt_dlls _target_exe _target_dir _windeployqt_exe)
    if(NOT WIN32)
        return()
    endif()
    
    # 使用传入的windeployqt路径
    if(NOT DEFINED _windeployqt_exe OR _windeployqt_exe STREQUAL "")
        message(WARNING "windeployqt path not provided, skipping Qt DLL copy")
        return()
    endif()
    
    # 去除可能的引号
    string(STRIP ${_windeployqt_exe} _windeployqt_exe)
    string(REGEX REPLACE "^\"(.*)\"$" "\\1" _windeployqt_exe "${_windeployqt_exe}")
    
    if(NOT EXISTS ${_windeployqt_exe})
        message(WARNING "windeployqt.exe not found at ${_windeployqt_exe}")
        message(STATUS "Checking if file exists (raw path): ${_windeployqt_exe}")
        return()
    endif()
    
    # 执行windeployqt
    # 使用--dir参数指定输出目录，--verbose 0 减少输出
    execute_process(
        COMMAND ${_windeployqt_exe} --dir ${_target_dir} --verbose 0 ${_target_exe}
        RESULT_VARIABLE _result
        OUTPUT_QUIET
        ERROR_QUIET
    )
    
    if(_result EQUAL 0)
        message(STATUS "Qt DLLs deployed successfully using windeployqt")
    else()
        message(WARNING "windeployqt failed with result ${_result}")
    endif()
endfunction()

########################################################
# 拷贝第三方库DLL到目标目录
# 参数：
#   _target_dir - 目标目录（通常是bin目录）
#   _build_type - 构建类型（Debug或Release）
########################################################
function(fcfun_copy_thirdlib_dlls _target_dir _build_type)
    if(NOT WIN32)
        return()
    endif()
    
    # 确定是debug还是release版本
    set(_is_debug FALSE)
    if(_build_type STREQUAL "Debug" OR _build_type MATCHES "Debug")
        set(_is_debug TRUE)
    endif()
    
    # 第三方库目录
    # 优先使用传入的FC_THIRDLIB_DIR，否则使用CMAKE_SOURCE_DIR
    if(DEFINED FC_THIRDLIB_DIR AND NOT FC_THIRDLIB_DIR STREQUAL "")
        set(_thirdlib_dir ${FC_THIRDLIB_DIR})
    elseif(DEFINED CMAKE_SOURCE_DIR AND NOT CMAKE_SOURCE_DIR STREQUAL "")
        set(_thirdlib_dir "${CMAKE_SOURCE_DIR}/ThirdLib")
    else()
        message(WARNING "FC_THIRDLIB_DIR and CMAKE_SOURCE_DIR not defined, skipping DLL copy")
        return()
    endif()
    
    # 转换为绝对路径
    get_filename_component(_thirdlib_dir ${_thirdlib_dir} ABSOLUTE)
    
    if(NOT EXISTS ${_thirdlib_dir})
        message(WARNING "ThirdLib directory not found: ${_thirdlib_dir}")
        return()
    endif()
    
    # 统计拷贝的文件数量
    set(_copied_count 0)
    
    # 获取ThirdLib目录下所有子目录
    file(GLOB _lib_dirs "${_thirdlib_dir}/*")
    
    # 遍历每个库目录
    foreach(_lib_dir IN LISTS _lib_dirs)
        # 只处理目录
        if(NOT IS_DIRECTORY ${_lib_dir})
            continue()
        endif()
        
        # 获取库名称
        get_filename_component(_lib_name ${_lib_dir} NAME)
        
        # 跳过一些不需要处理的目录（如pybind11只有头文件）
        if(_lib_name STREQUAL "pybind11")
            continue()
        endif()
        
        # 特殊处理：Gmsh - DLL在lib目录，不区分debug和release
        if(_lib_name STREQUAL "Gmsh")
            set(_gmsh_lib_dir "${_lib_dir}/lib")
            if(EXISTS ${_gmsh_lib_dir})
                file(GLOB _dll_files "${_gmsh_lib_dir}/*.dll")
                foreach(_dll IN LISTS _dll_files)
                    file(COPY ${_dll} DESTINATION ${_target_dir})
                    math(EXPR _copied_count "${_copied_count} + 1")
                endforeach()
                if(_dll_files)
                    message(STATUS "Copied Gmsh DLLs (all versions) from ${_gmsh_lib_dir}")
                endif()
            endif()
            continue()
        endif()
        
        # 特殊处理：freeimage 和 freetype - 不区分debug和release，拷贝所有DLL
        if(_lib_name STREQUAL "freeimage" OR _lib_name STREQUAL "freetype")
            set(_lib_bin_dir "${_lib_dir}/bin")
            if(EXISTS ${_lib_bin_dir})
                file(GLOB _dll_files "${_lib_bin_dir}/*.dll")
                foreach(_dll IN LISTS _dll_files)
                    file(COPY ${_dll} DESTINATION ${_target_dir})
                    math(EXPR _copied_count "${_copied_count} + 1")
                endforeach()
                if(_dll_files)
                    message(STATUS "Copied ${_lib_name} DLLs (all versions) from ${_lib_bin_dir}")
                endif()
            endif()
            continue()
        endif()
        
        # 特殊处理：OCC - 有bind（debug）和bin（release）的区别，需要拷贝所有DLL
        if(_lib_name STREQUAL "OCC")
            # 尝试多个可能的路径
            set(_occ_bin_dirs)
            if(_is_debug)
                # Debug版本：从bind目录拷贝所有DLL
                list(APPEND _occ_bin_dirs "${_lib_dir}/win64/vc14/bind")
                list(APPEND _occ_bin_dirs "${_lib_dir}/bind")
            else()
                # Release版本：从bin目录拷贝所有DLL
                list(APPEND _occ_bin_dirs "${_lib_dir}/win64/vc14/bin")
                list(APPEND _occ_bin_dirs "${_lib_dir}/bin")
            endif()
            
            foreach(_occ_bin_dir IN LISTS _occ_bin_dirs)
                if(EXISTS ${_occ_bin_dir})
                    # 拷贝所有DLL，不做任何过滤
                    file(GLOB _occ_dll_files "${_occ_bin_dir}/*.dll")
                    foreach(_dll IN LISTS _occ_dll_files)
                        file(COPY ${_dll} DESTINATION ${_target_dir})
                        math(EXPR _copied_count "${_copied_count} + 1")
                    endforeach()
                    if(_occ_dll_files)
                        message(STATUS "Copied OCC DLLs from ${_occ_bin_dir}")
                    endif()
                    break()
                endif()
            endforeach()
            continue()
        endif()
        
        # 特殊处理：VTK - 需要拷贝所有DLL（包括debug和release版本）
        if(_lib_name STREQUAL "VTK")
            set(_vtk_bin_dir "${_lib_dir}/bin")
            if(EXISTS ${_vtk_bin_dir})
                if(_is_debug)
                    # Debug版本：拷贝所有带d后缀的dll
                    file(GLOB _dll_files "${_vtk_bin_dir}/*d.dll")
                else()
                    # Release版本：拷贝所有不带d后缀的dll
                    file(GLOB _all_dll_files "${_vtk_bin_dir}/*.dll")
                    set(_dll_files)
                    foreach(_dll IN LISTS _all_dll_files)
                        get_filename_component(_dll_name ${_dll} NAME)
                        # 排除带d后缀的dll
                        if(NOT _dll_name MATCHES "d\\.dll$")
                            list(APPEND _dll_files ${_dll})
                        endif()
                    endforeach()
                endif()
                
                # 拷贝DLL文件
                foreach(_dll IN LISTS _dll_files)
                    file(COPY ${_dll} DESTINATION ${_target_dir})
                    math(EXPR _copied_count "${_copied_count} + 1")
                endforeach()
                
                if(_dll_files)
                    message(STATUS "Copied VTK DLLs from ${_vtk_bin_dir}")
                endif()
            endif()
            continue()
        endif()
        
        # 其他库：从bin目录拷贝，根据debug/release区分
        set(_lib_bin_dir "${_lib_dir}/bin")
        if(EXISTS ${_lib_bin_dir})
            if(_is_debug)
                # Debug版本：只拷贝带d后缀的dll
                file(GLOB _dll_files "${_lib_bin_dir}/*d.dll")
            else()
                # Release版本：拷贝不带d后缀的dll
                file(GLOB _all_dll_files "${_lib_bin_dir}/*.dll")
                set(_dll_files)
                foreach(_dll IN LISTS _all_dll_files)
                    get_filename_component(_dll_name ${_dll} NAME)
                    # 排除带d后缀的dll
                    if(NOT _dll_name MATCHES "d\\.dll$")
                        list(APPEND _dll_files ${_dll})
                    endif()
                endforeach()
            endif()
            
            # 拷贝DLL文件
            foreach(_dll IN LISTS _dll_files)
                file(COPY ${_dll} DESTINATION ${_target_dir})
                math(EXPR _copied_count "${_copied_count} + 1")
            endforeach()
            
            if(_dll_files)
                message(STATUS "Copied ${_lib_name} DLLs from ${_lib_bin_dir}")
            endif()
        endif()
    endforeach()
    
    # 输出拷贝成功信息
    if(_copied_count GREATER 0)
        message(STATUS "Copied ${_copied_count} third-party DLL(s) to ${_target_dir}")
    else()
        message(STATUS "No third-party DLLs copied to ${_target_dir}")
    endif()
endfunction()

########################################################
# 拷贝所有依赖DLL到构建目录
# 参数：
#   _target_name - 目标名称（通常是可执行文件名）
#   _build_type - 构建类型（Debug或Release）
#   _windeployqt_exe - windeployqt可执行文件路径（可选，可通过ARGV2传递）
########################################################
function(fcfun_copy_all_dlls_to_build _target_name _build_type)
    if(NOT WIN32)
        return()
    endif()
    
    # 确定bin目录（构建目录下的bin）
    set(_bin_dir "${CMAKE_BINARY_DIR}/bin")
    
    # 确保目录存在
    file(MAKE_DIRECTORY ${_bin_dir})
    
    # 首先执行windeployqt（如果提供了windeployqt路径）
    set(_target_exe "${_bin_dir}/${_target_name}.exe")
    if(EXISTS ${_target_exe})
        # 尝试从参数中获取windeployqt路径（第三个参数）
        set(_windeployqt_exe "")
        if(ARGC GREATER 2)
            set(_windeployqt_exe ${ARGV2})
        endif()
        
        # 如果提供了windeployqt路径，执行windeployqt
        if(_windeployqt_exe AND NOT _windeployqt_exe STREQUAL "")
            fcfun_copy_qt_dlls(${_target_exe} ${_bin_dir} ${_windeployqt_exe})
        else()
            message(STATUS "windeployqt path not provided, skipping Qt DLL deployment")
        endif()
    else()
        message(WARNING "Target executable not found: ${_target_exe}, skipping windeployqt")
    endif()
    
    # 然后拷贝第三方库DLL
    fcfun_copy_thirdlib_dlls(${_bin_dir} ${_build_type})
endfunction()

########################################################
# 脚本模式：当通过 cmake -P 运行时执行
# 用于构建后自动执行DLL拷贝
########################################################
if(DEFINED _TARGET_NAME AND DEFINED _BUILD_TYPE)
    # 脚本模式运行
    if(NOT WIN32)
        message(STATUS "DLL deployment is only supported on Windows")
        return()
    endif()
    
    # 设置第三方库目录（如果通过参数传入）
    if(DEFINED _FC_THIRDLIB_DIR)
        set(FC_THIRDLIB_DIR ${_FC_THIRDLIB_DIR})
    endif()
    
    # 确定bin目录
    if(DEFINED _CMAKE_BINARY_DIR)
        set(_bin_dir "${_CMAKE_BINARY_DIR}/bin")
    else()
        message(FATAL_ERROR "_CMAKE_BINARY_DIR not defined")
    endif()
    
    # 确保目录存在
    file(MAKE_DIRECTORY ${_bin_dir})
    
    # 首先执行windeployqt（如果提供了windeployqt路径）
    # 优先使用传入的可执行文件路径，否则尝试构建路径
    set(_target_exe "")
    if(DEFINED _TARGET_EXE AND NOT _TARGET_EXE STREQUAL "")
        # 去掉可能的引号
        string(STRIP ${_TARGET_EXE} _target_exe)
        string(REGEX REPLACE "^\"(.*)\"$" "\\1" _target_exe "${_target_exe}")
    endif()
    
    # 如果还是没有找到，尝试查找可执行文件，考虑 debug 后缀
    if(_target_exe STREQUAL "" OR NOT EXISTS ${_target_exe})
        set(_is_debug FALSE)
        if(_BUILD_TYPE STREQUAL "Debug" OR _BUILD_TYPE MATCHES "Debug")
            set(_is_debug TRUE)
        endif()
        
        # 先尝试带后缀的（debug 版本）
        if(_is_debug)
            set(_target_exe "${_bin_dir}/${_TARGET_NAME}d.exe")
            if(NOT EXISTS ${_target_exe})
                # 如果找不到带 d 的，尝试不带后缀的
                set(_target_exe "${_bin_dir}/${_TARGET_NAME}.exe")
            endif()
        else()
            # Release 版本，不带后缀
            set(_target_exe "${_bin_dir}/${_TARGET_NAME}.exe")
        endif()
    endif()
    
    # 检查可执行文件是否存在，如果不存在则等待一小段时间
    # 在 POST_BUILD 阶段，文件可能还在写入中
    if(NOT EXISTS ${_target_exe})
        # 等待最多5秒，每0.5秒检查一次
        set(_wait_count 0)
        while(NOT EXISTS ${_target_exe} AND _wait_count LESS 10)
            execute_process(COMMAND ${CMAKE_COMMAND} -E sleep 0.5 RESULT_VARIABLE _sleep_result)
            math(EXPR _wait_count "${_wait_count} + 1")
        endwhile()
    endif()
    
    if(EXISTS ${_target_exe})
        if(DEFINED _WINDEPLOYQT_EXE AND NOT _WINDEPLOYQT_EXE STREQUAL "")
            message(STATUS "Found target executable: ${_target_exe}")
            # 去除 windeployqt 路径中可能的引号
            string(STRIP ${_WINDEPLOYQT_EXE} _windeployqt_clean)
            string(REGEX REPLACE "^\"(.*)\"$" "\\1" _windeployqt_clean "${_windeployqt_clean}")
            fcfun_copy_qt_dlls(${_target_exe} ${_bin_dir} ${_windeployqt_clean})
        else()
            message(STATUS "windeployqt path not provided, skipping Qt DLL deployment")
        endif()
    else()
        message(WARNING "Target executable not found: ${_target_exe}, skipping windeployqt")
        message(STATUS "Searched for: ${_bin_dir}/${_TARGET_NAME}.exe and ${_bin_dir}/${_TARGET_NAME}d.exe")
        message(STATUS "Bin directory contents:")
        file(GLOB _bin_files "${_bin_dir}/*.exe")
        foreach(_file IN LISTS _bin_files)
            message(STATUS "  - ${_file}")
        endforeach()
    endif()
    
    # 然后拷贝第三方库DLL
    fcfun_copy_thirdlib_dlls(${_bin_dir} ${_BUILD_TYPE})
endif()
