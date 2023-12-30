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
 * @file conceptions.hpp
 * @brief 基础概念
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */
#ifndef __LLFRAME_CONCEPTIONS_HPP__
#define __LLFRAME_CONCEPTIONS_HPP__
#include <type_traits>
namespace llframe {
// 是整形
template <class Ty>
concept is_Integral = std::is_integral_v<Ty>;

template <class TT, class UT>
consteval auto consteval_min(const TT &lfte_value,
                             const UT &right_value) noexcept {
    return (lfte_value < right_value) ? lfte_value : right_value;
}

template <class _Ty, template <class...> class _Ty_Base>
struct _Is_Instance : public std::false_type {};

template <template <class...> class _Ty_Base, class... _Args>
struct _Is_Instance<_Ty_Base<_Args...>, _Ty_Base> : public std::true_type {};

/**
 * @brief 是否是模板类的一个实例
 *
 * @tparam Ty 模板类实例
 * @tparam Ty_Base 模板基类
 */
template <class Ty, template <class...> class Ty_Base>
constexpr inline bool is_instance =
    _Is_Instance<std::remove_cv_t<std::remove_reference_t<Ty>>, Ty_Base>::value;

template <typename _Ty>
struct _add_const {
    using type = const _Ty;
};

template <typename _Ty>
struct _add_const<_Ty &> {
    using type = const std::remove_const_t<_Ty> &;
};

template <typename _Ty>
struct _add_const<_Ty *> {
    using type = const std::remove_const_t<_Ty> *;
};

/**
 * @brief 添加const关键字
 *
 * @tparam Ty
 */
template <typename Ty>
using add_const_t = typename _add_const<Ty>::type;
} // namespace llframe

#endif //__LLFRAME_CONCEPTIONS_HPP__