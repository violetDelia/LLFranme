# #---------- test option ----------##
# cache
if(DEFINED TEST_LLFRAME)
    unset(TEST_LLFRAME CACHE)
endif()

if(DEFINED TEST_STD)
    unset(TEST_STD CACHE)
endif()

# option
option(TEST_LLFRAME "test LLFramwork" ON)
option(TEST_STD "test STD" ON)

# #---------- external library ----------##
find_package(GTest 1.14.0 REQUIRED)

# #---------- source files ----------##
set(TEST_ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_all.cpp")

if(TEST_STD)
    set(TEST_ALL_FILES  ${TEST_ALL_FILES}  "${CMAKE_CURRENT_SOURCE_DIR}/test_std.cpp")
endif(TEST_STD)
# #---------- add subdirectory ----------##

# #---------- TEST_ALL ----------##
add_executable(TEST_LLFRAME_ALL "${TEST_ALL_FILES}")
target_include_directories(TEST_LLFRAME_ALL
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(TEST_LLFRAME_ALL PRIVATE ${GTEST_LIBRARIES})
