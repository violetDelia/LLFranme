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
 * @file iterator.hpp
 * @brief 迭代器接口
 * @details
 * @author 时光丶人爱
 * @date 2023-12-23
 * @see If you have any questions about the code or if you think there is a better way to implement
 * it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_ITERATOR_HPP__
#define __LLFRAME_ITERATOR_HPP__
#ifdef __LLFRAME_USE_MODULE__
#else
#endif // __LLFRAME_USE_MODULE__
#include <type_traits>
#include <iterator>

// define other
namespace llframe
{

}

// define iterator
namespace llframe
{

    template <class Implement>
    class Const_Forward_Iterator
    {
    private:
        using Self = Const_Forward_Iterator;

    public:
        using difference_type = Implement::difference_type;
        using value_type = Implement::value_type;
        using pointer = Implement::pointer;
        using reference = Implement::reference;
        using iterator_category = Implement::iterator_category;
        static_assert(std::is_same_v<iterator_category, std::forward_iterator_tag>);

    public:
        [[nodiscard]] constexpr bool operator==(const Self &other) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Self &other) const noexcept;
        [[nodiscard]] constexpr reference operator*() const;
        [[nodiscard]] constexpr pointer operator->() const;
        constexpr Self &operator++();
        constexpr Self &operator++(int);
    };

    template <class Implement>
    class Const_Bidirectional_Iterator : public Const_Forward_Iterator<Implement>
    {
    private:
        using Self = Const_Bidirectional_Iterator;

    public:
        using difference_type = Implement::difference_type;
        using value_type = Implement::value_type;
        using pointer = Implement::pointer;
        using reference = Implement::reference;
        using iterator_category = Implement::iterator_category;
        static_assert(std::is_same_v<iterator_category, std::bidirectional_iterator_tag>);

    public:
        constexpr Self &operator--();
        constexpr Self &operator--(int);
    };

    template <class Implement>
    class Const_Random_Iterator : public Const_Bidirectional_Iterator<Implement>
    {
    private:
        using Self = Const_Random_Iterator;

    public:
        using difference_type = Implement::difference_type;
        using value_type = Implement::value_type;
        using pointer = Implement::pointer;
        using reference = Implement::reference;
        using iterator_category = Implement::iterator_category;
        static_assert(std::is_same_v<iterator_category, std::random_access_iterator_tag>);

    public:
        [[nodiscard]] constexpr bool
        operator<(const Self &other) const noexcept;
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

    template <class Implement>
    class Forward_Iterator : public Const_Forward_Iterator<Implement>
    {
    private:
        using Self = Forward_Iterator;

    public:
        using difference_type = Implement::difference_type;
        using value_type = Implement::value_type;
        using pointer = Implement::pointer;
        using reference = Implement::reference;
        using iterator_category = Implement::iterator_category;
        static_assert(std::is_same_v<iterator_category, std::forward_iterator_tag>);

    public:
        [[nodiscard]] constexpr bool operator==(const Self &other) const noexcept;
        [[nodiscard]] constexpr bool operator!=(const Self &other) const noexcept;
        [[nodiscard]] constexpr reference operator*() const;
        [[nodiscard]] constexpr pointer operator->() const;
        constexpr Self &operator++();
        constexpr Self &operator++(int);
    };

    template <class Implement>
    class Bidirectional_Iterator : public Const_Bidirectional_Iterator<Implement>
    {
    private:
        using Self = Bidirectional_Iterator;

    public:
        using difference_type = Implement::difference_type;
        using value_type = Implement::value_type;
        using pointer = Implement::pointer;
        using reference = Implement::reference;
        using iterator_category = Implement::Riterator_category;
        static_assert(std::is_same_v<iterator_category, std::bidirectional_iterator_tag>);

    public:
        constexpr Self &operator--();
        constexpr Self &operator--(int);
    };

    template <class Implement>
    class Random_Iterator : public Const_Random_Iterator<Implement>
    {
    private:
        using Self = Random_Iterator;

    public:
        using difference_type = Implement::difference_type;
        using value_type = Implement::value_type;
        using pointer = Implement::pointer;
        using reference = Implement::reference;
        using iterator_category = Implement::iterator_category;
        static_assert(std::is_same_v<iterator_category, std::random_access_iterator_tag>);

    public:
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

} // llframe
// implement iterator
namespace llframe
{

    template <class Implement>
    constexpr bool
    Const_Forward_Iterator<Implement>::operator==(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator==(other);
    };

    template <class Implement>
    constexpr bool
    Const_Forward_Iterator<Implement>::operator!=(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator!=(other);
    };

    template <class Implement>
    constexpr Const_Forward_Iterator<Implement>::reference
    Const_Forward_Iterator<Implement>::operator*() const
    {
        return static_cast<Implement *>(this)->operator*();
    };

    template <class Implement>
    constexpr Const_Forward_Iterator<Implement>::pointer
    Const_Forward_Iterator<Implement>::operator->() const
    {
        return static_cast<Implement *>(this)->operator->();
    };

    template <class Implement>
    constexpr Const_Forward_Iterator<Implement> &
    Const_Forward_Iterator<Implement>::operator++()
    {
        return static_cast<Implement *>(this)->operator++();
    };

    template <class Implement>
    constexpr Const_Forward_Iterator<Implement> &
    Const_Forward_Iterator<Implement>::operator++(int x)
    {
        return static_cast<Implement *>(this)->operator++(x);
    };

    template <class Implement>
    constexpr Const_Bidirectional_Iterator<Implement> &
    Const_Bidirectional_Iterator<Implement>::operator--()
    {
        return static_cast<Implement *>(this)->operator--();
    };

    template <class Implement>
    constexpr Const_Bidirectional_Iterator<Implement> &
    Const_Bidirectional_Iterator<Implement>::operator--(int x)
    {
        return static_cast<Implement *>(this)->operator--(x);
    };

    template <class Implement>
    constexpr bool
    Const_Random_Iterator<Implement>::operator<(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator<(other);
    };

    template <class Implement>
    constexpr bool
    Const_Random_Iterator<Implement>::operator>(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator>(other);
    };

    template <class Implement>
    constexpr bool
    Const_Random_Iterator<Implement>::operator>=(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator>=(other);
    };

    template <class Implement>
    constexpr bool
    Const_Random_Iterator<Implement>::operator<=(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator<=(other);
    };

    template <class Implement>
    constexpr Const_Random_Iterator<Implement>::reference
    Const_Random_Iterator<Implement>::operator[](difference_type n) const
    {
        return static_cast<Implement *>(this)->operator[](n);
    };

    template <class Implement>
    constexpr Const_Random_Iterator<Implement> &
    Const_Random_Iterator<Implement>::operator+=(difference_type n)
    {
        return static_cast<Implement *>(this)->operator+=(n);
    };

    template <class Implement>
    constexpr Const_Random_Iterator<Implement> &
    Const_Random_Iterator<Implement>::operator-=(difference_type n)
    {
        return static_cast<Implement *>(this)->operator-=(n);
    };

    template <class Implement>
    constexpr Const_Random_Iterator<Implement>
    Const_Random_Iterator<Implement>::operator+(difference_type n) const
    {
        return static_cast<Implement *>(this)->operator+(n);
    };

    template <class Implement>
    constexpr Const_Random_Iterator<Implement>
    Const_Random_Iterator<Implement>::operator-(difference_type n) const
    {
        return static_cast<Implement *>(this)->operator-(n);
    };

    template <class Implement>
    constexpr Const_Random_Iterator<Implement>::difference_type
    Const_Random_Iterator<Implement>::operator-(const Self &left) const
    {
        return static_cast<Implement *>(this)->operator-(left);
    };

    template <class Implement>
    constexpr bool
    Forward_Iterator<Implement>::operator==(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator==(other);
    };

    template <class Implement>
    constexpr bool
    Forward_Iterator<Implement>::operator!=(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator!=(other);
    };

    template <class Implement>
    constexpr Forward_Iterator<Implement>::reference
    Forward_Iterator<Implement>::operator*() const
    {
        return static_cast<Implement *>(this)->operator*();
    };

    template <class Implement>
    constexpr Forward_Iterator<Implement>::pointer
    Forward_Iterator<Implement>::operator->() const
    {
        return static_cast<Implement *>(this)->operator->();
    };

    template <class Implement>
    constexpr Forward_Iterator<Implement> &
    Forward_Iterator<Implement>::operator++()
    {
        return static_cast<Implement *>(this)->operator++();
    };

    template <class Implement>
    constexpr Forward_Iterator<Implement> &
    Forward_Iterator<Implement>::operator++(int x)
    {
        return static_cast<Implement *>(this)->operator++(x);
    };

    template <class Implement>
    constexpr Bidirectional_Iterator<Implement> &
    Bidirectional_Iterator<Implement>::operator--()
    {
        return static_cast<Implement *>(this)->operator--();
    };

    template <class Implement>
    constexpr Bidirectional_Iterator<Implement> &
    Bidirectional_Iterator<Implement>::operator--(int x)
    {
        return static_cast<Implement *>(this)->operator--(x);
    };

    template <class Implement>
    constexpr bool
    Random_Iterator<Implement>::operator<(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator<(other);
    };

    template <class Implement>
    constexpr bool
    Random_Iterator<Implement>::operator>(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator>(other);
    };

    template <class Implement>
    constexpr bool
    Random_Iterator<Implement>::operator>=(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator>=(other);
    };

    template <class Implement>
    constexpr bool
    Random_Iterator<Implement>::operator<=(const Self &other) const noexcept
    {
        return static_cast<Implement *>(this)->operator<=(other);
    };

    template <class Implement>
    constexpr Random_Iterator<Implement>::reference
    Random_Iterator<Implement>::operator[](difference_type n) const
    {
        return static_cast<Implement *>(this)->operator[](n);
    };

    template <class Implement>
    constexpr Random_Iterator<Implement> &
    Random_Iterator<Implement>::operator+=(difference_type n)
    {
        return static_cast<Implement *>(this)->operator+=(n);
    };

    template <class Implement>
    constexpr Random_Iterator<Implement> &
    Random_Iterator<Implement>::operator-=(difference_type n)
    {
        return static_cast<Implement *>(this)->operator-=(n);
    };

    template <class Implement>
    constexpr Random_Iterator<Implement>
    Random_Iterator<Implement>::operator+(difference_type n) const
    {
        return static_cast<Implement *>(this)->operator+(n);
    };

    template <class Implement>
    constexpr Random_Iterator<Implement>
    Random_Iterator<Implement>::operator-(difference_type n) const
    {
        return static_cast<Implement *>(this)->operator-(n);
    };

    template <class Implement>
    constexpr Random_Iterator<Implement>::difference_type
    Random_Iterator<Implement>::operator-(const Self &left) const
    {
        return static_cast<Implement *>(this)->operator-(left);
    };

} // namespace llframe

#endif //__LLFRAME_ITERATOR_HPP__
