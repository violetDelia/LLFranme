# #---------- option cache ----------# #
if(DEFINED COMPILER_TEST)
    unset(COMPILER_TEST CACHE)
endif()

if(DEFINED BUILD_SHARED_LIBS)
    unset(BUILD_SHARED_LIBS CACHE)
endif()

if(DEFINED USE_MODULE)
    unset(USE_MODULE CACHE)
endif()

if(DEFINED TEST_ALL)
    unset(TEST_ALL CACHE)
endif()

# #---------- build options ----------# #
option(OUT_COMPILER_INFO "out compiler information" OFF)
option(COMPILER_TEST "Test if the compilation is working" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(USE_MODULE "module support" ON)
option(TEST_ALL "test" ON)

if(USE_MODULE)
    add_compile_definitions(__LLFRAME_USE_MODULE__)
endif(USE_MODULE)

# #---------- cmake settings ----------# #
CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

# #---------- project settings ----------# #
project(LLFrame_compiler LANGUAGES C CXX CUDA)

# #---------- version define ----------# #
set(LLFrame_VERSION 1.0.0)

# #---------- reletive path define ----------##
set(COMPILER_TEST_RELATIVE_DIR "compiler_test")
set(LLFRAME_RELATIVE_DIR "llframe")
set(INSTALL_DIR "install")
set(INSTALL_INCLUDE_DIR "include")
set(INSTALL_LIB_DIR "lib")
set(INSTALL_CMAKE_DIR "cmake")
set(INSTALL_RUNTIME_DIR "bin")

# #---------- define absolute path ----------##
cmake_path(APPEND COMPILER_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${COMPILER_TEST_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_RELATIVE_DIR})
cmake_path(APPEND INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${INSTALL_DIR})
cmake_path(APPEND INSTALL_INCLUDE_DIR ${INSTALL_DIR} ${INSTALL_INCLUDE_DIR})
cmake_path(APPEND INSTALL_LIB_DIR ${INSTALL_DIR} ${INSTALL_LIB_DIR})
cmake_path(APPEND INSTALL_CMAKE_DIR ${INSTALL_DIR} ${INSTALL_CMAKE_DIR})
cmake_path(APPEND INSTALL_RUNTIME_DIR ${INSTALL_DIR} ${INSTALL_RUNTIME_DIR})

# #---------- compiler settings ----------# #
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CUDA_STANDARD 20)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

if(MSVC)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/wd4819>)
    string(REGEX REPLACE "\"$" " /wd4819\"" CMAKE_CUDA_FLAGS ${CMAKE_CUDA_FLAGS})
endif()

# #---------- add subdirectory ----------##
if(COMPILER_TEST)
    add_subdirectory(${COMPILER_TEST_DIR})
endif(COMPILER_TEST)

add_subdirectory(${LLFRAME_DIR})

# ---------- main ----------# #
add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_include_directories(main
    PRIVATE
    $<BUILD_INTERFACE:${LLFRAME_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LLFRAME_INCLUDE_DIR}>
)
target_link_libraries(main PRIVATE LLFrame)
