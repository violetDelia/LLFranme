# #---------- test option ----------##
# cache
if(DEFINED TEST_SIZE)
    unset(TEST_ALLOCATOR CACHE)
endif()

# option
option(TEST_SIZE "llfrmae_memory::size.hpp" ON)

# #---------- source files ----------##
if(TEST_SIZE)
    list(APPEND LLFrame_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_size.cpp")
    set(LLFrame_TEST_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
endif(TEST_SIZE)