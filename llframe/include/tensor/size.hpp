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
 * @see If you have any questions about the code or if you think there is a better way to implement
 * it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */
#ifndef __LLFRAME_SIZE_HPP__
#define __LLFRAME_SIZE_HPP__
#include <tuple>
#include <optional>
#include <type_traits>
#include "core/exception_helper.hpp"
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.conceptions;
#else
#include "core/conceptions.hpp"
#endif // __LLFRAME_USE_MODULE__
// define conceptions

namespace llframe
{
    template <is_Integral... Integrals>
    class Size;
    template <class Ty>
    concept is_Size = is_instance<Ty, Size>;
} // llframe

// define make_size
namespace llframe
{
    /**
     * @brief 构造size
     *
     * @tparam Integrals 整数
     * @param value 尺寸
     * @return Size<is_Integral... Integrals>
     */
    template <is_Integral... Integrals>
    inline consteval auto make_size(Integrals... value);
} // llframe
// define Size
namespace llframe
{

    /**
     * @brief 尺寸
     *
     * @tparam Ty 整数
     */
    template <is_Integral... Integrals>
    class Size
    {
        friend consteval auto llframe::make_size(Integrals... value);
        template <is_Integral... Other_Integrals>
        friend class Size;
        template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
        friend class _Size_Comparator;

    public:
        using size_type = size_t;

    protected:
        using tuple = std::tuple<Integrals...>;
        tuple data;

    public:
        constexpr Size(const Size &other) noexcept = default;
        constexpr Size(Size &&other) noexcept = delete;
        constexpr Size &operator=(const Size &other) noexcept = default;
        constexpr Size &operator=(Size &&other) noexcept = delete;

        template <is_Integral... Other_Integrals>
        constexpr bool operator==(const Size<Other_Integrals...> &other) const noexcept;

        template <is_Integral... Other_Integrals>
        constexpr bool operator!=(const Size<Other_Integrals...> &other) const noexcept;

        /**
         * @brief 维度个数
         *
         *
         * @return size_type
         */
        constexpr inline size_type dims() const noexcept;

        template <is_Integral Index>
        constexpr size_type operator[](Index index) const;

        /**
         * @brief 索引处的维度长度
         *
         * @tparam Index 整数
         * @param index 索引
         * @return  size_type
         */
        template <is_Integral Index>
        constexpr size_type at(Index index) const;

    protected:
        template <is_Integral Index>
        constexpr std::optional<size_t> at_(Index index) const noexcept;
        constexpr Size(Integrals... values) noexcept;
    };

} // llframe
// define _Size_Comparator
namespace llframe
{
    // 两个Size比较
    template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
    class _Size_Comparator
    {
        template <is_Integral... Integrals>
        friend class Size;
        template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
        friend class _Size_Comparator;

    private:
        static constexpr bool equle(const _Left_Size &_left_size, const _Right_Size &_right_size);
    };

    template <is_Size _Left_Size, is_Size _Right_Size>
    class _Size_Comparator<_Left_Size, _Right_Size, -1>
    {
        template <is_Integral... Integrals>
        friend class Size;
        template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
        friend class _Size_Comparator;

    private:
        static constexpr bool equle(const _Left_Size &_left_size, const _Right_Size &_right_size);
    };
} // llframe
// define others
namespace llframe
{

}
// implement make_size
namespace llframe
{
    template <is_Integral... Integrals>
    inline consteval auto make_size(Integrals... value)
    {
        return Size<Integrals...>(value...);
    };
} // llframe
// implement Size
namespace llframe
{

    template <is_Integral... Integrals>
    constexpr Size<Integrals...>::Size(Integrals... values) noexcept : data{values...} {};

    template <is_Integral... Integrals>
    constexpr inline Size<Integrals...>::size_type
    Size<Integrals...>::dims() const noexcept
    {
        return std::tuple_size_v<decltype(data)>;
    };

    template <is_Integral... Integrals>
    template <is_Integral Index>
    constexpr std::optional<size_t>
    Size<Integrals...>::at_(Index index) const noexcept
    {
        auto find_index_to_ass = [&]<size_t I>(std::in_place_index_t<I>, size_t index, size_t &res)
        {
            if (I == index)
            {
                res = std::get<I>(data);
                return true;
            }
            return false;
        };
        return [&]<size_t... Tuple_Len>(std::index_sequence<Tuple_Len...> is) -> std::optional<size_t>
        {
            size_type res{};
            if ((find_index_to_ass(std::in_place_index<Tuple_Len>, index, res) || ...))
            {
                return res;
            }
            return std::nullopt;
        }(std::index_sequence_for<Integrals...>{});
    }

    template <is_Integral... Integrals>
    template <is_Integral Index>
    constexpr Size<Integrals...>::size_type
    Size<Integrals...>::at(Index index) const
    {
        if (static_cast<size_type>(index) > dims())
            __LLFRAME_THROW_EXCEPTION__(Out_Range);
        std::optional<size_t> dim_len = at_(index);
        if (!dim_len.has_value())
            __LLFRAME_THROW_EXCEPTION__(Exception)
        return at_(index).value();
    }

    template <is_Integral... Integrals>
    template <is_Integral Index>
    constexpr Size<Integrals...>::size_type
    Size<Integrals...>::operator[](Index index) const
    {
        return at(index);
    }

    template <is_Integral... Integrals>
    template <is_Integral... Other_Integrals>
    constexpr bool
    Size<Integrals...>::operator==(const Size<Other_Integrals...> &other) const noexcept
    {
        const auto this_dims = dims();
        const auto other_dims = other.dims();
        if (this_dims != other_dims)
            return false;
        if (this_dims == 0)
            return true;
        return _Size_Comparator<decltype(*this), decltype(other), sizeof...(Integrals) - 1>::equle(*this, other);
    }

    template <is_Integral... Integrals>
    template <is_Integral... Other_Integrals>
    constexpr bool
    Size<Integrals...>::operator!=(const Size<Other_Integrals...> &other) const noexcept
    {
        return !this->operator==(other);
    }
} // llframe
// implement _Size_Comparator
namespace llframe
{
    template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
    constexpr bool llframe::_Size_Comparator<_Left_Size, _Right_Size, _Index>::equle(const _Left_Size &_left_size, const _Right_Size &_right_size)
    {
        if (_left_size.at(_Index) != _right_size.at(_Index))
            return false;
        return _Size_Comparator<_Left_Size, _Right_Size, _Index - 1>::equle(_left_size, _right_size);
    }

    template <is_Size _Left_Size, is_Size _Right_Size>
    constexpr bool llframe::_Size_Comparator<_Left_Size, _Right_Size, -1>::equle(const _Left_Size &_left_size, const _Right_Size &_right_size)
    {
        // if (_left_size[0] != _right_size[0])
        //     return false;
        return true;
    }
} // llframe

#endif //__LLFRAME_SIZE_HPP__