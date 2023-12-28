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
#include "core/exception_helper.hpp"
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.base_type;
import llframe.memory.allocator;
import llframe.core.helper;
import llframe.core.iterator;
#else
#include
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
[[nodiscard]] inline constexpr auto make_size(Size<Dims> &size) noexcept;

} // namespace llframe

// define Size
namespace llframe { /**
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
    using pointer = size_t *;
    using const_pointer = const size_t *;
    using reference = size_t &;
    using const_reference = const size_t &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

private:
    using Self = Size<Dims>;
    using allocator = Allocator<value_type, HOST>;

public:
    using iterator = Random_Iterator<Self>;
    using const_iterator = Const_Random_Iterator<Self>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // protected:
public:
    static const constinit size_t Dims = Dims;
    pointer data{};
    pointer data_end{};

public:
    constexpr Size() = default;
    constexpr Size(const Size &other) = default;
    constexpr Size(Size &&other) noexcept = default;
    constexpr Size &operator=(const Size &other) = default;
    constexpr Size &operator=(Size &&other) = default;
    constexpr virtual ~Size() = default;

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
    operator==(Size<Other_Dims> &other) const noexcept;

    template <size_t Other_Dims>
    [[nodiscard]] constexpr bool
    operator!=(Size<Other_Dims> &other) const noexcept;

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

protected:
    template <is_Integral... Integrals>
    constexpr Size(Integrals... values) noexcept;

private:
    template <is_Integral... Integrals>
    friend constexpr auto make_size(Integrals... values) noexcept;
    template <size_t Dims>
    friend constexpr auto make_size(Size &size) noexcept;
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
inline constexpr auto make_size(Size<Dims> &size) noexcept {
    return Size<Dims>(std::move(size));
}
} // namespace llframe

// impletment Size
namespace llframe {

template <size_t Dims>
template <is_Integral... Integrals>
constexpr Size<Dims>::Size(Integrals... values) noexcept :
    data(allocator::allocate(Self::Dims + 1)), data_end(data + Self::Dims) {
    auto index = begin();
    // end = data + Self::Dims;
    //  auto index = begin();

    // auto index = begin();
    //  static_cast(sizeof...(values) == Dims);
};

template <size_t Dims>
consteval inline size_t Size<Dims>::dims() const noexcept {
    return Self::Dims;
};

template <size_t Dims>
constexpr Size<Dims>::value_type Size<Dims>::at(size_type index) const {
    if (static_cast<size_type>(index) >= Dims)
        __LLFRAME_THROW_EXCEPTION__(Out_Range);
    if (static_cast<size_type>(data.size()) != Dims)
        __LLFRAME_THROW_EXCEPTION_INFO__(Exception, "size is null");
    return data[index];
}

template <size_t Dims>
constexpr Size<Dims>::reference Size<Dims>::operator[](size_type index) {
    if (static_cast<size_type>(index) >= Dims)
        __LLFRAME_THROW_EXCEPTION__(Out_Range);
    return data[index];
}

template <size_t Dims>
template <size_t Other_Dims>
constexpr bool Size<Dims>::operator==(Size<Other_Dims> &other) const noexcept {
    if constexpr (Dims != Other_Dims) return false;
    for (int i{}; i < Dims; i++) {
        if (at(i) != other.at(i)) return false;
    }
    return true;
}

template <size_t Dims>
template <size_t Other_Dims>
constexpr bool Size<Dims>::operator!=(Size<Other_Dims> &other) const noexcept {
    if constexpr (Dims != Other_Dims) return true;
    for (int i{}; i < Dims; i++) {
        if (at(i) != other.at(i)) return true;
    }
    return false;
}

} // namespace llframe

#endif //__LLFRAME_SIZE_HPP__