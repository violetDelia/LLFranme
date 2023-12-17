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
    inline consteval auto make_size(Integrals... value)
    {
        return Size<Integrals...>(value...);
    };

    /**
     * @brief 尺寸
     * 
     * @tparam Ty 整数
     */
    template <is_Integral... Integrals>
    class Size
    {
    public:
        using size_type = size_t;

    protected:
        using tuple = std::tuple<Integrals...>;
        tuple data;
        constexpr Size(Integrals... values) noexcept;
        friend consteval auto llframe::make_size(Integrals... value);

    public:
        constexpr Size(const Size &other) noexcept = default;
        constexpr Size(Size &&other) noexcept = delete;
        constexpr Size &operator=(const Size &other) noexcept = default;
        constexpr Size &operator=(Size &&other) noexcept = delete;

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
    };

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

} // llframe
#endif //__LLFRAME_SIZE_HPP__