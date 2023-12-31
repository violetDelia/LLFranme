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
 * @file test_config.h
 * @brief 测试宏
 * @details 根据CMakeLists.txt选项生成
 * @author 时光丶人爱
 * @date 2023-12-7
 * @copyright Apache 2.0
 */

#ifndef __LLFRAME_TEST_CONFIG_HPP__
#define __LLFRAME_TEST_CONFIG_HPP__

#define TEST_LLFRAME
#define TEST_CORE
#ifdef TEST_CORE
#define TEST_BASE_TYPE
#define TEST_ITERATOR
#endif // TEST_CORE
#define TEST_MEMORY
#ifdef TEST_MEMORY
/* #undef TEST_ALLOCATOR */
#endif // TEST_MEMORY
#define TEST_TENSOR
#ifdef TEST_TENSOR
#define TEST_SIZE
#endif // TEST_TENSOR

#endif //__LLFRAME_TEST_CONFIG_HPP__
