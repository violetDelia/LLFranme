#include "test_config.h"
#ifdef TEST_ITERATOR
#include <gtest/gtest.h>
#ifdef __LLFRAME_USE_MODULE__
import llframe;
#else
#include "llframe.hpp"
#endif // __LLFRAME_USE_MODULE__
#include <iterator>
#include <array>
using namespace llframe;

TEST(iterator, is_Forward_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    ASSERT_EQ(is_Forward_Iterator<Const_Forward_Iterator<decltype(arr)>>, true);
    ASSERT_EQ(is_Forward_Iterator<Forward_Iterator<decltype(arr)>>, true);
    ASSERT_EQ(is_Forward_Iterator<Const_Bidirectional_Iterator<decltype(arr)>>,
              true);
    ASSERT_EQ(is_Forward_Iterator<Bidirectional_Iterator<decltype(arr)>>, true);
    ASSERT_EQ(is_Forward_Iterator<Const_Random_Iterator<decltype(arr)>>, true);
    ASSERT_EQ(is_Forward_Iterator<Random_Iterator<decltype(arr)>>, true);
}
TEST(iterator, is_Bidirectional_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    ASSERT_EQ(is_Bidirectional_Iterator<Const_Forward_Iterator<decltype(arr)>>,
              false);
    ASSERT_EQ(is_Bidirectional_Iterator<Forward_Iterator<decltype(arr)>>,
              false);
    ASSERT_EQ(
        is_Bidirectional_Iterator<Const_Bidirectional_Iterator<decltype(arr)>>,
        true);
    ASSERT_EQ(is_Bidirectional_Iterator<Bidirectional_Iterator<decltype(arr)>>,
              true);
    ASSERT_EQ(is_Bidirectional_Iterator<Const_Random_Iterator<decltype(arr)>>,
              true);
    ASSERT_EQ(is_Bidirectional_Iterator<Random_Iterator<decltype(arr)>>, true);
}
TEST(iterator, is_Random_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    ASSERT_EQ(is_Random_Iterator<Const_Forward_Iterator<decltype(arr)>>, false);
    ASSERT_EQ(is_Random_Iterator<Forward_Iterator<decltype(arr)>>, false);
    ASSERT_EQ(is_Random_Iterator<Const_Bidirectional_Iterator<decltype(arr)>>,
              false);
    ASSERT_EQ(is_Random_Iterator<Bidirectional_Iterator<decltype(arr)>>, false);
    ASSERT_EQ(is_Random_Iterator<Const_Random_Iterator<decltype(arr)>>, true);
    ASSERT_EQ(is_Random_Iterator<Random_Iterator<decltype(arr)>>, true);
}
TEST(iterator, Const_Forward_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    std::array<const int, 3> another_arr{0, 1, 2};
    using Iterator = Const_Forward_Iterator<decltype(arr)>;
    using It_traits = std::iterator_traits<Iterator>;
    using Iterator_Another = Const_Forward_Iterator<decltype(another_arr)>;
    using It_A_traits = std::iterator_traits<Iterator_Another>;

    ASSERT_EQ((std::is_same_v<typename It_traits::pointer, const int *>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::value_type, int>), true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::pointer, const int *>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::value_type, const int>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::iterator_category,
                              std::forward_iterator_tag>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::iterator_category,
                              std::forward_iterator_tag>),
              true);

    Iterator it1(arr.data());
    Iterator it2(arr.data());
    Iterator_Another it3(another_arr.data());

    ASSERT_EQ((std::is_same_v<decltype(*it3), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3.operator->()), const int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(*it1), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1.operator->()), const int *>), true);

    ASSERT_EQ(it1 == it2, true);
    ASSERT_EQ(it1 == it3, false);
    ASSERT_EQ(it1 != it2, false);
    ASSERT_EQ(it1 != it3, true);

    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);
    ASSERT_EQ(*(it1++), 0);
    ASSERT_EQ(*(++it2), 1);
    ASSERT_EQ(*(++it3), 1);
    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*it3, 1);

    ASSERT_EQ((std::input_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::forward_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::bidirectional_iterator<decltype(it1)>), false);
    ASSERT_EQ((std::random_access_iterator<decltype(it1)>), false);
}

