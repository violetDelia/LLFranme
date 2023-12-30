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

// Exception
namespace llframe {
/**
 * @brief 异常
 *
 */
class Exception {
public:
    constexpr Exception() = default;

    constexpr Exception(const Exception &other) noexcept = default;

    constexpr Exception(Exception &&other) noexcept = default;

    /**
     * @brief 构造Exception
     *
     *
     * @param message 异常信息
     */
    constexpr Exception(const char *message) noexcept;

    /**
     * @brief 构造Exception
     *
     *
     * @param message 异常信息
     * @param file 源文件名
     * @param line 所在源文件行数
     * @param func_name 所在源文件的函数名
     */
    constexpr Exception(const char *message, const char *file,
                        const size_t line, const char *func_name) noexcept;

    /**
     * @brief 构造Exception
     *
     *
     * @param file 源文件名
     * @param line 所在源文件行数
     * @param func_name 所在源文件的函数名
     */
    constexpr Exception(const char *file, const size_t line,
                        const char *func_name) noexcept;

    /**
     * @brief 记录异常的传递信息
     *
     *
     * @param file 文件名
     * @param line 行数
     * @param func_name 函数名
     * @return  异常信息
     */
    [[nodiscard]] constexpr virtual std::string what() const noexcept;

    /**
     * @brief 记录异常的传递信息
     *
     *
     * @param file 文件名
     * @param line 行数
     * @param func_name 函数名
     */
    constexpr void up_info(const char *file, const size_t line,
                           const char *func_name) noexcept;

    // protected:
public:
    // 异常信息
    const std::string message{"unknown exception!"};
    // 位置信息
    std::string locations{"\n"};
};

constexpr Exception::Exception(const char *message) noexcept :
    message(message){};

constexpr Exception::Exception(const char *message, const char *file,
                               const size_t line,
                               const char *func_name) noexcept :
    message(message) {
    this->up_info(file, line, func_name);
};

constexpr Exception::Exception(const char *file, const size_t line,
                               const char *func_name) noexcept {
    this->up_info(file, line, func_name);
};

constexpr std::string Exception::what() const noexcept {
    return this->message + this->locations;
};

constexpr void Exception::up_info(const char *file, const size_t line,
                                  const char *func_name) noexcept {
    this->locations.append("\t");
    this->locations.append(func_name);
    this->locations.append(": ");
    this->locations.append(file);
    this->locations.append("<");
    this->locations.append(std::to_string(line));
    this->locations.append(">\n");
};
} // namespace llframe
// Un_Implement
namespace llframe {
class Un_Implement : public Exception {
public:
    using Exception::Exception;

    constexpr std::string what() const noexcept override;

public:
    // 异常信息
    const std::string message{"not implement!"};
};

constexpr std::string Un_Implement::what() const noexcept {
    return this->message + this->locations;
};
} // namespace llframe
// Bad_Alloc
namespace llframe {
class Bad_Alloc : public Exception {
public:
    using Exception::Exception;

    constexpr std::string what() const noexcept override;

public:
    // 异常信息
    const std::string message{"bad allocate!"};
};

constexpr std::string Bad_Alloc::what() const noexcept {
    return this->message + this->locations;
};

} // namespace llframe
// Out_Range
namespace llframe {
class Out_Range : public Exception {
public:
    using Exception::Exception;

    constexpr std::string what() const noexcept override;

public:
    // 异常信息
    const std::string message{"out of range!"};
};
constexpr std::string Out_Range::what() const noexcept {
    return this->message + this->locations;
};

} // namespace llframe
// Null_Pointer
namespace llframe {
class Null_Pointer : public Exception {
public:
    using Exception::Exception;

    constexpr std::string what() const noexcept override;

public:
    // 异常信息
    const std::string message{"null pointer error!"};
};
constexpr std::string Null_Pointer::what() const noexcept {
    return this->message + this->locations;
}
} // namespace llframe
#endif //__LLFRAME_EXCEPTION_HPP__