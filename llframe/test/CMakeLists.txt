# #---------- test option ----------##
# cache
if(DEFINED TEST_LLFRAME)
    unset(TEST_LLFRAME CACHE)
endif()

if(DEFINED TEST_CORE)
    unset(TEST_CORE CACHE)
endif()

if(DEFINED TEST_MEMORY)
    unset(TEST_MEMORY CACHE)
endif()

if(DEFINED TEST_TENSOR)
    unset(TEST_TENSOR CACHE)
endif()

# option
option(TEST_LLFRAME "test llframe" ON)
option(TEST_CORE "test llfrmae::core" ON)
option(TEST_MEMORY "test llfrmae::memory" ON)
option(TEST_TENSOR "test llfrmae::tensor" ON)

# #---------- reletive path define ----------##
set(CORE_TEST_RELATIVE_DIR "core")
set(MEMORY_TEST_RELATIVE_DIR "memory")
set(TENSOR_TEST_RELATIVE_DIR "tensor")

# #---------- define absolute path ----------##
cmake_path(APPEND CORE_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CORE_TEST_RELATIVE_DIR})
cmake_path(APPEND MEMORY_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${MEMORY_TEST_RELATIVE_DIR})
cmake_path(APPEND TENSOR_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${TENSOR_TEST_RELATIVE_DIR})

# #---------- external library ----------##
find_package(GTest 1.14.0 REQUIRED)

# #---------- source files ----------##
set(LLFrame_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_all.cpp")

if(TEST_LLFRAME)
    list(APPEND TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_llframe.cpp")
    set(TEST_ALL_FILES ${TEST_ALL_FILES} PARENT_SCOPE)
endif(TEST_LLFRAME)

if(TEST_CORE)
    list(APPEND TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_core.cpp")
    set(TEST_ALL_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
    add_subdirectory(${CORE_TEST_DIR})
endif(TEST_CORE)

if(TEST_MEMORY)
    list(APPEND TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_memory.cpp")
    set(TEST_ALL_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
    add_subdirectory(${MEMORY_TEST_DIR})
endif(TEST_MEMORY)

if(TEST_TENSOR)
    set(TEST_ALL_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
    add_subdirectory(${TENSOR_TEST_DIR})
endif(TEST_TENSOR)

# #---------- TEST_ALL ----------##
add_executable(test_LLFrame ${LLFrame_TEST_FILES})
target_include_directories(test_LLFrame
    PRIVATE
    $<BUILD_INTERFACE: ${LLFRAME_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LLFRAME_INCLUDE_DIR}>
)

target_link_libraries(test_LLFrame PRIVATE ${GTEST_LIBRARIES} LLFrame)
