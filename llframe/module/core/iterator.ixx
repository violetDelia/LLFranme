//    Copyright 2023 时光丶人爱

//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at

//        http://www.apache.org/licenses/LICENSE-2.0

//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

/**
 * @file iterator.ixx
 * @brief 迭代器接口
 * @details
 * @author 时光丶人爱
 * @date 2023-12-23
 * @see If you have any questions about the code or if you think there is a
 * better way to implement it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */

module;
#include "core/iterator.hpp"
export module llframe.core.iterator;
export namespace llframe {
using llframe::is_Bidirectional_Iterator;
using llframe::is_Forward_Iterator;
using llframe::is_Random_Iterator;

using llframe::Bidirectional_Iterator;
using llframe::Const_Bidirectional_Iterator;
using llframe::Const_Forward_Iterator;
using llframe::Const_Random_Iterator;
using llframe::Forward_Iterator;
using llframe::Random_Iterator;

template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
constexpr bool operator==(const Left_Iterator &left,
                          const Right_Iterator &right) noexcept;

template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
constexpr bool operator!=(const Left_Iterator &left,
                          const Right_Iterator &right) noexcept;

template <is_Forward_Iterator Iterator>
constexpr typename Iterator::reference
operator*(const Iterator &iterator) noexcept;

template <is_Forward_Iterator Iterator>
constexpr typename Iterator::Self &operator++(Iterator &iterator);

template <is_Forward_Iterator Iterator>
constexpr typename Iterator::Self operator++(Iterator &iterator, int);

template <is_Bidirectional_Iterator Iterator>
constexpr typename Iterator::Self &operator--(Iterator &iterator);

template <is_Bidirectional_Iterator Iterator>
constexpr typename Iterator::Self operator--(Iterator &iterator, int);

template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
constexpr bool operator>(const Left_Iterator &left,
                         const Right_Iterator &right) noexcept;

template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
constexpr bool operator<(const Left_Iterator &left,
                         const Right_Iterator &right) noexcept;

template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
constexpr bool operator>=(const Left_Iterator &left,
                          const Right_Iterator &right) noexcept;

template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
constexpr bool operator<=(const Left_Iterator &left,
                          const Right_Iterator &right) noexcept;

template <is_Random_Iterator Iterator>
constexpr typename Iterator::Self
operator+(const Iterator &iterator, const typename Iterator::difference_type n);

template <is_Random_Iterator Iterator>
constexpr typename Iterator::Self
operator-(const Iterator &iterator, const typename Iterator::difference_type n);

template <is_Random_Iterator Iterator>
constexpr typename Iterator::Self &
operator+=(Iterator &iterator, const typename Iterator::difference_type n);

template <is_Random_Iterator Iterator>
constexpr typename Iterator::Self &
operator-=(Iterator &iterator, const typename Iterator::difference_type n);

template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
constexpr typename Left_Iterator::difference_type
operator-(const Left_Iterator &left, const Right_Iterator &right) noexcept;

template <is_Forward_Iterator Iterator>
std::ostream &operator<<(std::ostream &os, const Iterator &it);

template <is_Forward_Iterator Iterator>
std::ostream &operator<<(std::ostream &os, const Iterator &&it);
} // namespace llframe