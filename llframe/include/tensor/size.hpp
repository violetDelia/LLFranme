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
 * @details
 * @author 时光丶人爱
 * @date 2023-12-9
 * @see If you have any questions about the code or if you think there is a
 * better way to implement it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_SIZE_HPP__
#define __LLFRAME_SIZE_HPP__
#include <type_traits>
#include <algorithm>
#include <memory>
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

// define make_size
namespace llframe {
template <size_t Dims>
class Size;

/**
 * @brief 构造size
 *
 * @tparam Integrals 整数
 * @param value 尺寸
 * @return Size<is_Integral... Integrals>
 */
template <is_Integral... Integrals>
[[nodiscard]] inline constexpr auto make_size(Integrals... value) noexcept;

template <size_t Dims>
[[nodiscard]] inline constexpr auto make_size(const Size<Dims> &size) noexcept;

} // namespace llframe

// define Size
namespace llframe {
/**
 * @brief 尺寸
 * std::array不安全,move不能清理原有的内存,data()返回不定义;
 * 所以删掉move,隐藏构造, 访问index不能是const的
 * ,有必要重新写一个array
 * @tparam Ty 整数
 */
template <size_t Dims>
class Size {
public:
    using value_type = size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

private:
    using Self = Size<Dims>;

protected:
    using allocator = Allocator<value_type, HOST>;

public:
    using iterator = Random_Iterator<Self>;
    using const_iterator = Const_Random_Iterator<Self>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // protected:

    static const constinit size_t Dims = Dims;

protected:
    pointer _begin{};
    pointer _end{};

private:
    template <is_Integral... Integrals>
    friend constexpr auto make_size(Integrals... values) noexcept;
    template <size_t Dims>
    friend constexpr auto make_size(Size &size) noexcept;

public:
    constexpr Size() noexcept;
    constexpr Size(const Self &other) noexcept;
    constexpr Size(Self &&other) noexcept;
    constexpr Size &operator=(const Self &other) noexcept;
    constexpr Size &operator=(Self &&other) noexcept;
    constexpr virtual ~Size() noexcept;

    template <is_Integral... Integrals>
    constexpr Size(Integrals... values) noexcept;

public:
    constexpr iterator begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr iterator end() noexcept;
    constexpr const_iterator end() const noexcept;

    constexpr reverse_iterator rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;

    constexpr const_iterator cbegin() const noexcept;
    constexpr const_iterator cend() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

public:
    template <size_t Other_Dims>
    [[nodiscard]] constexpr bool
    operator==(const Size<Other_Dims> &other) const noexcept;

    template <size_t Other_Dims>
    [[nodiscard]] constexpr bool
    operator!=(const Size<Other_Dims> &other) const noexcept;

    /**
     * @brief 维度个数
     *
     *
     * @return size_type
     */
    [[nodiscard]] consteval size_t dims() const noexcept;

    [[nodiscard]] constexpr reference operator[](size_type index);

    /**
     * @brief 索引处的维度长度  动态的get
     *
     * @tparam Index 整数
     * @param index 索引
     * @return  size_type
     */
    [[nodiscard]] constexpr value_type at(size_type index) const;

private:
    /**
     * @brief 是否为空
     *
     *
     * @return
     */
    [[nodiscard]] constexpr inline bool _empty() const;
};

} // namespace llframe

// define other
namespace llframe {

}

// impletment make_size
namespace llframe {

template <is_Integral... Integrals>
inline constexpr auto make_size(Integrals... values) noexcept {
    return Size<sizeof...(Integrals)>(values...);
};

template <size_t Dims>
inline constexpr auto make_size(const Size<Dims> &size) noexcept {
    return Size<Dims>(size);
}
} // namespace llframe

