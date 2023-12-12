
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was LLFrameConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################
set(LLFrame_INCLUDE_DIR   "D:/TianYi_Sync_Folder/13325386007/code/LLFrame/install/include/llframe")
set(LLFrame_MODULE_DIR "D:/TianYi_Sync_Folder/13325386007/code/LLFrame/install/include/llframe/__MODULE__")
file(GLOB_RECURSE LLFrame_MODULE_FILES "D:/TianYi_Sync_Folder/13325386007/code/LLFrame/install/include/llframe/__MODULE__/*.ixx")
include("${CMAKE_CURRENT_LIST_DIR}/LLFrameTargets.cmake")
