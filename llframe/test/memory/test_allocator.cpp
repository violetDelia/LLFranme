#include "test_config.h"
#ifdef TEST_ALLOCATOR
#include <gtest/gtest.h>
#ifdef __LLFRAME_USE_MODULE__
import llframe.memory.allocator;
#else
#include "memory/allocator.hpp"
#endif // __LLFRAME_USE_MODULE__



#endif // TEST_ALLOCATOR