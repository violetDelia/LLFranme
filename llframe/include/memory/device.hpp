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
 * @file device.hpp
 * @brief 设备的定义
 * @details
 * @author 时光丶人爱
 * @date 2023-12-11
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_DEVICE_HPP__
#define __LLFRAME_DEVICE_HPP__
#include <type_traits>
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.base_type;
#else
#include "core/base_type.hpp"
#endif // __LLFRAME_USE_MODULE__
namespace llframe { inline namespace device {
/**
 * @brief 记录设备信息
 *
 */
class _Device {
private:
    size_t id{};

public:
    /**
     * @brief
     * @param id
     */
    constexpr _Device(size_t id);

    constexpr _Device() = default;

    constexpr _Device(const _Device &other) = default;

    constexpr _Device(_Device &&other) = default;

    _Device &operator=(const _Device &other) = default;

    _Device &operator=(_Device &other) = default;
};

class HOST : public _Device {};

class CPU : public _Device {};

class GPU : public _Device {};

// 是设备
template <class Ty>
concept is_Device = std::is_base_of_v<_Device, Ty>;

}}     // namespace llframe::device
#endif //__LLFRAME_MEMORY_HPP__