# #---------- cmake settings ----------# #
CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
project(Tutorials VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "Tutorials")

# #---------- compiler settings ----------# #
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

if(MSVC)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/wd4819>)
endif()

# include
get_filename_component(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
cmake_path(APPEND INSTALL_CMAKE_DIR ${PARENT_DIR} "install")

if(EXISTS ${INSTALL_CMAKE_DIR})
    find_package(LLFrame 1.0.0 REQUIRED PATHS ${INSTALL_CMAKE_DIR})

    # # ---------- mian ----------# #
    add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/tutorial.cpp" ${LLFrame_MODULE_FILES})
    target_include_directories(main
        PRIVATE
        $<BUILD_INTERFACE:${LLFrame_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${NONE}>
    )
    target_link_libraries(main PRIVATE LLFrame)
endif()
