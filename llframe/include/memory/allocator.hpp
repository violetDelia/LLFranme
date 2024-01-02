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
#include <type_traits>
#include "core/exception_helper.hpp"
#ifdef __LLFRAME_USE_MODULE__
import llframe.memory.device;
import llframe.core.base_type;
#else
#include "memory/device.hpp"
#include "core/base_type.hpp"
#endif // __LLFRAME_USE_MODULE__
#include <memory>
#include <execution>
// define _Allocator_Base
namespace llframe {
/**
 * @brief 分配器,确保能够编译时分配内存,内存池后面再说
 *
 *
 * @tparam Ty 分配对象的类型
 * @tparam Device 设备类型
 */
template <class Ty>
class _Allocator_Base {
private:
    using Self = _Allocator_Base<Ty>;

public:
    using value_type = Ty;
    using pointer = Ty  *;
    using const_pointer = const Ty *;
    using reference = Ty  &;
    using const_reference = const Ty  &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    constexpr _Allocator_Base() noexcept = delete;

    /**
     * @brief 分配内存
     * @param n 数量
     * @return 内存头指针
     */
    [[nodiscard]] static constexpr pointer allocate(size_type n);

    /**
     * @brief 解内存
     *
     * @param p 内存指针
     * @param n 数量
     * @return
     */
    constexpr static inline void deallocate(value_type *p, size_type n);

protected:
    /**
     * @brief 获取的内存长度
     * @tparam _Ty_Size 类型
     * @param n 数量
     * @return 长度  字节数
     */
    template <size_type _Ty_Size>
    static constexpr size_type _get_size(const size_type n);
};
} // namespace llframe
// impletment _Allocator_Base
namespace llframe {

template <class Ty>
constexpr _Allocator_Base<Ty>::pointer
_Allocator_Base<Ty>::allocate(size_type n) {
    size_type allocate_size{};
    __LLFRAME_TRY_CATCH_BEGIN__
    allocate_size = Self::_get_size<sizeof(Ty)>(n);
    __LLFRAME_TRY_CATCH_END__
    return allocate_size == 0 ?
               nullptr :
               static_cast<Ty *>(::operator new(allocate_size));
    ;
};

template <class Ty>
constexpr void _Allocator_Base<Ty>::deallocate(Ty *p, size_type n) {
    ::operator delete(p, n);
};

template <class Ty>
template <_Allocator_Base<Ty>::size_type _Ty_Size>
constexpr _Allocator_Base<Ty>::size_type
_Allocator_Base<Ty>::_get_size(const size_type n) {
    constexpr bool _overflow_posibility = _Ty_Size > 1;
    if constexpr (_overflow_posibility) {
        constexpr size_t _max_n = std::numeric_limits<size_t>::max() / _Ty_Size;
        if (_max_n < n) {
            __LLFRAME_THROW_EXCEPTION_INFO__(Bad_Alloc, "allocate overflow!")
        }
    }
    return n * _Ty_Size;
};

}; // namespace llframe
// define Allocator
namespace llframe {
template <class Ty, device::is_Device Device = HOST>
class Allocator : public _Allocator_Base<Ty> {
private:
    using Base = _Allocator_Base<Ty>;

public:
    using value_type = Base::value_type;
    using pointer = Base::pointer;
    using const_pointer = Base::const_pointer;
    using reference = Base::reference;
    using const_reference = Base::const_reference;
    using device_type = Device;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;
};

}; // namespace llframe
// define Allocator<Ty, HOST>
namespace llframe {
template <class Ty>
class Allocator<Ty, HOST> : public _Allocator_Base<Ty> {
private:
    using Base = _Allocator_Base<Ty>;

public:
    using value_type = Base::value_type;
    using pointer = Base::pointer;
    using const_pointer = Base::const_pointer;
    using reference = Base::reference;
    using const_reference = Base::const_reference;
    using device_type = HOST;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;

public:
    template <std::forward_iterator It>
    static void defaut_construct(It first, It last);

    template <std::forward_iterator It, class ExecutionPolicy>
    static void defaut_construct(ExecutionPolicy &&policy, It first, It last);

    template <std::forward_iterator It>
    static void defaut_construct(It first, size_type n);

    template <std::forward_iterator It, class ExecutionPolicy>
    static void defaut_construct(ExecutionPolicy &&policy, It first,
                                 size_type n);

    template <std::forward_iterator It>
    static void construct(It first, It last);

    template <std::forward_iterator It, class ExecutionPolicy>
    static void construct(ExecutionPolicy &&policy, It first, It last);

    template <std::forward_iterator It>
    static void construct(It first, size_t n);

    template <std::forward_iterator It, class ExecutionPolicy>
    static void construct(ExecutionPolicy &&policy, It first, size_type n);

