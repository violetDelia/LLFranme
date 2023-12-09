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
 * @file allocator.hpp
 * @brief 基础内存分配器
 * @details
 * @author 时光丶人爱
 * @date 2023-12-8
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_ALLOCATOR_HPP__
#define __LLFRAME_ALLOCATOR_HPP__
#include <memory>

namespace llframe
{
    template <typename Ty>
    // 分配器 保证编译器分配内存
    class Allocator : private std::allocator<Ty>
    {
    private:
        using father = std::allocator<Ty>;

    public:
        using value_type = father::value_type;
        using size_type = father::size_type;
        using difference_type = father::difference_type;
        using propagate_on_container_move_assignment = father::propagate_on_container_move_assignment;
        using is_always_equal = father::is_always_equal;
        using father::allocate;
        using father::deallocate;
    };
} // llframe

#endif //__LLFRAME_CONFIG_HPP__
