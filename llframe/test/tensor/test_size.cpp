#include "test_config.h"
#ifdef TEST_SIZE
#include <gtest/gtest.h>
#include <type_traits>
#ifdef __LLFRAME_USE_MODULE__
import llframe.size;
import llframe.core.exception;
#else
#include "tensor/size.hpp"
#include "core/exception.hpp"
#endif // __LLFRAME_USE_MODULE__

TEST(size, make_size)
{
    auto a = llframe::make_size();
    ASSERT_EQ((std::is_same_v<llframe::Size<>, decltype(a)>), true);
};
TEST(size, dim)
{
    auto a = llframe::make_size();
    ASSERT_EQ(a.dims(), 0);
    auto b = llframe::make_size(1);
    ASSERT_EQ(b.dims(), 1);
    auto c = llframe::make_size(1, 2);
    ASSERT_EQ(c.dims(), 2);
    auto d = llframe::make_size(1, 2, 3);
    ASSERT_EQ(d.dims(), 3);
}
TEST(size, at)
{
    auto a = llframe::make_size(0, 1, 2, 3);
    ASSERT_EQ(a.at(0), 0);
    ASSERT_EQ(a.at(1), 1);
    ASSERT_EQ(a.at(2), 2);
    ASSERT_EQ(a.at(3), 3);
    ASSERT_ANY_THROW(a.at(4));
    ASSERT_EQ(a[0], 0);
    ASSERT_EQ(a[1], 1);
    ASSERT_EQ(a[2], 2);
    ASSERT_EQ(a[3], 3);
    ASSERT_ANY_THROW(a[4]);
}
TEST(size, assignment)
{
    auto a = llframe::make_size(0,1,2,3);
    auto b = a;
    ASSERT_EQ(b.at(0), 0);
    ASSERT_EQ(b.at(1), 1);
    ASSERT_EQ(b.at(2), 2);
    ASSERT_EQ(b.at(3), 3);
    ASSERT_EQ(b.dims(), 4);
    auto c(a);
    ASSERT_EQ(c.at(0), 0);
    ASSERT_EQ(c.at(1), 1);
    ASSERT_EQ(c.at(2), 2);
    ASSERT_EQ(c.at(3), 3);
    ASSERT_EQ(c.dims(), 4);
}
#endif // TEST_SIZE