TEST(iterator, Forward_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    std::array<const int, 3> another_arr{0, 1, 2};
    using Iterator = Forward_Iterator<decltype(arr)>;
    using It_traits = std::iterator_traits<Iterator>;
    using Iterator_Another = Forward_Iterator<decltype(another_arr)>;
    using It_A_traits = std::iterator_traits<Iterator_Another>;

    ASSERT_EQ((std::is_same_v<typename It_traits::pointer, int *>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::reference, int &>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::value_type, int>), true);

    ASSERT_EQ((std::is_same_v<typename It_A_traits::pointer, const int *>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::value_type, const int>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::iterator_category,
                              std::forward_iterator_tag>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::iterator_category,
                              std::forward_iterator_tag>),
              true);

    Iterator it1(arr.data());
    Iterator it2(arr.data());
    Iterator_Another it3(another_arr.data());

    ASSERT_EQ((std::is_same_v<decltype(*it1), int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1.operator->()), int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(*it3), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3.operator->()), const int *>), true);

    ASSERT_EQ(it1 == it2, true);
    ASSERT_EQ(it1 == it3, false);
    ASSERT_EQ(it1 != it2, false);
    ASSERT_EQ(it1 != it3, true);

    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);
    ASSERT_EQ(*(it1++), 0);
    ASSERT_EQ(*(++it2), 1);
    ASSERT_EQ(*(++it3), 1);
    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*it3, 1);

    ASSERT_EQ((std::input_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::forward_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::bidirectional_iterator<decltype(it1)>), false);
    ASSERT_EQ((std::random_access_iterator<decltype(it1)>), false);

    it2 = it1;
    *it1 = 5;
    ASSERT_EQ(*it2, 5);
}
TEST(iterator, Const_Bidirectional_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    std::array<const int, 3> another_arr{0, 1, 2};
    using Iterator = Const_Bidirectional_Iterator<decltype(arr)>;
    using It_traits = std::iterator_traits<Iterator>;
    using Iterator_Another =
        Const_Bidirectional_Iterator<decltype(another_arr)>;
    using It_A_traits = std::iterator_traits<Iterator_Another>;

    ASSERT_EQ((std::is_same_v<typename It_traits::pointer, const int *>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::value_type, int>), true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::pointer, const int *>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::value_type, const int>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::iterator_category,
                              std::bidirectional_iterator_tag>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::iterator_category,
                              std::bidirectional_iterator_tag>),
              true);

    Iterator it1(arr.data());
    Iterator it2(arr.data());
    Iterator_Another it3(another_arr.data());

    ASSERT_EQ((std::is_same_v<decltype(*it3), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3.operator->()), const int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(*it1), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1.operator->()), const int *>), true);

    ASSERT_EQ(it1 == it2, true);
    ASSERT_EQ(it1 == it3, false);
    ASSERT_EQ(it1 != it2, false);
    ASSERT_EQ(it1 != it3, true);

    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);
    ASSERT_EQ(*(it1++), 0);
    ASSERT_EQ(*(++it2), 1);
    ASSERT_EQ(*(++it3), 1);
    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*it3, 1);

    ASSERT_EQ(*(it1--), 1);
    ASSERT_EQ(*(--it2), 0);
    ASSERT_EQ(*(--it3), 0);
    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);

    ASSERT_EQ((std::input_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::forward_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::bidirectional_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::random_access_iterator<decltype(it1)>), false);
}
TEST(iterator, Bidirectional_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    std::array<const int, 3> another_arr{0, 1, 2};
    using Iterator = Bidirectional_Iterator<decltype(arr)>;
    using It_traits = std::iterator_traits<Iterator>;
    using Iterator_Another = Bidirectional_Iterator<decltype(another_arr)>;
    using It_A_traits = std::iterator_traits<Iterator_Another>;

    ASSERT_EQ((std::is_same_v<typename It_traits::pointer, int *>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::reference, int &>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::value_type, int>), true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::pointer, const int *>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::value_type, const int>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::iterator_category,
                              std::bidirectional_iterator_tag>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::iterator_category,
                              std::bidirectional_iterator_tag>),
              true);

    Iterator it1(arr.data());
    Iterator it2(arr.data());
    Iterator_Another it3(another_arr.data());

    ASSERT_EQ((std::is_same_v<decltype(*it3), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3.operator->()), const int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(*it1), int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1.operator->()), int *>), true);

    ASSERT_EQ(it1 == it2, true);
    ASSERT_EQ(it1 == it3, false);
    ASSERT_EQ(it1 != it2, false);
    ASSERT_EQ(it1 != it3, true);

    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);
    ASSERT_EQ(*(it1++), 0);
    ASSERT_EQ(*(++it2), 1);
    ASSERT_EQ(*(++it3), 1);
    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*it3, 1);

    ASSERT_EQ(*(it1--), 1);
    ASSERT_EQ(*(--it2), 0);
    ASSERT_EQ(*(--it3), 0);
    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);

    ASSERT_EQ((std::input_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::forward_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::bidirectional_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::random_access_iterator<decltype(it1)>), false);

    it2 = it1;
    *it1 = 5;
    ASSERT_EQ(*it2, 5);
}

