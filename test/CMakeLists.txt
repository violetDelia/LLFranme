# #---------- test option ----------##
# cache
if(DEFINED TEST_LLFRAME)
    unset(TEST_LLFRAME CACHE)
endif()

if(DEFINED TEST_CORE)
    unset(TEST_CORE CACHE)
endif()

# option
option(TEST_LLFRAME "test llframe" ON)
option(TEST_CORE "test llfrmae_core" ON)

# #---------- reletive path define ----------##
set(CORE_TEST_RELATIVE_DIR "core")

# #---------- define absolute path ----------##
cmake_path(APPEND CORE_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CORE_TEST_RELATIVE_DIR})

# #---------- external library ----------##
find_package(GTest 1.14.0 REQUIRED)

# #---------- source files ----------##
set(TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_all.cpp")

if(TEST_LLFRAME)
    list(APPEND TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_llframe.cpp")
    set(TEST_ALL_FILES ${TEST_ALL_FILES} PARENT_SCOPE)
endif(TEST_LLFRAME)

if(TEST_CORE)
    list(APPEND TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_core.cpp")
    set(TEST_ALL_FILES ${TEST_ALL_FILES} PARENT_SCOPE)
    add_subdirectory(${CORE_TEST_DIR})
endif(TEST_CORE)

# #---------- TEST_ALL ----------##
add_executable(${TEST_NAME} ${TEST_ALL_FILES})
target_include_directories(${TEST_NAME}
    PUBLIC
    $<BUILD_INTERFACE: ${PROJECT_INCLUDE_FILES} ${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDE_RELATIVE_DIR}>
)

target_link_libraries(${TEST_NAME} PRIVATE ${GTEST_LIBRARIES} llframe)
