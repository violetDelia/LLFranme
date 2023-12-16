# #---------- test option ----------##
# cache
if(DEFINED TEST_ALLOCATOR)
    unset(TEST_ALLOCATOR CACHE)
endif()

if(DEFINED TEST_DEVICE)
    unset(TEST_DEVICE CACHE)
endif()

# option
option(TEST_ALLOCATOR "llfrmae_memory::allocate.hpp" ON)
option(TEST_DEVICE "llfrmae_memory::device.hpp")

# #---------- source files ----------##
if(TEST_ALLOCATOR)
    list(APPEND LLFrame_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_allocator.cpp")
    set(LLFrame_TEST_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
endif(TEST_ALLOCATOR)

if(TEST_DEVICE)
    list(APPEND LLFrame_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_device.cpp")
    set(LLFrame_TEST_FILES ${LLFrame_TEST_FILES} PARENT_SCOPE)
endif(TEST_DEVICE)