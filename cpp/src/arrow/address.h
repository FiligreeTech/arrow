// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef ARROW_ADDRESS_H
#define ARROW_ADDRESS_H

#include <cstddef>

namespace arrow {

  class Device;

  /// \brief How addresses are represented across all devices.
  ///
  /// There are enough bits to hold a memory handle in CUDA/OpenCL
  /// as well as a native address in CPU memory.
  using RawAddress = uint8_t*;

  ////////////////////////////////////////////////////////////////////////////////
  /// \class Address
  /// \brief represents a memory location on a compute device somewhere. There is
  /// no ownership associated with either the underlying address or the device.
  ///
  /// A null device implies the address is in CPU memory.
  class Address {
  public :
    /// Constructor.
    Address(RawAddress baseAddress,
            Device* device = nullptr,
            ptrdiff_t offset = 0)
      : baseAddress_(baseAddress)
      , device_(nullptr)
      , offset_(offset)
    {
    }

    /// Copy constructor.
    Address(const Address& rhs)
      : baseAddress_(rhs.baseAddress_)
      , device_(rhs.device_)
      , offset_(rhs.offset_)
    {
    }

    /// Assignment
    Address& operator=(const Address& addr)
    {
      baseAddress_ = rhs.baseAddress_;
      device_ = rhs.device_;
      offset_ = rhs.offset_;
      return *this;
    }

    /// get the base address
    RawAddress baseAddress() const { return baseAddress_;}

    /// get the offset
    ptrdiff_t offset() const { return offset_;}

    /// get the device
    Device*   device() const { return device_;}

    /// offset the address
    Address &offset(ptrdiff_t off)
    {
      offset_ += off;
      return *this;
    }

    /// offset the address
    Address &operator+=(ptrdiff_t off)
    {
      offset_ += off;
      return *this;
    }

    /// offset the address
    Address &operator-=(ptrdiff_t off)
    {
      offset_ -= off;
      return *this;
    }

  protected :
    RawAddress baseAddress_; ///< The address on the device, hard cast to a pointer
    ptrdiff_t  offset_;      /// the offset from the base address
    Device*    device_;      ///< Or should it be a shared/weak pointer?
  };

  /// offset the address
  inline Address operator+(const Address& address, ptrdiff_t offset)
  {
    return Address(address.baseAddress(),
                   address.device(),
                   address.offset() + offset);

  }

  /// offset the address
  inline Address operator-(const Address& address, ptrdiff_t offset)
  {
    return Address(address.baseAddress(),
                   address.device(),
                   address.offset() - offset);

  }

}  // namespace arrow

#endif  // ARROW_ADDRESS_H_
