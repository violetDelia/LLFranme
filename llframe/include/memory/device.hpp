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
namespace llframe
{

    inline namespace device
    {
        /**
         * @brief 记录设备信息
         *
         */
        class Device
        {
        private:
            size_t id{};

        public:
            /**
             * @brief 
             * @param id 
             */
            constexpr Device(size_t id);

            constexpr Device() = default;

            constexpr Device(const Device &other) = default;

            constexpr Device(Device &&other) = default;
        };

        class HOST : public Device
        {
        };

        class CPU : public Device
        {
        };

        class GPU : public Device
        {
        };

        template <typename Ty>
        concept is_Device = std::is_base_of_v<Device, Ty>;

    }
} // llframe
#endif //__LLFRAME_MEMORY_HPP__