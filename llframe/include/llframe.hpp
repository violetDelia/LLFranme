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
 * @file llframe.hpp
 * @brief
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @see If you have any questions about the code or if you think there is a better way to implement
 * it,please contact me by email 1733535832@qq.com.
 * @copyright Apache 2.0
 */
#ifndef __LLFRAME_HPP__
#define __LLFRAME_HPP__
#include "config.h"
#ifdef __LLFRAME_USE_MODULE__
import llframe.core;
import llframe.memory;
#else
#include "memory/memory.hpp"
#include "core/core.hpp"
#include "core/exception_helper.hpp"
#endif // __LLFRAME_USE_MODULE__
namespace llframe
{
    
}// llframe
#endif //__LLFRAME_HPP__