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
 * @file exception.hpp
 * @brief 异常
 * @details
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_EXCEPTION_HPP__
#define __LLFRAME_EXCEPTION_HPP__
#include <source_location>
#include <string>
#include <stdio.h>

#define __UN_IMPLEMENTED__                              \
    printf("Not implemented:\n");                       \
    printf("\tin file:\t %s\tline:%d\n",                \
           std::source_location::current().file_name(), \
           std::source_location::current().line());     \
    printf("\tfunction name :\t %s\n ",                 \
           std::source_location::current().function_name());

namespace llframe
{

    /**
     * @brief 异常
     *
     */
    class Exception
    {
    public:
        constexpr Exception() = delete;

        constexpr Exception(const Exception &other) noexcept = default;

        constexpr Exception(Exception &&other) noexcept = default;

        /**
         * @brief 构造Exception
         *
         *
         * @param message 异常信息
         */
        Exception(const char *message) noexcept;

        /**
         * @brief 构造Exception
         *
         *
         * @param message 异常信息
         * @param file 源文件名
         * @param line 所在源文件行数
         * @param func_name 所在源文件的函数名
         */
        Exception(const char *message, const char *file, const size_t line, const char *func_name) noexcept;

        /**
         * @brief 记录异常的传递信息
         *
         *
         * @param file 文件名
         * @param line 行数
         * @param func_name 函数名
         * @return  异常信息
         */
        [[nodiscard]] virtual std::string what() const noexcept;

        /**
         * @brief 记录异常的传递信息
         *
         *
         * @param file 文件名
         * @param line 行数
         * @param func_name 函数名
         */
        void up_info(const char *file, const size_t line, const char *func_name) noexcept;

    protected:
        // 异常信息
        const std::string message{"unknown exception"};
        // 位置信息
        std::string locations{"\n"};
    };

} // llframe
// 抛出异常
#define __LLFRAME_THROW_EXCEPTION__(Exception, message)          \
    throw Exception(message,                                     \
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
#define __LLFRAME_TRY_CATCH_END__                                            \
    }                                                                        \
    catch (llframe::Exception e)                                             \
    {                                                                        \
        __LLFRAME_EXCEPTION_UPDATE__(e)                                      \
    }                                                                        \
    catch (...)                                                              \
    {                                                                        \
        __LLFRAME_THROW_EXCEPTION__(llframe::Exception, "unknown exception") \
    }

#endif //__LLFRAME_EXCEPTION_HPP__