# #---------- test option ----------##
# cache
if(DEFINED TEST_ALLOCATOR)
    unset(TEST_ALLOCATOR CACHE)
endif()

# option
option(TEST_ALLOCATOR "llfrmae_core::base_type.hpp" ON)

# #---------- source files ----------##
if(TEST_ALLOCATOR)
    list(APPEND LLFrame_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_allocator.cpp")
    set(LLFrame_TEST_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
endif(TEST_ALLOCATOR)