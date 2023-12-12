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
#ifdef __LLFRAME_USE_MODULE__
import llframe.core.base_type;
#else
#include "core/base_type.hpp"
#endif // __LLFRAME_USE_MODULE__
namespace llframe
{

    namespace device
    {
        template <size_t Id = 0>
        struct Device
        {
            /**
             * @brief 获取设备的id
             * 
             *
             * @return Id
             */
            consteval inline size_t get_id() noexcept
            {
                return Id;
            }
        };

        template <size_t Id>
        struct Host : Device<Id>
        {
        };

        template <size_t Id>
        struct GPU : Device<Id>
        {
        };

    }
} // llframe
#endif //__LLFRAME_MEMORY_HPP__