TEST(iterator, Const_Random_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    std::array<const int, 3> another_arr{0, 1, 2};
    using Iterator = Const_Random_Iterator<decltype(arr)>;
    using It_traits = std::iterator_traits<Iterator>;
    using Iterator_Another = Const_Random_Iterator<decltype(another_arr)>;
    using It_A_traits = std::iterator_traits<Iterator_Another>;

    ASSERT_EQ((std::is_same_v<typename It_traits::pointer, const int *>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::value_type, int>), true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::pointer, const int *>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::value_type, const int>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::iterator_category,
                              std::random_access_iterator_tag>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::iterator_category,
                              std::random_access_iterator_tag>),
              true);

    Iterator it1(arr.data());
    Iterator it2(arr.data());
    Iterator_Another it3(another_arr.data());

    ASSERT_EQ((std::is_same_v<decltype(*it3), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3.operator->()), const int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(*it1), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1.operator->()), const int *>), true);

    ASSERT_EQ((std::is_same_v<decltype(it1[0]), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3[0]), const int &>), true);

    ASSERT_EQ(it1 == it2, true);
    ASSERT_EQ(it1 == it3, false);
    ASSERT_EQ(it1 != it2, false);
    ASSERT_EQ(it1 != it3, true);
    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);

    ASSERT_EQ(*(it1++), 0);
    ASSERT_EQ(*(++it2), 1);
    ASSERT_EQ(*(++it3), 1);
    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*it3, 1);

    ASSERT_EQ(*(it1--), 1);
    ASSERT_EQ(*(--it2), 0);
    ASSERT_EQ(*(--it3), 0);
    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);

    ++it1;
    ASSERT_EQ(it1 > it2, true);
    ASSERT_EQ(it1 >= it2, true);
    ASSERT_EQ(it1 < it2, false);
    ASSERT_EQ(it1 <= it2, false);
    ASSERT_EQ(it2 + 1 == it1, true);
    ASSERT_EQ(*(it2 + 2) == 2, true);

    ++it1;
    ASSERT_EQ(it1 - 2 == it2, true);
    ASSERT_EQ(*(it1 - 2) == 0, true);
    ASSERT_EQ((it1 -= 2) == it1, true);
    ASSERT_EQ(*it1 == 0, true);
    ASSERT_EQ(*(it1 += 2) == 2, true);
    ASSERT_EQ(*it1 == 2, true);

    ASSERT_EQ(it2[0] == 0, true);
    ASSERT_EQ(it2[1] == 1, true);
    ASSERT_EQ(it2[2] == 2, true);
    ASSERT_EQ(it1[0] == 2, true);
    ASSERT_EQ(it1[-1] == 1, true);
    ASSERT_EQ(it1[-2] == 0, true);
    ASSERT_EQ(it1 - it2, 2);

    ASSERT_EQ((std::input_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::forward_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::bidirectional_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::random_access_iterator<decltype(it1)>), true);
}