// impletment Size
namespace llframe {
template <size_t Dims>
constexpr Size<Dims>::Size() noexcept : _begin{}, _end{} {};

template <size_t Dims>
constexpr Size<Dims>::Size(const Self &other) noexcept :
    _begin(allocator::allocate(Self::Dims)), _end(_begin + Self::Dims) {
    std::ranges::copy(other.begin(), other.end(), begin());
};

template <size_t Dims>
constexpr Size<Dims>::Size(Self &&other) noexcept :
    _begin(other._begin), _end(other._end) {
    other._begin = nullptr;
    other._end = nullptr;
};

template <size_t Dims>
constexpr Size<Dims>::Self &Size<Dims>::operator=(const Self &other) noexcept {
    if (this != std::addressof(other)) {
        if (_empty()) {
            _begin = allocator::allocate(Self::Dims);
            _end = _begin + Self::Dims;
        }
        std::ranges::copy(other.begin(), other.end(), begin());
    }
    return *this;
};

template <size_t Dims>
constexpr Size<Dims>::Self &Size<Dims>::operator=(Self &&other) noexcept {
    if (this != std::addressof(other)) {
        _begin(other._begin);
        _end(other._end);
        other._begin = nullptr;
        other._end = nullptr;
    }
    return *this;
};

template <size_t Dims>
template <is_Integral... Integrals>
constexpr Size<Dims>::Size(Integrals... values) noexcept :
    _begin(allocator::allocate(Self::Dims)), _end(_begin + Self::Dims) {
    static_assert(sizeof...(values) == Dims);
    auto index = begin();
    --index;
    ((*(++index) = values), ...);
};

template <size_t Dims>
constexpr Size<Dims>::~Size() noexcept {
    if (_empty()) return;
    allocator::deallocate(_begin, Dims + 1);
    _begin = nullptr;
    _end = nullptr;
};

template <size_t Dims>
constexpr bool Size<Dims>::_empty() const {
    return (_begin == nullptr) && (_end == nullptr);
};

template <size_t Dims>
consteval inline size_t Size<Dims>::dims() const noexcept {
    return Self::Dims;
};

template <size_t Dims>
constexpr Size<Dims>::value_type Size<Dims>::at(size_type index) const {
    if (static_cast<size_type>(index) >= Dims)
        __LLFRAME_THROW_EXCEPTION__(Out_Range);
    if (_empty()) return size_t(0);
    return *(begin() + index);
}

template <size_t Dims>
constexpr Size<Dims>::reference Size<Dims>::operator[](size_type index) {
    if (_empty()) __LLFRAME_THROW_EXCEPTION__(Null_Pointer);
    return begin()[index];
}

template <size_t Dims>
template <size_t Other_Dims>
constexpr bool
Size<Dims>::operator==(const Size<Other_Dims> &other) const noexcept {
    if constexpr (Dims != Other_Dims) return false;
    for (int i{}; i < Dims; i++) {
        if (at(i) != other.at(i)) return false;
    }
    return true;
}

template <size_t Dims>
template <size_t Other_Dims>
constexpr bool
Size<Dims>::operator!=(const Size<Other_Dims> &other) const noexcept {
    return !(*this == other);
}
} // namespace llframe

// impletment Size iterator
namespace llframe {
template <size_t Dims>
constexpr Size<Dims>::iterator Size<Dims>::begin() noexcept {
    return iterator(_begin);
};

template <size_t Dims>
constexpr Size<Dims>::const_iterator Size<Dims>::begin() const noexcept {
    return const_iterator(_begin);
};

template <size_t Dims>
constexpr Size<Dims>::iterator Size<Dims>::end() noexcept {
    return iterator(_end);
};

template <size_t Dims>
constexpr Size<Dims>::const_iterator Size<Dims>::end() const noexcept {
    return const_iterator(_end);
};

template <size_t Dims>
constexpr Size<Dims>::reverse_iterator Size<Dims>::rbegin() noexcept {
    return reverse_iterator(_begin);
};

template <size_t Dims>
constexpr Size<Dims>::const_reverse_iterator
Size<Dims>::rbegin() const noexcept {
    return const_reverse_iterator(_begin);
};

template <size_t Dims>
constexpr Size<Dims>::reverse_iterator Size<Dims>::rend() noexcept {
    return reverse_iterator(_end);
};

template <size_t Dims>
constexpr Size<Dims>::const_reverse_iterator Size<Dims>::rend() const noexcept {
    return const_reverse_iterator(_end);
};

template <size_t Dims>
constexpr Size<Dims>::const_iterator Size<Dims>::cbegin() const noexcept {
    return const_iterator(_begin);
};

template <size_t Dims>
constexpr Size<Dims>::const_iterator Size<Dims>::cend() const noexcept {
    return const_iterator(_end);
};

template <size_t Dims>
constexpr Size<Dims>::const_reverse_iterator
Size<Dims>::crbegin() const noexcept {
    return const_reverse_iterator(_begin);
};

template <size_t Dims>
constexpr Size<Dims>::const_reverse_iterator
Size<Dims>::crend() const noexcept {
    return const_reverse_iterator(_end);
};
} // namespace llframe

#endif //__LLFRAME_SIZE_HPP__