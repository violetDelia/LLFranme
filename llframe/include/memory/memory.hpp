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
 * @file memory.hpp
 * @brief 内存相关的组件
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */
#ifndef __LLFRAME_MEMORY_HPP__
#define __LLFRAME_MEMORY_HPP__
#ifdef __LLFRAME_USE_MODULE__
import llframe.memory.device;
import llframe.memory.allocator;
#else
#include "memory/allocator.hpp"
#endif // __LLFRAME_USE_MODULE__
namespace llframe {

} // namespace llframe
#endif //__LLFRAME_MEMORY_HPP__
