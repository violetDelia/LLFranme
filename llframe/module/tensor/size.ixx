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
 * @file size.ixx
 * @brief 形状
 * @details
 * @author 时光丶人爱
 * @date 2023-12-9
 * @see If you have any questions about the code or if you think there is a
 * better way to implement it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */
module;
#include "tensor/size.hpp"
export module llframe.tensor.size;
export namespace llframe {
using llframe::Array;
using llframe::Size;
using llframe::make_size;
using llframe::is_Size;
using llframe::operator<<;
using llframe::operator==;
using llframe::operator!=;

// template <is_Size Size>
// std::ostream &operator<<(std::ostream &os, const Size &size);

// template <is_Size Size>
// std::ostream &operator<<(std::ostream &os, const Size &&size);
} // namespace llframe