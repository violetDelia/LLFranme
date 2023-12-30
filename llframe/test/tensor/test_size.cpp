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

TEST(size, make_size) {
    auto a = llframe::make_size();
    ASSERT_EQ((std::is_same_v<llframe::Size<0>, decltype(a)>), true);
    ASSERT_EQ(a.begin().operator->() == nullptr, true);
    auto b = llframe::make_size(a);
    ASSERT_EQ((std::is_same_v<decltype(b), decltype(a)>), true);
    ASSERT_EQ(b.begin().operator->() == nullptr, true);
    auto c = llframe::make_size(1, 2, size_t(3), long(4));
    ASSERT_EQ((std::is_same_v<llframe::Size<4>, decltype(c)>), true);
    ASSERT_EQ(c.begin().operator->() == nullptr, false);
    auto d = llframe::make_size(c);
    ASSERT_EQ((std::is_same_v<decltype(c), decltype(d)>), true);
    ASSERT_EQ(d.begin().operator->() == nullptr, false);
};
TEST(size, construct) {
    int dim_1 = 0;
    long long dim_2 = 1;
    int place_holder{};
    llframe::Size<2> a(dim_1, dim_2);
    ASSERT_EQ(a.at(0), 0);
    ASSERT_EQ(a.at(1), 1);
    ASSERT_THROW(place_holder = a.at(2), llframe::Out_Range);
    auto b(a);
    ASSERT_EQ(b.at(0), 0);
    ASSERT_EQ(b.at(1), 1);
    ASSERT_THROW(place_holder = b.at(2), llframe::Out_Range);
    auto c(std::move(b));
    ASSERT_EQ(b.begin().operator->() == nullptr, true);
    ASSERT_EQ(c.at(0), 0);
    ASSERT_EQ(c.at(1), 1);
    ASSERT_THROW(place_holder = c.at(2), llframe::Out_Range);
    auto d = c;
    ASSERT_EQ(d.at(0), 0);
    ASSERT_EQ(d.at(1), 1);
    ASSERT_THROW(place_holder = d.at(2), llframe::Out_Range);
    auto e = std::move(d);
    ASSERT_EQ(d.begin().operator->() == nullptr, true);
    ASSERT_EQ(e.at(0), 0);
    ASSERT_EQ(e.at(1), 1);
    ASSERT_THROW(place_holder = c.at(2), llframe::Out_Range);
}
TEST(size, dims) {
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
TEST(size, operator_equal) {
    auto a = llframe::make_size();
    auto b = llframe::make_size(1, 2);
    auto c = llframe::make_size(size_t(1), long(2));
    auto d = llframe::make_size(0, 0);
    auto e(std::move(b));
    ASSERT_EQ((a == b), false);
    ASSERT_EQ((a != b), true);

    ASSERT_EQ((b == c), false);
    ASSERT_EQ((b != c), true);
    ASSERT_EQ((b == d), true);
    ASSERT_EQ((b != d), false);

    ASSERT_EQ((c == e), true);
    ASSERT_EQ((c != e), false);
}

TEST(size, at) {
    int place_holder{};
    auto a = llframe::make_size();
    ASSERT_THROW(place_holder = a.at(0), llframe::Out_Range);
    auto b = llframe::make_size(0, 1);
    ASSERT_EQ(b.at(0), 0);
    ASSERT_EQ(b.at(1), 1);
    ASSERT_THROW(place_holder = a.at(2), llframe::Out_Range);
    auto c = std::move(b);
    ASSERT_EQ(b.at(0), 0);
    ASSERT_EQ(b.at(1), 0);
    ASSERT_THROW(place_holder = a.at(2), llframe::Out_Range);
    ASSERT_EQ(c.at(0), 0);
    ASSERT_EQ(c.at(1), 1);
    ASSERT_THROW(place_holder = c.at(2), llframe::Out_Range);
    auto d = c;
    ASSERT_EQ(d.at(0), c.at(0));
    ASSERT_EQ(d.at(1), c.at(1));
    ASSERT_THROW(place_holder = d.at(2), llframe::Out_Range);
}

TEST(size, operator_array_subscript) {
    int place_holder{};
    auto a = llframe::make_size();
    ASSERT_THROW(place_holder = a[0], llframe::Null_Pointer);
    auto b = llframe::make_size(0, 1);
    ASSERT_EQ(b[0], 0);
    ASSERT_EQ(b[1], 1);
    ASSERT_NO_THROW(place_holder = b[2]);
    auto c = std::move(b);
    ASSERT_THROW(place_holder = b[0], llframe::Null_Pointer);
    ASSERT_EQ(c[0], 0);
    ASSERT_EQ(c[1], 1);
    ASSERT_NO_THROW(place_holder = c[2]);
    auto d = c;
    ASSERT_EQ(d[0], c[0]);
    ASSERT_EQ(d[1], c[1]);
    ASSERT_NO_THROW(place_holder = d[2]);
    ASSERT_EQ(d[0], 0);
    d[0] = 2;
    ASSERT_EQ(d[0], 2);
}
#endif // TEST_SIZE