    template <std::forward_iterator It, std::forward_iterator Target_It>
    static void move(It first, It last, Target_It target_first);

    template <std::forward_iterator It, std::forward_iterator Target_It,
              class ExecutionPolicy>
    static void move(ExecutionPolicy &&policy, It first, It last,
                     Target_It target_first);

    template <std::forward_iterator It, std::forward_iterator Target_It>
    static void move(It first, size_type n, Target_It target_first);

    template <std::forward_iterator It, std::forward_iterator Target_It,
              class ExecutionPolicy>
    static void move(ExecutionPolicy &&policy, It first, size_type n,
                     Target_It target_first);

    template <std::forward_iterator It>
    static void fill(It first, It last, const_reference value);

    template <class ExecutionPolicy, std::forward_iterator It>
    static void fill(ExecutionPolicy &&policy, It first, It last,
                     const_reference value);

    template <std::forward_iterator It>
    static void fill(It first, size_type n, const_reference value);

    template <class ExecutionPolicy, std::forward_iterator It>
    static void fill(ExecutionPolicy &&policy, It first, size_type n,
                     const_reference value);

    template <std::forward_iterator It, std::forward_iterator Target_It>
    static void copy(It first, It last, Target_It target_first);

    template <std::forward_iterator It, std::forward_iterator Target_It,
              class ExecutionPolicy>
    static void copy(ExecutionPolicy &&policy, It first, It last,
                     Target_It target_first);

    template <std::forward_iterator It, std::forward_iterator Target_It>
    static void copy(It first, size_type n, Target_It target_first);

    template <std::forward_iterator It, std::forward_iterator Target_It,
              class ExecutionPolicy>
    static void copy(ExecutionPolicy &&policy, It first, size_type n,
                     Target_It target_first);

    template <std::forward_iterator It>
    void static destroy(It first, It last);

    template <class ExecutionPolicy, std::forward_iterator It>
    void static destroy(ExecutionPolicy &&policy, It first, It last);

    template <std::forward_iterator It>
    void static destroy(It first, size_type n);

    template <class ExecutionPolicy, std::forward_iterator It>
    static void destroy(ExecutionPolicy &&policy, It first, size_type last);

    static void destroy_at(pointer p);

    template <class... Args>
    static pointer construct_at(pointer p, Args &&...args);
};

}; // namespace llframe

