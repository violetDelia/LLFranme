#include "test_config.h"
#include <gtest/gtest.h>
#ifdef TEST_STD
TEST(test_std, string)
{
    std::string string("123456");
    ASSERT_EQ(string.size(), 6);
}
#endif