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
 * @file exception.ixx
 * @brief 异常
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */

module;
#include "core/exception.hpp"
export module llframe.core.exception;
export namespace llframe {
using llframe::Exception;
using llframe::Un_Implement;
using llframe::Bad_Alloc;
using llframe::Out_Range;
using llframe::Null_Pointer;
} // namespace llframe