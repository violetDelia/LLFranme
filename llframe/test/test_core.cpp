#include "test_config.h"
#ifdef TEST_CORE
#include <gtest/gtest.h>
#ifdef __LLFRAME_USE_MODULE__
import llframe.core;
#else
#include "core/core.hpp"
#endif // __LLFRAME_USE_MODULE__

#endif // TEST_CORE