TEST(iterator, Random_Iterator) {
    std::array<int, 3> arr{0, 1, 2};
    std::array<const int, 3> another_arr{0, 1, 2};
    using Iterator = Random_Iterator<decltype(arr)>;
    using It_traits = std::iterator_traits<Iterator>;
    using Iterator_Another = Random_Iterator<decltype(another_arr)>;
    using It_A_traits = std::iterator_traits<Iterator_Another>;

    ASSERT_EQ((std::is_same_v<typename It_traits::pointer, int *>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::reference, int &>), true);
    ASSERT_EQ((std::is_same_v<typename It_traits::value_type, int>), true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::pointer, const int *>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::reference, const int &>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::value_type, const int>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_traits::iterator_category,
                              std::random_access_iterator_tag>),
              true);
    ASSERT_EQ((std::is_same_v<typename It_A_traits::iterator_category,
                              std::random_access_iterator_tag>),
              true);

    Iterator it1(arr.data());
    Iterator it2(arr.data());
    Iterator_Another it3(another_arr.data());

    ASSERT_EQ((std::is_same_v<decltype(*it1), int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1.operator->()), int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(it1[0]), int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(*it3), const int &>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3.operator->()), const int *>), true);
    ASSERT_EQ((std::is_same_v<decltype(it3[0]), const int &>), true);

    ASSERT_EQ(it1 == it2, true);
    ASSERT_EQ(it1 == it3, false);
    ASSERT_EQ(it1 != it2, false);
    ASSERT_EQ(it1 != it3, true);

    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);
    ASSERT_EQ(*(it1++), 0);
    ASSERT_EQ(*(++it2), 1);
    ASSERT_EQ(*(++it3), 1);
    ASSERT_EQ(*it1, 1);
    ASSERT_EQ(*it2, 1);
    ASSERT_EQ(*it3, 1);

    ASSERT_EQ(*(it1--), 1);
    ASSERT_EQ(*(--it2), 0);
    ASSERT_EQ(*(--it3), 0);
    ASSERT_EQ(*it1, 0);
    ASSERT_EQ(*it2, 0);
    ASSERT_EQ(*it3, 0);

    ++it1;
    ASSERT_EQ(it1 > it2, true);
    ASSERT_EQ(it1 >= it2, true);
    ASSERT_EQ(it1 < it2, false);
    ASSERT_EQ(it1 <= it2, false);
    ASSERT_EQ(it2 + 1 == it1, true);
    ASSERT_EQ(*(it2 + 2) == 2, true);

    ++it1;
    ASSERT_EQ(it1 - 2 == it2, true);
    ASSERT_EQ(*(it1 - 2) == 0, true);
    ASSERT_EQ((it1 -= 2) == it1, true);
    ASSERT_EQ(*it1 == 0, true);
    ASSERT_EQ(*(it1 += 2) == 2, true);
    ASSERT_EQ(*it1 == 2, true);

    ASSERT_EQ(it2[0] == 0, true);
    ASSERT_EQ(it2[1] == 1, true);
    ASSERT_EQ(it2[2] == 2, true);
    ASSERT_EQ(it1[0] == 2, true);
    ASSERT_EQ(it1[-1] == 1, true);
    ASSERT_EQ(it1[-2] == 0, true);
    ASSERT_EQ(it1 - it2, 2);

    ASSERT_EQ((std::input_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::forward_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::bidirectional_iterator<decltype(it1)>), true);
    ASSERT_EQ((std::random_access_iterator<decltype(it1)>), true);

    it2 = it1;
    *it1 = 5;
    ASSERT_EQ(*it2, 5);
}
#endif // TEST_ITERATOR