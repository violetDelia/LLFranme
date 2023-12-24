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
import llframe.core.helper;
#else
#include "core/helper.hpp"
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
    inline constexpr auto make_size(Integrals... value);
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

    protected:
        using tuple = std::tuple<Integrals...>;
        tuple data;

    public:
        using size_type = size_t;
        using optional_size_type = std::optional<size_type>;
        static constexpr auto n_dims = std::tuple_size_v<tuple>;

    public:
        constexpr Size(Integrals... values) noexcept;
        constexpr Size(const Size &other) noexcept = default;
        constexpr Size(Size &&other) noexcept = default;
        constexpr Size &operator=(const Size &other) noexcept = default;
        constexpr Size &operator=(Size &&other) noexcept = default;

        template <is_Integral... Other_Integrals>
        [[nodiscard]] constexpr bool
        operator==(const Size<Other_Integrals...> &other) const noexcept;

        template <is_Integral... Other_Integrals>
        [[nodiscard]] constexpr bool
        operator!=(const Size<Other_Integrals...> &other) const noexcept;

        /**
         * @brief 维度个数
         *
         *
         * @return size_type
         */
        [[nodiscard]] consteval size_type dims() const noexcept;

        template <is_Integral Index_Ty>
        [[nodiscard]] constexpr size_type operator[](Index_Ty index) const;

        /**
         * @brief 索引处的维度长度  动态的get
         *
         * @tparam Index 整数
         * @param index 索引
         * @return  size_type
         */
        template <is_Integral Index_Ty>
        [[nodiscard]] constexpr size_type at(Index_Ty index) const;

        /**
         * @brief 获取Index处的长度
         *
         *
         * @tparam Index
         * @return size_type
         */
        template <size_type Index>
        [[nodiscard]] constexpr size_type get() const noexcept;

    protected:
        template <is_Integral Index_Ty>
        [[nodiscard]] constexpr optional_size_type
        at_(Index_Ty index) const noexcept;
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
        static constexpr inline bool
        equle(const _Left_Size &_left_size,
              const _Right_Size &_right_size) noexcept;
    };

    template <is_Size _Left_Size, is_Size _Right_Size>
    class _Size_Comparator<_Left_Size, _Right_Size, -1>
    {
        template <is_Integral... Integrals>
        friend class Size;
        template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
        friend class _Size_Comparator;

    private:
        static constexpr inline bool
        equle(const _Left_Size &_left_size,
              const _Right_Size &_right_size) noexcept;
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
    inline constexpr auto make_size(Integrals... value)
    {
        return Size<Integrals...>(value...);
    };
} // llframe
// implement Size
namespace llframe
{

    template <is_Integral... Integrals>
    constexpr Size<Integrals...>::Size(Integrals... values) noexcept
        : data{values...} {};

    template <is_Integral... Integrals>
    consteval inline Size<Integrals...>::size_type
    Size<Integrals...>::dims() const noexcept
    {
        using Self = Size<Integrals...>;
        return Self::n_dims;
    };

    template <is_Integral... Integrals>
    template <Size<Integrals...>::size_type Index>
    constexpr Size<Integrals...>::size_type
    Size<Integrals...>::get() const noexcept
    {
        static_assert(Index < n_dims);
        return std::get<Index>(data);
    };

    template <is_Integral... Integrals>
    template <is_Integral Index_Ty>
    constexpr Size<Integrals...>::optional_size_type
    Size<Integrals...>::at_(Index_Ty index) const noexcept
    {
        auto find_index_to_ass = [&]<size_type Index>(std::in_place_index_t<Index>, size_type index, size_type &res)
        {
            if (Index == index)
            {
                res = get<Index>();
                return true;
            }
            return false;
        };
        return [&]<size_type... Tuple_Len>(
                   std::index_sequence<Tuple_Len...> is) -> optional_size_type
        {
            size_type res{};
            if ((find_index_to_ass(std::in_place_index<Tuple_Len>,
                                   index,
                                   res) ||
                 ...))
            {
                return res;
            }
            return std::nullopt;
        }(std::index_sequence_for<Integrals...>{});
    }

    template <is_Integral... Integrals>
    template <is_Integral Index_Ty>
    constexpr Size<Integrals...>::size_type
    Size<Integrals...>::at(Index_Ty index) const
    {
        if (static_cast<size_type>(index) > n_dims)
            __LLFRAME_THROW_EXCEPTION__(Out_Range);
        optional_size_type dim_len = at_(index);
        if (!dim_len.has_value())
            __LLFRAME_THROW_EXCEPTION__(Exception)
        return dim_len.value();
    }

    template <is_Integral... Integrals>
    template <is_Integral Index_Ty>
    constexpr Size<Integrals...>::size_type
    Size<Integrals...>::operator[](Index_Ty index) const
    {
        return at(index);
    }

    template <is_Integral... Integrals>
    template <is_Integral... Other_Integrals>
    constexpr bool
    Size<Integrals...>::operator==(const Size<Other_Integrals...> &other)
        const noexcept
    {
        using Self = Size<Integrals...>;
        using Other_Size = Size<Other_Integrals...>;
        constexpr auto maximum_index = static_cast<int>(
            consteval_min(sizeof...(Integrals), sizeof...(Other_Integrals)) - 1);
        if constexpr (Self::n_dims != Other_Size::n_dims)
            return false;
        return _Size_Comparator<Self, Other_Size, maximum_index>::equle(*this, other);
    }

    template <is_Integral... Integrals>
    template <is_Integral... Other_Integrals>
    constexpr bool
    Size<Integrals...>::operator!=(const Size<Other_Integrals...> &other)
        const noexcept
    {
        return !this->operator==(other);
    }
} // llframe
// implement _Size_Comparator
namespace llframe
{

    template <is_Size _Left_Size, is_Size _Right_Size, int _Index>
    constexpr inline bool
    _Size_Comparator<_Left_Size, _Right_Size, _Index>::equle(
        const _Left_Size &_left_size,
        const _Right_Size &_right_size) noexcept
    {
        // if (_left_size.at(_Index) != _right_size.at(_Index))
        if (_left_size.get<_Index>() != _right_size.get<_Index>())
            return false;
        return _Size_Comparator<_Left_Size, _Right_Size, _Index - 1>::equle(
            _left_size, _right_size);
    }

    template <is_Size _Left_Size, is_Size _Right_Size>
    constexpr inline bool
    _Size_Comparator<_Left_Size, _Right_Size, -1>::equle(
        const _Left_Size &_left_size,
        const _Right_Size &_right_size) noexcept
    {
        return true;
    }
} // llframe

#endif //__LLFRAME_SIZE_HPP__