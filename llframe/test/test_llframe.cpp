#include "test_config.h"
#ifdef TEST_LLFRAME
#include <gtest/gtest.h>
#ifdef __LLFRAME_USE_MODULE__
import llframe;
#else
#include "llframe.hpp"
#endif // __LLFRAME_USE_MODULE__

#endif // TEST_FRAMWORK