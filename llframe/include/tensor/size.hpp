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
 * @file size.hpp
 * @brief 形状
 * @details 具有移动语义.
 * @author 时光丶人爱
 * @date 2023-12-9
 * @see If you have any questions about the code or if you think there is a
 * better way to implement it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_SIZE_HPP__
#define __LLFRAME_SIZE_HPP__
#include <initializer_list>
#include <type_traits>
#include <iostream>
#include <iterator>
#include "core/exception_helper.hpp"
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.base_type;
import llframe.memory.allocator;
import llframe.core.helper;
import llframe.core.iterator;
#else
#include "core/base_type.hpp"
#include "memory/allocator.hpp"
#include "core/iterator.hpp"
#include "core/helper.hpp"
#endif // __LLFRAME_USE_MODULE__

// define Array
namespace llframe {
/**
 * @brief 数组 
 * @tparam Dims 维度
 */
template <class Ty, size_t Dims>
class Array {
private:
    using Self = Array<Ty, Dims>;

public:
    using value_type = Ty;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    using iterator = Random_Iterator<Self>;
    using const_iterator = Const_Random_Iterator<Self>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
    using allocator = Allocator<value_type, HOST>;

public:
    static const constinit size_t Dims = Dims;

protected:
    pointer _begin{};
    pointer _end{};

public:
    constexpr Array() noexcept;
    constexpr Array(const Self &other) noexcept;
    constexpr Array(Self &&other) noexcept;
    constexpr Array(std::initializer_list<Ty> list) noexcept;
    template <std::input_iterator It>
    constexpr Array(It first, It last) noexcept;
    constexpr Array &operator=(const Self &other) noexcept;
    constexpr Array &operator=(Self &&other) noexcept;
    constexpr virtual ~Array() noexcept;

public:
    constexpr virtual iterator begin() noexcept;
    constexpr virtual const_iterator begin() const noexcept;
    constexpr virtual iterator end() noexcept;
    constexpr virtual const_iterator end() const noexcept;

    constexpr virtual reverse_iterator rbegin() noexcept;
    constexpr virtual const_reverse_iterator rbegin() const noexcept;
    constexpr virtual reverse_iterator rend() noexcept;
    constexpr virtual const_reverse_iterator rend() const noexcept;

    constexpr virtual const_iterator cbegin() const noexcept;
    constexpr virtual const_iterator cend() const noexcept;
    constexpr virtual const_reverse_iterator crbegin() const noexcept;
    constexpr virtual const_reverse_iterator crend() const noexcept;

public:
    /**
     * @brief 元素个数
     *
     *
     * @return size_type
     */
    [[nodiscard]] consteval size_t size() const noexcept;

    [[nodiscard]] constexpr reference operator[](size_type index);

    /**
     * @brief 索引处的维度长度  动态的get
     *
     * @tparam Index 整数
     * @param index 索引
     * @return  size_type
     */
    [[nodiscard]] constexpr virtual value_type at(size_type index) const;

protected:
    [[nodiscard]] constexpr virtual bool _empty() const;

private:
    template <size_t Dims, class Ty, is_Device Device>
    friend class _Tensor_Base;
};

template <class Ty, class Other_Ty, size_t Dims, size_t Other_Dims>
[[nodiscard]] consteval bool operator==(Array<Ty, Dims> &left,
                                        Array<Other_Ty, Other_Dims> &right);

template <class Ty, class Other_Ty, size_t Dims, size_t Other_Dims>
[[nodiscard]] consteval bool operator!=(Array<Ty, Dims> &left,
                                        Array<Other_Ty, Other_Dims> &right);

template <class Ty, size_t Dims>
[[nodiscard]] constexpr bool operator==(Array<Ty, Dims> &left,
                                        Array<Ty, Dims> &right);

template <class Ty, size_t Dims>
[[nodiscard]] constexpr bool operator!=(Array<Ty, Dims> &left,
                                        Array<Ty, Dims> &right);
} // namespace llframe

