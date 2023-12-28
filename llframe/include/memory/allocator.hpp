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
// _Allocator_Base
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
public:
    using value_type = Ty;
    using value_pointer = Ty *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;

public:
    /**
     * @brief 分配内存
     * @param n 数量
     * @return 内存头指针
     */
    [[nodiscard]] static constexpr value_pointer allocate(size_type n);

    /**
     * @brief 解内存
     *
     * @param p 内存指针
     * @param n 数量
     * @return
     */
    static constexpr void deallocate(value_type *p, size_type n) noexcept;

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

template <class Ty>
constexpr _Allocator_Base<Ty>::value_pointer
_Allocator_Base<Ty>::allocate(size_type n) {
    __LLFRAME_THROW_EXCEPTION__(Un_Implement);
};

template <class Ty>
constexpr void _Allocator_Base<Ty>::deallocate(Ty *p, size_type n) noexcept {
    __LLFRAME_THROW_EXCEPTION__(Un_Implement);
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
// Allocator
namespace llframe {
template <class Ty, device::is_Device Device = HOST>
class Allocator : public _Allocator_Base<Ty> {
private:
    using Base = _Allocator_Base<Ty>;

public:
    using value_type = Base::value_type;
    using value_pointer = Base::value_pointer;
    using device_type = Device;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;
    using propagate_on_container_move_assignment =
        Base::propagate_on_container_move_assignment;
};

}; // namespace llframe
// Allocator<Ty, HOST>
namespace llframe {
template <class Ty>
class Allocator<Ty, HOST> : public _Allocator_Base<Ty> {
private:
    using Base = _Allocator_Base<Ty>;

public:
    using value_type = Base::value_type;
    using value_pointer = Base::value_pointer;
    using device_type = HOST;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;
    using propagate_on_container_move_assignment =
        Base::propagate_on_container_move_assignment;

public:
    /**
     * @brief 分配内存 HOST特化
     *
     * @param n 数量
     * @return 头指针
     */
    [[nodiscard]] static constexpr value_pointer allocate(size_type n);

    /**
     * @brief 接分配内存 HOST特化
     *
     * @param n 数量
     * @param p 内存指针
     * @return
     */
    static inline constexpr void deallocate(value_pointer p, size_type n);
};

template <class Ty>
constexpr Allocator<Ty, HOST>::value_pointer
Allocator<Ty, HOST>::allocate(size_type n) {
    size_type allocate_size{};
    __LLFRAME_TRY_CATCH_BEGIN__
    allocate_size = Base::_get_size<sizeof(Ty)>(n);
    __LLFRAME_TRY_CATCH_END__
    return allocate_size == 0 ?
               nullptr :
               static_cast<Ty *>(::operator new(allocate_size));
}

template <class Ty>
inline constexpr void Allocator<Ty, HOST>::deallocate(value_pointer p,
                                                      size_type n) {
    ::operator delete(p, n);
}

}; // namespace llframe
// Allocator<Ty, CPU>
namespace llframe {
template <class Ty>
class Allocator<Ty, CPU> : public Allocator<Ty, HOST> {
private:
    using Base = Allocator<Ty, HOST>;

public:
    using value_type = Base::value_type;
    using value_pointer = Base::value_pointer;
    using device_type = CPU;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;
    using propagate_on_container_move_assignment =
        Base::propagate_on_container_move_assignment;
};

} // namespace llframe
// Allocator<Ty, GPU>
namespace llframe {
template <class Ty>
class Allocator<Ty, GPU> : public Allocator<Ty, HOST> {
private:
    using Base = Allocator<Ty, HOST>;

public:
    using value_type = Base::value_type;
    using value_pointer = Base::value_pointer;
    using device_type = GPU;
    using size_type = Base::size_type;
    using difference_type = Base::difference_type;
    using propagate_on_container_move_assignment =
        Base::propagate_on_container_move_assignment;
};

} // namespace llframe
#endif //__LLFRAME_CONFIG_HPP__