// impletment Allocator<Ty,HOST>
namespace llframe {
template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::defaut_construct(It first, It last) {
    std::uninitialized_default_construct(first, last);
};

template <class Ty>
template <std::forward_iterator It, class ExecutionPolicy>
void Allocator<Ty, HOST>::defaut_construct(ExecutionPolicy &&policy, It first,
                                           It last) {
    std::uninitialized_default_construct(
        std::forward<ExecutionPolicy &&>(policy), first, last);
};

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::defaut_construct(It first, size_type n) {
    std::uninitialized_default_construct_n(first, n);
};

template <class Ty>
template <std::forward_iterator It, class ExecutionPolicy>
void Allocator<Ty, HOST>::defaut_construct(ExecutionPolicy &&policy, It first,
                                           size_type n) {
    std::uninitialized_default_construct_n(
        std::forward<ExecutionPolicy &&>(policy), first, n);
};

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::construct(It first, It last) {
    std::uninitialized_value_construct(first, last);
};

template <class Ty>
template <std::forward_iterator It, class ExecutionPolicy>
void Allocator<Ty, HOST>::construct(ExecutionPolicy &&policy, It first,
                                    It last) {
    std::uninitialized_value_construct(std::forward<ExecutionPolicy &&>(policy),
                                       first, last);
};

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::construct(It first, size_type n) {
    std::uninitialized_value_construct_n(first, n);
};

template <class Ty>
template <std::forward_iterator It, class ExecutionPolicy>
void Allocator<Ty, HOST>::construct(ExecutionPolicy &&policy, It first,
                                    size_type n) {
    std::uninitialized_value_construct_n(
        std::forward<ExecutionPolicy &&>(policy), first, n);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It>
void Allocator<Ty, HOST>::move(It first, It last, Target_It target_first) {
    std::uninitialized_move(first, last, target_first);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It,
          class ExecutionPolicy>
void Allocator<Ty, HOST>::move(ExecutionPolicy &&policy, It first, It last,
                               Target_It target_first) {
    std::uninitialized_move(std::forward<ExecutionPolicy &&>(policy), first,
                            last, target_first);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It>
void Allocator<Ty, HOST>::move(It first, size_type n, Target_It target_first) {
    std::uninitialized_move_n(first, n, target_first);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It,
          class ExecutionPolicy>
void Allocator<Ty, HOST>::move(ExecutionPolicy &&policy, It first, size_type n,
                               Target_It target_first) {
    std::uninitialized_move_n(std::forward<ExecutionPolicy &&>(policy), first,
                              n, target_first);
};

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::fill(It first, It last, const_reference value) {
    std::uninitialized_fill(first, last, value);
}

template <class Ty>
template <class ExecutionPolicy, std::forward_iterator It>
void Allocator<Ty, HOST>::fill(ExecutionPolicy &&policy, It first, It last,
                               const_reference value) {
    std::uninitialized_fill(std::forward<ExecutionPolicy &&>(policy), first,
                            last, value);
}

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::fill(It first, size_type n, const_reference value) {
    std::uninitialized_fill_n(first, n, value);
}

template <class Ty>
template <class ExecutionPolicy, std::forward_iterator It>
void Allocator<Ty, HOST>::fill(ExecutionPolicy &&policy, It first, size_type n,
                               const_reference value) {
    std::uninitialized_fill_n(std::forward<ExecutionPolicy &&>(policy), first,
                              n, value);
}

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It>
void Allocator<Ty, HOST>::copy(It first, It last, Target_It target_first) {
    std::uninitialized_copy(first, last, target_first);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It,
          class ExecutionPolicy>
void Allocator<Ty, HOST>::copy(ExecutionPolicy &&policy, It first, It last,
                               Target_It target_first) {
    std::uninitialized_copy(std::forward<ExecutionPolicy &&>(policy), first,
                            last, target_first);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It>
void Allocator<Ty, HOST>::copy(It first, size_type n, Target_It target_first) {
    std::uninitialized_copy_n(first, n, target_first);
};

template <class Ty>
template <std::forward_iterator It, std::forward_iterator Target_It,
          class ExecutionPolicy>
void Allocator<Ty, HOST>::copy(ExecutionPolicy &&policy, It first, size_type n,
                               Target_It target_first) {
    std::uninitialized_copy_n(std::forward<ExecutionPolicy &&>(policy), first,
                              n, target_first);
};

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::destroy(It first, It last) {
    std::destroy(first, last);
}

template <class Ty>
template <class ExecutionPolicy, std::forward_iterator It>
void Allocator<Ty, HOST>::destroy(ExecutionPolicy &&policy, It first, It last) {
    std::destroy(std::forward<ExecutionPolicy &&>(policy), first, last);
}

template <class Ty>
template <std::forward_iterator It>
void Allocator<Ty, HOST>::destroy(It first, size_type n) {
    std::destroy_n(first, n);
}

template <class Ty>
template <class ExecutionPolicy, std::forward_iterator It>
void Allocator<Ty, HOST>::destroy(ExecutionPolicy &&policy, It first,
                                  size_type n) {
    std::destroy_n(std::forward<ExecutionPolicy &&>(policy), first, n);
}

template <class Ty>
void Allocator<Ty, HOST>::destroy_at(pointer p) {
    std::destroy_at(p);
}

template <class Ty>
template <class... Args>
Allocator<Ty, HOST>::pointer Allocator<Ty, HOST>::construct_at(pointer p,
                                                               Args &&...args) {
    return std::construct_at(p, std::forward<Args>(args)...);
}
}; // namespace llframe
// namespace llframe
// // Allocator<Ty, CPU>
// namespace llframe {
// template <class Ty>
// class Allocator<Ty, CPU> : public Allocator<Ty, HOST> {
// private:
//     using Base = Allocator<Ty, HOST>;

// public:
//     using value_type = Base::value_type;
//     using pointer = Base::pointer;
//     using const_pointer = Base::const_pointer;
//     using reference = Base::reference;
//     using device_type = CPU;
//     using size_type = Base::size_type;
//     using difference_type = Base::difference_type;

// public:
//     [[nodiscard]] static constexpr pointer allocate(size_type n);
//     constexpr static void deallocate(value_type *p, size_type n);
// };

// } // namespace llframe
// // Allocator<Ty, GPU>
// namespace llframe {
// template <class Ty>
// class Allocator<Ty, GPU> : public Allocator<Ty, HOST> {
// private:
//     using Base = Allocator<Ty, HOST>;

// public:
//     using value_type = Base::value_type;
//     using pointer = Base::pointer;
//     using const_pointer = Base::const_pointer;
//     using reference = Base::reference;
//     using device_type = GPU;
//     using size_type = Base::size_type;
//     using difference_type = Base::difference_type;

// public:
//     [[nodiscard]] static constexpr pointer allocate(size_type n);
//     constexpr static void deallocate(value_type *p, size_type n);
// };

// } // namespace llframe
#endif //__LLFRAME_CONFIG_HPP__