// define Size
namespace llframe {
/**
 * @brief 形状
 * 如果内存为空,用at访问会返回0,而不是空指针错误.
 * @tparam Dims
 */
template <size_t Dims>
class Size : public Array<size_t, Dims> {
private:
    using Self = Size<Dims>;
    using Base = Array<size_t, Dims>;

public:
    using value_type = Base::value_type;
    using pointer = Base::pointer;
    using const_pointer = Base::const_pointer;
    using reference = Base::reference;
    using const_reference = Base::const_reference;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;
    using iterator_category = Base::iterator_category;
    using iterator = Base::iterator;
    using const_iterator = Base::const_iterator;
    using reverse_iterator = Base::reverse_iterator;
    using const_reverse_iterator = Base::const_reverse_iterator;

protected:
    using allocator = Base::allocator;

private:
    using Base::size;
    using Base::Array;

public:
    template <is_Integral... Integrals>
    constexpr Size(Integrals... values) noexcept;
    constexpr Size() noexcept = default;
    constexpr Size(const Self &other) noexcept  = default;
    constexpr Size(Self &&other) noexcept;
    constexpr Size &operator=(const Self &other) noexcept = default;
    constexpr Size &operator=(Self &&other) noexcept;

public:
    [[nodiscard]] consteval size_type dims() const noexcept;
};

template <class _Ty>
struct _Is_Size : std::false_type {};

template <template <size_t> class _Ty, size_t _Arg>
struct _Is_Size<_Ty<_Arg>> : std::is_base_of<Size<_Arg>, _Ty<_Arg>> {};

template <class Ty>
concept is_Size = _Is_Size<Ty>::value;

template <is_Size Size>
std::ostream &operator<<(std::ostream &os, const Size &size);

template <is_Size Size>
std::ostream &operator<<(std::ostream &os, const Size &&size);

/**
 * @brief 构造size
 *
 * @tparam Integrals 整数
 * @param value 尺寸
 * @return Size<is_Integral... Integrals>
 */
template <is_Integral... Integrals>
[[nodiscard]] inline constexpr Size<sizeof...(Integrals)>
make_size(Integrals... value) noexcept;

template <size_t Dims>
[[nodiscard]] inline constexpr Size<Dims>
make_size(const Size<Dims> &size) noexcept;
} // namespace llframe

