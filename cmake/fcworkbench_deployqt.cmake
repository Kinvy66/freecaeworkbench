# 拷贝第三方库DLL到构建目录
# 用于在构建时将依赖的DLL拷贝到build/bin目录下

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
    if(_build_type STREQUAL "Debug" OR _build_type MATCHES "Debug")
        set(_dll_suffix "d")
    else()
        set(_dll_suffix "")
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
    
    # 需要拷贝的第三方库列表（从bin目录）
    set(_thirdlib_list
        SARibbon
        QtADS
        qwt
        VTK
        quazip
        spdlog
        zlib
    )
    
    # 拷贝每个第三方库的DLL（从bin目录）
    foreach(_lib IN LISTS _thirdlib_list)
        set(_lib_bin_dir "${_thirdlib_dir}/${_lib}/bin")
        if(EXISTS ${_lib_bin_dir})
            # 查找所有DLL文件
            if(_dll_suffix)
                # Debug版本：拷贝带d后缀的dll
                file(GLOB _dll_files "${_lib_bin_dir}/*${_dll_suffix}.dll")
            else()
                # Release版本：拷贝不带d后缀的dll，但要排除带d后缀的
                file(GLOB _all_dll_files "${_lib_bin_dir}/*.dll")
                set(_dll_files)
                foreach(_dll IN LISTS _all_dll_files)
                    get_filename_component(_dll_name ${_dll} NAME)
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
        endif()
    endforeach()
    
    # 特殊处理Gmsh库（DLL在lib目录，且没有debug/release后缀区分）
    set(_gmsh_lib_dir "${_thirdlib_dir}/Gmsh/lib")
    if(EXISTS ${_gmsh_lib_dir})
        # Gmsh的DLL没有debug/release后缀区分，直接拷贝所有dll
        file(GLOB _gmsh_dll_files "${_gmsh_lib_dir}/*.dll")
        foreach(_dll IN LISTS _gmsh_dll_files)
            file(COPY ${_dll} DESTINATION ${_target_dir})
            math(EXPR _copied_count "${_copied_count} + 1")
        endforeach()
    endif()
    
    # 特殊处理OCC库（可能在不同的目录结构）
    # Debug版本需要拷贝所有DLL（包括带d后缀和不带d后缀的）
    # Release版本只拷贝不带d后缀的DLL
    set(_occ_bin_dirs
        "${_thirdlib_dir}/OCC/win64/vc14/bin"
        "${_thirdlib_dir}/OCC/bin"
    )
    
    foreach(_occ_bin_dir IN LISTS _occ_bin_dirs)
        if(EXISTS ${_occ_bin_dir})
            if(_dll_suffix)
                # Debug版本：拷贝所有DLL（包括带d后缀和不带d后缀的）
                file(GLOB _occ_dll_files "${_occ_bin_dir}/*.dll")
            else()
                # Release版本：只拷贝不带d后缀的DLL
                file(GLOB _all_occ_dll_files "${_occ_bin_dir}/*.dll")
                set(_occ_dll_files)
                foreach(_dll IN LISTS _all_occ_dll_files)
                    get_filename_component(_dll_name ${_dll} NAME)
                    if(NOT _dll_name MATCHES "d\\.dll$")
                        list(APPEND _occ_dll_files ${_dll})
                    endif()
                endforeach()
            endif()
            
            foreach(_dll IN LISTS _occ_dll_files)
                file(COPY ${_dll} DESTINATION ${_target_dir})
                math(EXPR _copied_count "${_copied_count} + 1")
            endforeach()
            break()
        endif()
    endforeach()
    
    # 拷贝OCC的依赖库：freetype和freeimage
    # 这两个库没有区分debug和release版本，直接拷贝所有DLL
    # freetype DLL
    set(_freetype_bin_dir "${_thirdlib_dir}/freetype/bin")
    if(EXISTS ${_freetype_bin_dir})
        file(GLOB _freetype_dll_files "${_freetype_bin_dir}/*.dll")
        foreach(_dll IN LISTS _freetype_dll_files)
            file(COPY ${_dll} DESTINATION ${_target_dir})
            math(EXPR _copied_count "${_copied_count} + 1")
        endforeach()
    endif()
    
    # freeimage DLL
    set(_freeimage_bin_dir "${_thirdlib_dir}/freeimage/bin")
    if(EXISTS ${_freeimage_bin_dir})
        file(GLOB _freeimage_dll_files "${_freeimage_bin_dir}/*.dll")
        foreach(_dll IN LISTS _freeimage_dll_files)
            file(COPY ${_dll} DESTINATION ${_target_dir})
            math(EXPR _copied_count "${_copied_count} + 1")
        endforeach()
    endif()
    
    # 输出拷贝成功信息
    if(_copied_count GREATER 0)
        message(STATUS "Copied ${_copied_count} third-party DLL(s) to ${_target_dir}")
    endif()
endfunction()

########################################################
# 拷贝Qt DLL到目标目录
# 参数：
#   _target_exe - 目标可执行文件路径
#   _target_dir - 目标目录（通常是bin目录）
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
    
    if(NOT EXISTS ${_windeployqt_exe})
        message(WARNING "windeployqt.exe not found at ${_windeployqt_exe}")
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
        message(STATUS "Qt DLLs deployed successfully")
    else()
        message(WARNING "windeployqt failed with result ${_result}")
    endif()
endfunction()

########################################################
# 拷贝所有依赖DLL到构建目录
# 参数：
#   _target_name - 目标名称（通常是可执行文件名）
#   _build_type - 构建类型（Debug或Release）
########################################################
function(fcfun_copy_all_dlls_to_build _target_name _build_type)
    if(NOT WIN32)
        return()
    endif()
    
    # 确定bin目录（构建目录下的bin）
    set(_bin_dir "${CMAKE_BINARY_DIR}/bin")
    
    # 确保目录存在
    file(MAKE_DIRECTORY ${_bin_dir})
    
    # 拷贝第三方库DLL
    fcfun_copy_thirdlib_dlls(${_bin_dir} ${_build_type})
    
    # 拷贝Qt DLL
    set(_target_exe "${_bin_dir}/${_target_name}.exe")
    if(EXISTS ${_target_exe})
        fcfun_copy_qt_dlls(${_target_exe} ${_bin_dir} ${_windeployqt_exe})
    endif()
endfunction()
