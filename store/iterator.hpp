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
 * @brief 迭代器
 * @details
 * @author 时光丶人爱
 * @date 2023-12-23
 * @see If you have any questions about the code or if you think there is a better way to Iterator
 * it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_ITERATOR_HPP__
#define __LLFRAME_ITERATOR_HPP__
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.exception;
import llframe.core.helper;
#else
#include "core/exception.hpp"
#include "core/helper.hpp"
#endif // __LLFRAME_USE_MODULE__
#include "core/exception_helper.hpp"
#include <type_traits>
#include <iterator>

// define other
namespace llframe
{

    template <class Container>
    class Const_Forward_Iterator;

    template <class Container>
    class Forward_Iterator;

    template <class Container>
    class Const_Bidirectional_Iterator;

    template <class Container>
    class Const_Random_Iterator;

    template <class _Ty>
    struct _Is_Forward_Iterator : std::false_type
    {
    };

    template <template <class> typename _Ty, class _Arg>
    struct _Is_Forward_Iterator<_Ty<_Arg>>
        : std::is_base_of<Const_Forward_Iterator<_Arg>, _Ty<_Arg>>
    {
    };

    template <class _Ty>
    struct _Is_Bidirectional_Iterator : std::false_type
    {
    };

    template <template <class> typename _Ty, class _Arg>
    struct _Is_Bidirectional_Iterator<_Ty<_Arg>>
        : std::is_base_of<Const_Bidirectional_Iterator<_Arg>, _Ty<_Arg>>
    {
    };

    template <class _Ty>
    struct _Is_Random_Iterator : std::false_type
    {
    };

    template <template <class> typename _Ty, class _Arg>
    struct _Is_Random_Iterator<_Ty<_Arg>>
        : std::is_base_of<Const_Random_Iterator<_Arg>, _Ty<_Arg>>
    {
    };

    template <class Ty>
    concept is_Forward_Iterator = _Is_Forward_Iterator<Ty>::value;

    template <class Ty>
    concept is_Bidirectional_Iterator = _Is_Bidirectional_Iterator<Ty>::value;

    template <class Ty>
    concept is_Random_Iterator = _Is_Bidirectional_Iterator<Ty>::value;
}
// define operator
namespace llframe
{

    template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
    [[nodiscard]] constexpr bool
    operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

    template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
    [[nodiscard]] constexpr bool
    operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

    template <is_Forward_Iterator Iterator>
    [[nodiscard]] constexpr typename Iterator::reference
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
    [[nodiscard]] constexpr bool
    operator>(const Left_Iterator &left, const Right_Iterator &right) noexcept;

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    [[nodiscard]] constexpr bool
    operator<(const Left_Iterator &left, const Right_Iterator &right) noexcept;

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    [[nodiscard]] constexpr bool
    operator>=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    [[nodiscard]] constexpr bool
    operator<=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

    template <is_Random_Iterator Iterator>
    [[nodiscard]] constexpr typename Iterator::Self
    operator+(const Iterator &iterator, const typename Iterator::difference_type n);

    template <is_Random_Iterator Iterator>
    [[nodiscard]] constexpr typename Iterator::Self
    operator-(const Iterator &iterator, const typename Iterator::difference_type n);

    template <is_Random_Iterator Iterator>
    constexpr typename Iterator::Self &
    operator+=(Iterator &iterator, const typename Iterator::difference_type n);

    template <is_Random_Iterator Iterator>
    constexpr typename Iterator::Self &
    operator-=(Iterator &iterator, const typename Iterator::difference_type n);

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    [[nodiscard]] constexpr typename Left_Iterator::difference_type
    operator-(const Left_Iterator &left, const Right_Iterator &right) noexcept;
}
// define iterator
namespace llframe
{

    template <class Container>
    class Const_Forward_Iterator
    {
    private:
        using Self = Const_Forward_Iterator;

    protected:
        using address = std::remove_const_t<typename Container::pointer>;

    public:
        using difference_type = typename Container::difference_type;
        using value_type = typename Container::value_type;
        using pointer = typename add_const_t<typename Container::pointer>;
        using reference = typename add_const_t<typename Container::reference>;
        using iterator_category = std::forward_iterator_tag;

    protected:
        address _pointer{};

    public:
        constexpr Const_Forward_Iterator() noexcept = default;
        constexpr Const_Forward_Iterator(const Self &other) noexcept = default;
        constexpr Const_Forward_Iterator(Self &&other) noexcept = default;
        constexpr Self &operator=(const Self &other) noexcept = default;
        constexpr Self &operator=(Self &&other) noexcept = default;
        constexpr Const_Forward_Iterator(address pointer) noexcept;
        constexpr virtual ~Const_Forward_Iterator() = default;

    public:
        [[nodiscard]] constexpr pointer operator->() const noexcept;

    private:
        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::reference operator*(const Iterator &iterator) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator++(Iterator &iterator);

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self operator++(Iterator &iterator, int);
    };

    template <class Container>
    class Const_Bidirectional_Iterator : public Const_Forward_Iterator<Container>
    {

