# #---------- build options ----------# #
if(DEFINED TEST_PROJECT)
    unset(TEST_PROJECT CACHE)
endif()

option(TEST_PROJECT "test project" ON)

# #---------- cmake settings ----------# #
CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

# #---------- project settings ----------# #
project(LLFrame VERSION 1.0.0 LANGUAGES C CXX CUDA DESCRIPTION "LLFrame")

# #---------- dir define ----------##
# compiler_test
set(COMPILER_TEST_RELATIVE_DIR "compiler_test")
cmake_path(APPEND COMPILER_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${COMPILER_TEST_RELATIVE_DIR}")

# llframe
set(LLFRAME_INCLUDE_RELATIVE_DIR "include")
cmake_path(APPEND LLFRAME_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${LLFRAME_INCLUDE_RELATIVE_DIR}")
set(LLFRAME_SOURCE_RELATIVE_DIR "src")
cmake_path(APPEND LLFRAME_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${LLFRAME_SOURCE_RELATIVE_DIR}")

# test
set(PROJECT_TEST_RELATIVE_DIR "test")
cmake_path(APPEND PROJECT_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${PROJECT_TEST_RELATIVE_DIR}")

# install
set(INSTALL_DIR "${PROJECT_SOURCE_DIR}/install")

# #---------- generate configure header file ----------##
configure_file(config.h.in config.h)
configure_file(config.h.in "${LLFRAME_INCLUDE_DIR}/config.h")

# #---------- compiler settings ----------# #
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CUDA_STANDARD 20)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

# #---------- compiler test ----------##
add_subdirectory(${COMPILER_TEST_SOURCE_DIR})

# ---------- main ----------# #
add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_include_directories(main
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_DIR}>
)
target_link_libraries(main PRIVATE)

# #---------- output compiler info ----------# #
message(STATUS "${PROJECT_NAME} version: " ${PROJECT_VERSION})
message(STATUS "C standard is: " ${CMAKE_C_STANDARD})
message(STATUS "CXX standard is: " ${CMAKE_CXX_STANDARD})
message(STATUS "CUDA standard is: " ${CMAKE_CUDA_STANDARD})
message(STATUS "C compiler is: " ${CMAKE_C_COMPILER_ID} " - " ${CMAKE_C_COMPILER})
message(STATUS "CXX compiler is: " ${CMAKE_CXX_COMPILER_ID} " - " ${CMAKE_CXX_COMPILER})
message(STATUS "CUDA compiler is: " ${CMAKE_CUDA_COMPILER_ID} " - " ${CMAKE_CUDA_COMPILER})

# #---------- install ----------##
# install include dir
install(DIRECTORY "${LLFRAME_INCLUDE_DIR}" DESTINATION ${INSTALL_DIR})

# #---------- test ----------##
if(${TEST_PROJECT})
    message(STATUS "Testing project ON")
    set(TEST_NAME "${PROJECT_NAME}_test")
    enable_testing()
    configure_file(test_config.h.in test_config.h)
    add_subdirectory(${PROJECT_TEST_DIR})
endif()