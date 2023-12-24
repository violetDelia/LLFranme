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
 * @file base_type.ixx
 * @brief 基础类型定义
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */
module;
#include "core/base_type.hpp"
export module llframe.core.base_type;
export namespace llframe
{
    using llframe:: float32_t;
    using llframe::float64_t;
    using llframe::int16_t;
    using llframe::int32_t;
    using llframe::int64_t;
    using llframe::int8_t;
    using llframe::ptrdiff_t;
    using llframe::size_t;
    using llframe::uint16_t;
    using llframe::uint32_t;
    using llframe::uint64_t;
    using llframe::uint8_t;
}