    private:
        using Self = Const_Bidirectional_Iterator;
        using Base = Const_Forward_Iterator<Container>;

    protected:
        using address = typename Base::address;

    public:
        using difference_type = typename Base::difference_type;
        using value_type = typename Base::value_type;
        using pointer = typename Base::pointer;
        using reference = typename Base::reference;
        using iterator_category = std::bidirectional_iterator_tag;

    public:
        using Base::Const_Forward_Iterator;
        constexpr ~Const_Bidirectional_Iterator() override = default;

    private:
        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::reference
        operator*(const Iterator &iterator) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator++(Iterator &iterator);

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self operator++(Iterator &iterator, int);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator--(Iterator &iterator);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self operator--(Iterator &iterator, int);
    };

    template <class Container>
    class Const_Random_Iterator : public Const_Bidirectional_Iterator<Container>
    {

    private:
        using Self = Const_Random_Iterator;
        using Base = Const_Bidirectional_Iterator<Container>;

    protected:
        using address = typename Base::address;

    public:
        using difference_type = typename Base::difference_type;
        using value_type = typename Base::value_type;
        using pointer = typename Base::pointer;
        using reference = typename Base::reference;
        using iterator_category = std::random_access_iterator_tag;

    public:
        using Base::Const_Bidirectional_Iterator;
        constexpr ~Const_Random_Iterator() override = default;

    public:
        [[nodiscard]] constexpr reference operator[](const difference_type n) const;

