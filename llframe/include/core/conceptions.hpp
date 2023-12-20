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
namespace llframe
{
    template <class Ty>
    concept is_Integral = std::is_integral_v<Ty>;

    template <class _Ty, template <class...> class _Ty_Base>
    struct _Is_Instance : public std::false_type
    {
    };

    template <template <class...> class _Ty_Base, class... _Args>
    struct _Is_Instance<_Ty_Base<_Args...>, _Ty_Base> : public std::true_type
    {
    };

    template <class Ty, template <class...> class Ty_Base>
    constexpr inline bool is_instance = _Is_Instance<std::remove_cv_t<std::remove_reference_t<Ty>>, Ty_Base>::value;
} // llframe

#endif //__LLFRAME_CONCEPTIONS_HPP__