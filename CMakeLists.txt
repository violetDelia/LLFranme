# #---------- build options ----------# #
option(OUT_COMPILER_INFO "test project" OFF)
option(TEST_PROJECT "test project" ON)
option(COMPILER_TEST_OPTION "Test if the compilation is working" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(INSTALL_TEST "test insatll" ON)

# #---------- cmake settings ----------# #
CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

# #---------- project settings ----------# #
project(LLFrame VERSION 1.0.0 LANGUAGES C CXX CUDA DESCRIPTION "LLFrame")

# #---------- reletive path define ----------##
set(COMPILER_TEST_RELATIVE_DIR "compiler_test")
set(PROJECT_INCLUDE_RELETIVE_DIR "include")
set(PROJECT_SOUCE_RELETIVE_DIR "src")
set(CMAKE_RELATIVE_DIR "cmake")
set(PROJECT_TEST_RELATIVE_DIR "test")
set(LLFRAME_INCLUDE_RELATIVE_DIR "include/llframe")
set(LLFRAME_SOURCE_RELATIVE_DIR "src")
set(INSTALL_RELATIVE_DIR "install")
set(INSTALL_INCLUDE_RELATIVE_DIR "include")
set(INSTALL_LIB_RELATIVE_DIR "lib")
set(INSTALL_RUNTIME_RELATIVE_DIR "bin")
set(INSTALL_TEST_RELATIVE_DIR "install_test")

# #---------- define absolute path ----------##
cmake_path(APPEND COMPILER_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${COMPILER_TEST_RELATIVE_DIR})
cmake_path(APPEND PROJECT_SOUCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOUCE_RELETIVE_DIR})
cmake_path(APPEND PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_INCLUDE_RELETIVE_DIR})
cmake_path(APPEND INSTALL_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${INSTALL_TEST_RELATIVE_DIR})
cmake_path(APPEND CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_RELATIVE_DIR})
cmake_path(APPEND PROJECT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_TEST_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_INCLUDE_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_SOURCE_RELATIVE_DIR})
cmake_path(APPEND INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${INSTALL_RELATIVE_DIR})
cmake_path(APPEND INSTALL_INCLUDE_DIR ${INSTALL_DIR} ${INSTALL_INCLUDE_RELATIVE_DIR})
cmake_path(APPEND INSTALL_LIB_DIR ${INSTALL_DIR} ${INSTALL_LIB_RELATIVE_DIR})
cmake_path(APPEND INSTALL_CMAKE_DIR ${INSTALL_DIR} ${CMAKE_RELATIVE_DIR})
cmake_path(APPEND INSTALL_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${INSTALL_TEST_RELATIVE_DIR})

# #---------- generate configure header file ----------##
configure_file(config.h.in config.h)
configure_file(config.h.in "${LLFRAME_INCLUDE_DIR}/config.h")

# #---------- compiler settings ----------# #
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CUDA_STANDARD 20)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

if(MSVC)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/wd4819>)
    string(REGEX REPLACE "\"$" " /wd4819\"" CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS}")
endif()

# #---------- add subdirectory ----------##
# complier test
if(COMPILER_TEST_OPTION)
    add_subdirectory(${COMPILER_TEST_DIR})
endif(COMPILER_TEST_OPTION)

add_subdirectory(${PROJECT_SOUCE_DIR})

# # ---------- main ----------# #
add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_include_directories(main
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDE_RELATIVE_DIR}>
)
target_link_libraries(main PRIVATE llframe)

# # ---------- test_install ----------# #
if(INSTALL_TEST)
    add_subdirectory(${INSTALL_TEST_DIR})
endif(INSTALL_TEST)

# #---------- output compiler info ----------# #
if(OUT_COMPILER_INFO)
    message(STATUS "${PROJECT_NAME} version: " ${PROJECT_VERSION})
    message(STATUS "C standard is: " ${CMAKE_C_STANDARD})
    message(STATUS "CXX standard is: " ${CMAKE_CXX_STANDARD})
    message(STATUS "CUDA standard is: " ${CMAKE_CUDA_STANDARD})
    message(STATUS "C compiler is: " ${CMAKE_C_COMPILER_ID} "-" ${CMAKE_C_COMPILER})
    message(STATUS "CXX compiler is: " ${CMAKE_CXX_COMPILER_ID} "-" ${CMAKE_CXX_COMPILER})
    message(STATUS "CUDA compiler is: " ${CMAKE_CUDA_COMPILER_ID} "-" ${CMAKE_CUDA_COMPILER})
endif(OUT_COMPILER_INFO)

# #---------- install ----------##
# install
install(DIRECTORY ${PROJECT_INCLUDE_DIR} DESTINATION ${INSTALL_DIR})

# config.cmake
include(CMakePackageConfigHelpers)

configure_package_config_file("${CMAKE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LLFrameConfig.cmake"
    INSTALL_DESTINATION ${INSTALL_CMAKE_DIR})
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LLFrameConfig.cmake

    # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${INSTALL_CMAKE_DIR}
)

# configure_file("${CMAKE_DIR}/Config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}}/${PROJECT_NAME}Config.cmake")
# install(FILES "${CMAKE_CURRENT_BINARY_DIR}}/${PROJECT_NAME}Config.cmake" DESTINATION ${INSTALL_CMAKE_DIR})

# #---------- test ----------##
if(${TEST_PROJECT})
    message(STATUS "Testing project ON")
    set(TEST_NAME "${PROJECT_NAME}_test")
    enable_testing()
    configure_file(test_config.h.in test_config.h)
    add_subdirectory(${PROJECT_TEST_DIR})
endif()