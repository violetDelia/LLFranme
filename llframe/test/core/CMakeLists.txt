# #---------- test option ----------##
# cache
if(DEFINED TEST_BASE_TYPE)
    unset(TEST_BASE_TYPE CACHE)
endif()

# option
option(TEST_BASE_TYPE "llfrmae_core::base_type.hpp" ON)

# #---------- source files ----------##
if(TEST_BASE_TYPE)
    list(APPEND LLFrame_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_base_type.cpp")
    set(LLFrame_TEST_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
endif(TEST_BASE_TYPE)