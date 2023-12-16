#include "test_config.h"
#ifdef TEST_DEVICE
#include <gtest/gtest.h>
#ifdef __LLFRAME_USE_MODULE__
import llframe.memory.device;
#else
#include "memory/device.hpp"
TEST(device.construct)

#endif // __LLFRAME_USE_MODULE__
#endif // TEST_DEVICE
