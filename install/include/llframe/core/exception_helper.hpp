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
 * @file exception_helper.hpp
 * @brief 一些宏
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_EXCEPTION_HELPER_HPP__
#define __LLFRAME_EXCEPTION_HELPER_HPP__
#include <source_location>
#include <stdio.h>
#include "core/exception.hpp"

#define __UN_IMPLEMENTED__                              \
    printf("Not implemented:\n");                       \
    printf("\tin file:\t %s\tline:%d\n",                \
           std::source_location::current().file_name(), \
           std::source_location::current().line());     \
    printf("\tfunction name :\t %s\n ",                 \
           std::source_location::current().function_name());

// 抛出异常
#define __LLFRAME_THROW_EXCEPTION_INFO__(Exception, message)     \
    throw Exception(message,                                     \
                    std::source_location::current().file_name(), \
                    std::source_location::current().line(),      \
                    std::source_location::current().function_name());
// 抛出异常
#define __LLFRAME_THROW_EXCEPTION__(Exception)       \
    throw Exception(                                 \
        std::source_location::current().file_name(), \
        std::source_location::current().line(),      \
        std::source_location::current().function_name());
// 记录函数传递信息
#define __LLFRAME_EXCEPTION_UPDATE__(exception)                         \
    exception.up_info(std::source_location::current().file_name(),      \
                      std::source_location::current().line(),           \
                      std::source_location::current().function_name()); \
    throw exception;

#define __LLFRAME_TRY_CATCH_BEGIN__ \
    try                             \
    {
#define __LLFRAME_TRY_CATCH_END__                                                  \
    }                                                                              \
    catch (llframe::Exception e)                                                   \
    {                                                                              \
        e.up_info(std::source_location::current().file_name(),                     \
                  std::source_location::current().line(),                          \
                  std::source_location::current().function_name());                \
        throw e;                                                                   \
    }                                                                              \
    catch (...)                                                                    \
    {                                                                              \
        throw llframe::Exception(std::source_location::current().file_name(),      \
                                 std::source_location::current().line(),           \
                                 std::source_location::current().function_name()); \
    }

#endif //__LLFRAME_EXCEPTION_HELPER_HPP__