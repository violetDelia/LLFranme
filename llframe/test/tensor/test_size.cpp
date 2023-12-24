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
    ASSERT_EQ((std::is_same_v<llframe::Size<0>, decltype(a)>), true);
    auto b = llframe::make_size(a);
    ASSERT_EQ((std::is_same_v<decltype(b), decltype(a)>), true);
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
    int dim_1 = 1;
    int dim_2 = 2;
    auto e = llframe::make_size(dim_1, dim_2);
    ASSERT_EQ(e.dims(), 2);
}
TEST(size, construct)
{
    int dim_1 = 0;
    int dim_2 = 1;
    auto a = llframe::make_size(dim_1, dim_2);
    ASSERT_EQ(a.at(0), 0);
    ASSERT_EQ(a.at(1), 1);
}
TEST(size, operator_array_subscript)
{
    size_t place_holder{};
    auto a = llframe::make_size(0, 1, 2, 3);
    ASSERT_EQ(a[0], 0);
    ASSERT_EQ(a[1], 1);
    ASSERT_EQ(a[2], 2);
    ASSERT_EQ(a[3], 3);
    ASSERT_ANY_THROW(place_holder = a[4]);
    a[3] = 4;
    ASSERT_EQ(a[0], 0);
    ASSERT_EQ(a[1], 1);
    ASSERT_EQ(a[2], 2);
    ASSERT_EQ(a[3], 4);
    ASSERT_ANY_THROW(place_holder = a[4]);
    auto b = llframe::make_size(0, long(1), long long(2), size_t(3));
    for (int i = 0; i < b.dims(); i++)
    {
        ASSERT_EQ(b[i], i);
    }
    ASSERT_ANY_THROW(place_holder = b[4]);
}
TEST(size, at)
{
    size_t place_holder{};
    auto a = llframe::make_size(0, 1, 2, 3);
    ASSERT_EQ(a.at(0), 0);
    ASSERT_EQ(a.at(1), 1);
    ASSERT_EQ(a.at(2), 2);
    ASSERT_EQ(a.at(3), 3);
    ASSERT_ANY_THROW(place_holder = a.at(4));
    auto b = llframe::make_size(0, long(1), long long(2), size_t(3));
    for (int i = 0; i < b.dims(); i++)
    {
        ASSERT_EQ(b.at(i), i);
    }
    ASSERT_ANY_THROW(place_holder = b[4]);
}

TEST(size, assignment)
{
    auto a = llframe::make_size(0, 1, 2, 3);
    auto b = a;
    ASSERT_EQ(b.at(0), 0);
    ASSERT_EQ(b.at(1), 1);
    ASSERT_EQ(b.at(2), 2);
    ASSERT_EQ(b.at(3), 3);
    ASSERT_EQ(b.dims(), 4);
    auto c(std::move(a));
    ASSERT_ANY_THROW(a.at(0));
    ASSERT_ANY_THROW(a.at(1));
    ASSERT_ANY_THROW(a.at(2));
    ASSERT_ANY_THROW(a.at(3));
    ASSERT_EQ(a.dims(), 0);

    ASSERT_EQ(c.at(0), 0);
    ASSERT_EQ(c.at(1), 1);
    ASSERT_EQ(c.at(2), 2);
    ASSERT_EQ(c.at(3), 3);
    ASSERT_EQ(c.dims(), 4);
}
TEST(size, operator_equal)
{
    auto a = llframe::make_size();
    auto b = llframe::make_size();
    ASSERT_EQ((a == b), true);
    ASSERT_EQ((a != b), false);
    auto c = llframe::make_size(0, 1, 2, 3);
    ASSERT_EQ((a == c), false);
    // ASSERT_EQ((a != c), true);
    auto d = llframe::make_size(0, int(1), long(2), size_t(3));
    ASSERT_EQ((c == d), true);
    // ASSERT_EQ((d != d) ,false);
    auto e = llframe::make_size(0, int(1), long(2));
    ASSERT_EQ((d == e), false);
    ASSERT_EQ((e == d), false);
}

#endif // TEST_SIZE