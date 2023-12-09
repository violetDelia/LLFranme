#include "test_config.h"
#ifdef TEST_ALLOCATOR
#include <gtest/gtest.h>
#include "memory/allocator.hpp"
TEST(Allocator, value_type)
{
    ASSERT_EQ((std::is_same_v<llframe::Allocator<int>::value_type, std::allocator<int>::value_type>), true);
    ASSERT_EQ((std::is_same_v<llframe::Allocator<int>::value_type, std::allocator<float>::value_type>), false);
    ASSERT_EQ((std::is_same_v<std::allocator_traits<llframe::Allocator<int>>::value_type, int>), true);
    ASSERT_EQ((std::is_same_v<std::allocator_traits<llframe::Allocator<float>>::value_type, int>), false);
}
TEST(Allocator, size_type)
{
    ASSERT_EQ((std::is_same_v<llframe::Allocator<int>::size_type, std::size_t>), true);
    ASSERT_EQ((std::is_same_v<std::allocator_traits<llframe::Allocator<std::size_t>>::size_type, std::size_t>), true);
}
TEST(Allocator, difference_type)
{
    ASSERT_EQ((std::is_same_v<llframe::Allocator<int>::difference_type, std::ptrdiff_t>), true);
    ASSERT_EQ((std::is_same_v<std::allocator_traits<llframe::Allocator<std::size_t>>::difference_type, std::ptrdiff_t>), true);
}
TEST(Allocator, propagate_on_container_move_assignment)
{
    ASSERT_EQ((std::is_same_v<llframe::Allocator<int>::propagate_on_container_move_assignment, std::true_type>), true);
    ASSERT_EQ((std::is_same_v<std::allocator_traits<llframe::Allocator<std::size_t>>::propagate_on_container_move_assignment, std::true_type>), true);
}
TEST(Allocator, is_always_equal)
{
    ASSERT_EQ((std::is_same_v<llframe::Allocator<int>::is_always_equal, std::true_type>), true);
    ASSERT_EQ((std::is_same_v<std::allocator_traits<llframe::Allocator<std::size_t>>::is_always_equal, std::true_type>), true);
}
TEST(Allocator, allocate)
{
    auto allocator = llframe::Allocator<int>();
    int *p;
    ASSERT_ANY_THROW(p = allocator.allocate(std::numeric_limits<std::size_t>::max()));
}

#endif // TEST_ALLOCATOR