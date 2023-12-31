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
 * @file tensor.hpp
 * @brief 张量
 * @details
 * @author 时光丶人爱
 * @date 2023-12-9
 * @see If you have any questions about the code or if you think there is a
 * better way to implement it,please contact me by email 1152488956@qq.com.
 * @copyright Apache 2.0
 */
#ifndef __LLFRAME_TENSOR_HPP__
#define __LLFRAME_TENSOR_HPP__
#include <algorithm>
#ifdef __LLFRAME_USE_MODULE__
import llframe.tensor.size;
import llframe.memory.device;
#else
#include "tensor/size.hpp"
#include "memory/device.hpp"
#endif // __LLFRAME_USE_MODULE__

// define layout
namespace llframe {

}

// define Tensor
namespace llframe {
template <size_t Dims, class Ty, device::is_Device Device>
class _Tensor_Base {
private:
    using Self = _Tensor_Base<Dims, Ty, Device>;

public:
    using value_type = Ty;
    using pointer = value_type *;
    using device_type = Device;
    using shape_type = Size<Dims>;
    using shape_iterator = Size<Dims>::iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

protected:
    using host_allocator = Allocator<value_type, device::HOST>;
    using allocator = Allocator<value_type, device_type>;

protected:
    pointer _host{};
    const shape_type _shape;

public:
    constexpr _Tensor_Base() noexcept;
    constexpr virtual ~_Tensor_Base() noexcept;
    constexpr _Tensor_Base(const shape_type &shape) noexcept;
    constexpr _Tensor_Base(shape_type &&shape) noexcept;

public:
    // protected:
    constexpr size_type capacity() const;
};

template <size_t Dims, class Ty = float32_t, device::is_Device Device = HOST>
class Tensor : public _Tensor_Base<Dims, Ty, Device> {
private:
    using Self = Tensor<Dims, Ty, Device>;
    using Base = _Tensor_Base<Dims, Ty, Device>;

public:
    using value_type = Ty;
    using pointer = value_type *;
    using device_type = Device;
    using shape_type = Size<Dims>;
    using shape_iterator = Size<Dims>::iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

protected:
    using host_allocator = Allocator<value_type, device::HOST>;
    using allocator = Allocator<value_type, device_type>;

protected:
    pointer _data{};

public:
    constexpr Tensor() noexcept;
    constexpr virtual ~Tensor() noexcept;
    constexpr Tensor(const shape_type &shape) noexcept;
    constexpr Tensor(shape_type &&shape) noexcept;
};

template <size_t Dims, class Ty>
class Tensor<Dims, Ty, HOST> : public _Tensor_Base<Dims, Ty, HOST> {
private:
    using Self = Tensor<Dims, Ty, HOST>;
    using Base = _Tensor_Base<Dims, Ty, HOST>;

public:
    using value_type = Ty;
    using pointer = value_type *;
    using device_type = HOST;
    using shape_type = Size<Dims>;
    using shape_iterator = Size<Dims>::iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

protected:
    using host_allocator = Allocator<value_type, device::HOST>;
    using allocator = Allocator<value_type, device_type>;

public:
    using Base::_Tensor_Base;
};

} // namespace llframe

// impletment  _Tensor_Base construct
namespace llframe {
template <size_t Dims, class Ty, is_Device Device>
constexpr _Tensor_Base<Dims, Ty, Device>::_Tensor_Base() noexcept :
    _shape(), _host{} {};

template <size_t Dims, class Ty, is_Device Device>
constexpr _Tensor_Base<Dims, Ty, Device>::~_Tensor_Base() noexcept {
    if (_host != nullptr) host_allocator::deallocate(_host, capacity());
    _shape.~Size();
};

template <size_t Dims, class Ty, is_Device Device>
constexpr _Tensor_Base<Dims, Ty, Device>::_Tensor_Base(
    const shape_type &shape) noexcept :
    _shape(shape) {
    _host = host_allocator::allocate(capacity());
};

template <size_t Dims, class Ty, is_Device Device>
constexpr _Tensor_Base<Dims, Ty, Device>::_Tensor_Base(
    shape_type &&shape) noexcept :
    _shape(std::move(shape)) {
    _host = host_allocator::allocate(capacity());
};
} // namespace llframe
// impletment  _Tensor_Base
namespace llframe {
template <size_t Dims, class Ty, is_Device Device>
constexpr _Tensor_Base<Dims, Ty, Device>::size_type
_Tensor_Base<Dims, Ty, Device>::capacity() const {
    if (_shape.empty()) return 0;
    size_type capacity_ = 1;
    std::for_each(_shape.cbegin(), _shape.cend(),
                  [&capacity_](const size_type &v) { capacity_ *= v; });
    return capacity_;
}
} // namespace llframe

#endif //__LLFRAME_TENSOR_HPP__