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
 * @file size_iterator.hpp
 * @brief size的迭代器
 * @details
 * @author 时光丶人爱
 * @date 2023-12-23
 * @see If you have any questions about the code or if you think there is a better way to implement
 * it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_SIZE_ITERATOR_HPP__
#define __LLFRAME_SIZE_ITERATOR_HPP__
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.helper;
import llframe.core.iterator;
#else
#include "core/helper.hpp"
#include "core/iterator.hpp"
#endif // __LLFRAME_USE_MODULE__
#include <type_traits>

// size iterator
namespace llframe
{
    template <size_t Dims>
    class Size;

    template <class Ty>
    concept is_Size = is_instance<Ty, Size>;

    template <is_Size Size>
    class Const_Size_Iterator : public Const_Random_Iterator<Const_Size_Iterator<Size>>
    {
    private:
        using Self = Const_Size_Iterator;
        using address = Size::pointer;

    public:
        using difference_type = typename Size::difference_type;
        using value_type = typename Size::value_type;
        using pointer = const typename Size::pointer;
        using reference = const typename Size::reference;
        using iterator_category = typename Size::iterator_category;

    private:
        address element;

    public:
        constexpr Const_Size_Iterator() noexcept = default;
        constexpr Const_Size_Iterator(const Self &other) noexcept = default;
        constexpr Const_Size_Iterator(Self &&other) noexcept = default;
        constexpr Self &operator=(const Self &other) noexcept = default;
        constexpr Self &operator=(Self &&other) noexcept = default;

    public:
        [[nodiscard]] constexpr bool operator==(const Self &other) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Self &other) const noexcept;
        [[nodiscard]] constexpr reference operator*() const;
        [[nodiscard]] constexpr pointer operator->() const;
        constexpr Self &operator++();
        constexpr Self &operator++(int);
        constexpr Self &operator--();
        constexpr Self &operator--(int);
        [[nodiscard]] constexpr bool operator<(const Self &other) const noexcept;
        [[nodiscard]] constexpr bool operator>(const Self &other) const noexcept;
        [[nodiscard]] constexpr bool operator>=(const Self &other) const noexcept;
        [[nodiscard]] constexpr bool operator<=(const Self &other) const noexcept;
        [[nodiscard]] constexpr reference operator[](const difference_type n) const;
        constexpr Self &operator+=(const difference_type n);
        constexpr Self &operator-=(const difference_type n);
        [[nodiscard]] constexpr Self operator+(const difference_type n) const;
        [[nodiscard]] constexpr Self operator-(const difference_type n) const;
        [[nodiscard]] constexpr difference_type operator-(const Self &left) const;
    };

    template <is_Size Size>
    class Size_Iterator : public Random_Iterator<Const_Size_Iterator<Size>>
    {
    private:
        using Self = Size_Iterator;
        using const_iterator = Const_Size_Iterator<Size>;

    public:
        using difference_type = typename Size::difference_type;
        using value_type = typename Size::value_type;
        using pointer = typename Size::pointer;
        using reference = typename Size::reference;
        using iterator_category = typename Size::random_access_iterator_tag;

    public:
        // [[nodiscard]] constexpr reference operator*() const;
        // [[nodiscard]] constexpr pointer operator->() const;
        // constexpr Self &operator++();
        // constexpr Self &operator++(int);
        // constexpr Self &operator--();
        // constexpr Self &operator--(int);
        // [[nodiscard]] constexpr reference operator[](const difference_type n) const;
        // constexpr Self &operator+=(const difference_type n);
        // constexpr Self &operator-=(const difference_type n);
        // [[nodiscard]] constexpr Self operator+(const difference_type n) const;
        // [[nodiscard]] constexpr Self operator-(const difference_type n) const;
    };

} // llframe
// implement size iterator
namespace llframe
{
    template <is_Size Size>
    constexpr bool Const_Size_Iterator<Size>::operator==(const Self &other) const noexcept
    {
        return element == other.element;
    };

    template <is_Size Size>
    constexpr bool Const_Size_Iterator<Size>::operator!=(const Self &other) const noexcept
    {
        return element != other.element;
    };

    template <is_Size Size>
    constexpr const Const_Size_Iterator<Size>::reference
    Const_Size_Iterator<Size>::operator*() const
    {
        return *element;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size>::pointer
    Const_Size_Iterator<Size>::operator->() const
    {
        return element;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size> &Const_Size_Iterator<Size>::operator++()
    {
        ++element;
        return *this;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size> &Const_Size_Iterator<Size>::operator++(int)
    {
        Self _temp = *this;
        ++element;
        return _temp;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size> &Const_Size_Iterator<Size>::operator--()
    {
        --element;
        return *this;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size> &Const_Size_Iterator<Size>::operator--(int)
    {
        Self _temp = *this;
        --element;
        return _temp;
    };

    template <is_Size Size>
    constexpr bool
    Const_Size_Iterator<Size>::operator<(const Self &other)
        const noexcept
    {
        return element < other.element;
    };

    template <is_Size Size>
    constexpr bool
    Const_Size_Iterator<Size>::operator>(const Self &other)
        const noexcept
    {
        return element > other.element;
    };

    template <is_Size Size>
    constexpr bool Const_Size_Iterator<Size>::operator>=(const Self &other) const noexcept
    {
        return element >= other.element;
    };

    template <is_Size Size>
    constexpr bool Const_Size_Iterator<Size>::operator<=(const Self &other) const noexcept
    {
        return element <= other.element;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size>::reference
    Const_Size_Iterator<Size>::operator[](Size::difference_type n) const
    {
        return *(*this + n);
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size> &
    Const_Size_Iterator<Size>::operator+=(Size::difference_type n)
    {
        element += n;
        return *this;
    };

    // template <is_Size Size>
    // constexpr Const_Size_Iterator<Size> &
    // Const_Size_Iterator<Size>::operator-=(Size::difference_type n)
    // {
    //     element - = n;
    //     return *this;
    // };

    // template <is_Size Size>
    // constexpr Const_Size_Iterator<Size>
    // Const_Size_Iterator<Size>::operator+(Size::difference_type n) const
    // {
    //     Self _temp = *this;
    //     return _temp += n;
    // };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size>
    Const_Size_Iterator<Size>::operator-(Size::difference_type n) const
    {
        Self _temp = *this;
        return _temp -= n;
    };

    template <is_Size Size>
    constexpr Const_Size_Iterator<Size>::difference_type
    Const_Size_Iterator<Size>::operator-(const Const_Size_Iterator<Size> &left) const
    {
        return element - left.element;
    };

    // template <is_Size Size>
    // constexpr Size::reference Size_Iterator<Size>::operator*() const
    // {
    //     return const_cast<reference>(Base::operator*());
    // };
} // llframe

#endif //__LLFRAME_SIZE_ITERATOR_HPP__