// impletment Array
namespace llframe {
template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::Array() noexcept :
    _begin(allocator::allocate(Self::Dims)), _end(_begin + Self::Dims) {
    allocator::construct(begin(), end());
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::Array(const Self &other) noexcept :
    _begin(allocator::allocate(Self::Dims)), _end(_begin + Self::Dims) {
    allocator::copy(other.begin(), other.end(), begin());
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::Array(Self &&other) noexcept :
    _begin(allocator::allocate(Self::Dims)), _end(_begin + Self::Dims) {
    allocator::move(other.begin(), other.end(), begin());
};
template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::Array(std::initializer_list<Ty> list) noexcept {
    Array(list.begin(), list.end());
};

template <class Ty, size_t Dims>
template <std::input_iterator It>
constexpr Array<Ty, Dims>::Array(It first, It last) noexcept {
    size_type init_len = std::distance(first, last);
    if (init_len >= Dims)
        allocator::move(begin(), end(), first);
    else {
        allocator::move(begin(), init_len, first);
        allocator::construct(begin() + init_len, end());
    }
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::Self &
Array<Ty, Dims>::operator=(const Self &other) noexcept {
    if (this != std::addressof(other)) {
        if (_empty()) {
            _begin = allocator::allocate(Self::Dims);
            _end = _begin + Self::Dims;
        }
        allocator::copy(other.begin(), other.end(), begin());
    }

    return *this;
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::Self &
Array<Ty, Dims>::operator=(Self &&other) noexcept {
    if (this != std::addressof(other)) {
        if (_empty()) {
            _begin = allocator::allocate(Self::Dims);
            _end = _begin + Self::Dims;
        }
        allocator::move(other.begin(), other.end(), begin());
    }
    return *this;
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::~Array() noexcept {
    if (_empty()) return;
    allocator::destroy(begin(), Dims);
    allocator::deallocate(_begin, Dims);
    _begin = nullptr;
    _end = nullptr;
};

template <class Ty, size_t Dims>
constexpr bool Array<Ty, Dims>::_empty() const {
    return (_begin == nullptr) && (_end == nullptr);
};

template <class Ty, size_t Dims>
consteval inline size_t Array<Ty, Dims>::size() const noexcept {
    return Self::Dims;
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::value_type
Array<Ty, Dims>::at(size_type index) const {
    if (static_cast<size_type>(index) >= Dims)
        __LLFRAME_THROW_EXCEPTION__(Out_Range);
    return *(begin() + index);
}

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::reference
Array<Ty, Dims>::operator[](size_type index) {
    if (static_cast<size_type>(index) >= Dims)
        __LLFRAME_THROW_EXCEPTION__(Out_Range);
    return begin()[index];
}

template <class Ty, class Other_Ty, size_t Dims, size_t Other_Dims>
consteval bool operator==(Array<Ty, Dims> &left,
                          Array<Other_Ty, Other_Dims> &right) {
    return false;
}

template <class Ty, class Other_Ty, size_t Dims, size_t Other_Dims>
consteval bool operator!=(Array<Ty, Dims> &left,
                          Array<Other_Ty, Other_Dims> &right) {
    return true;
}

template <class Ty, size_t Dims>
constexpr bool operator==(Array<Ty, Dims> &left, Array<Ty, Dims> &right) {
    for (int i{}; i < Dims; i++) {
        if (left.at(i) != right.at(i)) return false;
    }
    return true;
};

template <class Ty, size_t Dims>
constexpr bool operator!=(Array<Ty, Dims> &left, Array<Ty, Dims> &right) {
    return !(left == right);
};

} // namespace llframe

// impletment Array iterator
namespace llframe {
template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::iterator Array<Ty, Dims>::begin() noexcept {
    return iterator(_begin);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_iterator
Array<Ty, Dims>::begin() const noexcept {
    return const_iterator(_begin);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::iterator Array<Ty, Dims>::end() noexcept {
    return iterator(_end);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_iterator
Array<Ty, Dims>::end() const noexcept {
    return const_iterator(_end);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::reverse_iterator Array<Ty, Dims>::rbegin() noexcept {
    return reverse_iterator(_begin);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_reverse_iterator
Array<Ty, Dims>::rbegin() const noexcept {
    return const_reverse_iterator(_begin);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::reverse_iterator Array<Ty, Dims>::rend() noexcept {
    return reverse_iterator(_end);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_reverse_iterator
Array<Ty, Dims>::rend() const noexcept {
    return const_reverse_iterator(_end);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_iterator
Array<Ty, Dims>::cbegin() const noexcept {
    return const_iterator(_begin);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_iterator
Array<Ty, Dims>::cend() const noexcept {
    return const_iterator(_end);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_reverse_iterator
Array<Ty, Dims>::crbegin() const noexcept {
    return const_reverse_iterator(_begin);
};

template <class Ty, size_t Dims>
constexpr Array<Ty, Dims>::const_reverse_iterator
Array<Ty, Dims>::crend() const noexcept {
    return const_reverse_iterator(_end);
};
} // namespace llframe

// impletment Size
namespace llframe {

template <size_t Dims>
template <is_Integral... Integrals>
constexpr Size<Dims>::Size(Integrals... values) noexcept {
    this->_begin = allocator::allocate(Self::Dims);
    this->_end = this->_begin + Self::Dims;
    static_assert(sizeof...(values) == Dims);
    auto index = this->begin();
    --index;
    ((*(++index) = values), ...);
}

template <size_t Dims>
constexpr Size<Dims>::Size(Self &&other) noexcept :
    Base::Array(std::move(other)) {
    value_type zore{};
    allocator::fill(other.begin(), other.end(), zore);
}

template <size_t Dims>
constexpr Size<Dims> &Size<Dims>::operator=(Self &&other) noexcept {
    Base::Array(std::move(other));
    value_type zore{};
    allocator::fill(other.begin(), other.end(), zore);
    return *this;
}

template <size_t Dims>
consteval Size<Dims>::size_type Size<Dims>::dims() const noexcept {
    return this->Dims;
};

template <is_Integral... Integrals>
inline constexpr Size<sizeof...(Integrals)>
make_size(Integrals... values) noexcept {
    return Size<sizeof...(Integrals)>(values...);
};

template <size_t Dims>
inline constexpr Size<Dims> make_size(const Size<Dims> &size) noexcept {
    return Size<Dims>(size);
}
template <is_Size Size>
std::ostream &operator<<(std::ostream &os, const Size &size) {
    auto it = size.cbegin();
    const auto end = size.cend();
    std::puts("size:[");
    int i{};
    for (; i < Size::Dims - 1; i++) { os << size.at(i) << ","; }
    if (i < Size::Dims) os << size.at(i);
    std::putchar("]");
    return os;
};

template <is_Size Size>
std::ostream &operator<<(std::ostream &os, const Size &&size) {
    return (os << size);
};
} // namespace llframe
#endif //__LLFRAME_SIZE_HPP__