    private:
        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::reference
        operator*(const Iterator &iterator) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator++(Iterator &iterator);

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self operator++(Iterator &iterator, int);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator--(Iterator &iterator);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self operator--(Iterator &iterator, int);

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator>(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator<(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator>=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator<=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self
        operator+(const Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self
        operator-(const Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self &
        operator+=(Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self &
        operator-=(Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr typename Left_Iterator::difference_type
        operator-(const Left_Iterator &left, const Right_Iterator &right) noexcept;
    };

    template <class Container>
    class Forward_Iterator : public Const_Forward_Iterator<Container>
    {

    private:
        using Self = Forward_Iterator;
        using Base = Const_Forward_Iterator<Container>;

    protected:
        using address = typename Base::address;

    public:
        using difference_type = typename Base::difference_type;
        using value_type = typename Base::value_type;
        using pointer = typename std::remove_const_t<typename Base::pointer>;
        using reference = typename std::remove_const_t<
            typename std::remove_reference_t<typename Base::reference>> &;
        using iterator_category = std::forward_iterator_tag;

    public:
        using Base::Const_Forward_Iterator;
        constexpr virtual ~Forward_Iterator() = default;

    public:
        [[nodiscard]] constexpr pointer operator->() const noexcept;

    private:
        using Base::operator->;

    private:
        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::reference
        operator*(const Iterator &iterator) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator++(Iterator &iterator);

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self operator++(Iterator &iterator, int);
    };

    template <class Container>
    class Bidirectional_Iterator : public Const_Bidirectional_Iterator<Container>
    {

    private:
        using Self = Bidirectional_Iterator;
        using Base = Const_Bidirectional_Iterator<Container>;

    protected:
        using address = typename Base::address;

    public:
        using difference_type = typename Base::difference_type;
        using value_type = typename Base::value_type;
        using pointer = typename std::remove_const_t<typename Base::pointer>;
        using reference = typename std::remove_const_t<
            typename std::remove_reference_t<typename Base::reference>> &;
        using iterator_category = std::bidirectional_iterator_tag;

    public:
        using Base::Const_Bidirectional_Iterator;
        constexpr ~Bidirectional_Iterator() override = default;

    public:
        [[nodiscard]] constexpr pointer operator->() const noexcept;

    private:
        using Base::operator->;

    private:
        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::reference
        operator*(const Iterator &iterator) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator++(Iterator &iterator);

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self operator++(Iterator &iterator, int);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator--(Iterator &iterator);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self operator--(Iterator &iterator, int);
    };

    template <class Container>
    class Random_Iterator : public Const_Random_Iterator<Container>
    {
    private:
        using Self = Random_Iterator;
        using Base = Const_Random_Iterator<Container>;

    protected:
        using address = typename Base::address;

    public:
        using difference_type = typename Base::difference_type;
        using value_type = typename Base::value_type;
        using pointer = typename std::remove_const_t<typename Base::pointer>;
        using reference = typename std::remove_const_t<
            typename std::remove_reference_t<typename Base::reference>> &;
        using iterator_category = std::bidirectional_iterator_tag;

    public:
        using Base::Const_Random_Iterator;
        constexpr ~Random_Iterator() override = default;

    public:
        [[nodiscard]] constexpr pointer operator->() const noexcept;
        [[nodiscard]] constexpr reference operator[](const difference_type n) const;

    private:
        using Base::operator->;
        using Base::operator[];

    private:
        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
        friend constexpr bool
        operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::reference
        operator*(const Iterator &iterator) noexcept;

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator++(Iterator &iterator);

        template <is_Forward_Iterator Iterator>
        friend constexpr typename Iterator::Self operator++(Iterator &iterator, int);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self &operator--(Iterator &iterator);

        template <is_Bidirectional_Iterator Iterator>
        friend constexpr typename Iterator::Self operator--(Iterator &iterator, int);

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator>(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator<(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator>=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr bool
        operator<=(const Left_Iterator &left, const Right_Iterator &right) noexcept;

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self
        operator+(const Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self
        operator-(const Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self &
        operator+=(Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Iterator>
        friend constexpr typename Iterator::Self &
        operator-=(Iterator &iterator, const typename Iterator::difference_type n);

        template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
        friend constexpr typename Left_Iterator::difference_type
        operator-(const Left_Iterator &left, const Right_Iterator &right) noexcept;
    };
} // llframe

// impletment operator
namespace llframe
{
    template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
    constexpr bool
    operator==(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer == right._pointer;
    }

    template <is_Forward_Iterator Left_Iterator, is_Forward_Iterator Right_Iterator>
    constexpr bool
    operator!=(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer != right._pointer;
    }

    template <is_Forward_Iterator Iterator>
    constexpr typename Iterator::reference operator*(const Iterator &iterator) noexcept
    {
        return *iterator._pointer;
    };

    template <is_Forward_Iterator Iterator>
    constexpr typename Iterator::Self &operator++(Iterator &iterator)
    {
        ++iterator._pointer;
        return iterator;
    };

    template <is_Forward_Iterator Iterator>
    constexpr typename Iterator::Self operator++(Iterator &iterator, int)
    {
        using Self = typename Iterator::Self;
        Self temp_ = iterator;
        ++iterator._pointer;
        return temp_;
    };

    template <is_Bidirectional_Iterator Iterator>
    constexpr typename Iterator::Self &operator--(Iterator &iterator)
    {
        --iterator._pointer;
        return iterator;
    };

    template <is_Bidirectional_Iterator Iterator>
    constexpr typename Iterator::Self operator--(Iterator &iterator, int)
    {
        using Self = typename Iterator::Self;
        Self temp_ = iterator;
        --iterator._pointer;
        return temp_;
    };

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    constexpr bool
    operator>(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer > right._pointer;
    };

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    constexpr bool
    operator<(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer < right._pointer;
    };

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    constexpr bool
    operator>=(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer >= right._pointer;
    };

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    constexpr bool
    operator<=(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer <= right._pointer;
    };

    template <is_Random_Iterator Iterator>
    constexpr typename Iterator::Self
    operator+(const Iterator &iterator, const typename Iterator::difference_type n)
    {
        using Self = typename Iterator::Self;
        Self temp_ = iterator;
        return temp_ += n;
    };

    template <is_Random_Iterator Iterator>
    constexpr typename Iterator::Self
    operator-(const Iterator &iterator, const typename Iterator::difference_type n)
    {
        using Self = typename Iterator::Self;
        Self temp_ = iterator;
        return temp_ -= n;
    };

    template <is_Random_Iterator Iterator>
    constexpr typename Iterator::Self &
    operator+=(Iterator &iterator, const typename Iterator::difference_type n)
    {
        iterator._pointer += n;
        return iterator;
    };

    template <is_Random_Iterator Iterator>
    constexpr typename Iterator::Self &
    operator-=(Iterator &iterator, const typename Iterator::difference_type n)
    {
        iterator._pointer -= n;
        return iterator;
    };

    template <is_Random_Iterator Left_Iterator, is_Random_Iterator Right_Iterator>
    [[nodiscard]] constexpr typename Left_Iterator::difference_type
    operator-(const Left_Iterator &left, const Right_Iterator &right) noexcept
    {
        return left._pointer - right._pointer;
    };
} // llframe

// impletment iterator
namespace llframe
{
    template <class Container>
    constexpr Const_Forward_Iterator<Container>::Const_Forward_Iterator(
        address pointer) noexcept : _pointer(pointer){};

    template <class Container>
    constexpr Const_Forward_Iterator<Container>::pointer
    Const_Forward_Iterator<Container>::operator->() const noexcept
    {
        return this->_pointer;
    };

    template <class Container>
    constexpr Forward_Iterator<Container>::pointer
    Forward_Iterator<Container>::operator->() const noexcept
    {
        return this->_pointer;
    };

    template <class Container>
    constexpr Bidirectional_Iterator<Container>::pointer
    Bidirectional_Iterator<Container>::operator->() const noexcept
    {
        return this->_pointer;
    }

    template <class Container>
    constexpr Const_Random_Iterator<Container>::reference
    Const_Random_Iterator<Container>::operator[](const difference_type n) const
    {
        return *(*this + n);
    }

    template <class Container>
    constexpr Random_Iterator<Container>::pointer
    Random_Iterator<Container>::operator->() const noexcept
    {
        return this->_pointer;
    };

    template <class Container>
    constexpr Random_Iterator<Container>::reference
    Random_Iterator<Container>::operator[](const difference_type n) const
    {
        return *(*this + n);
    }

}
#endif __LLFRAME_ITERATOR_HPP__