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

#ifndef ARROW_DEVICE_H
#define ARROW_DEVICE_H

namespace arrow {

  ////////////////////////////////////////////////////////////////////////////////
  /// \class Device
  /// \brief Abstract base class that represents a compute device with it's own
  /// address space, allows for allocation, deallocation and data transfer between
  /// devices.
  ///
  /// A null device pointer implies the address is in CPU memory.
  class Device {
  public :
    /// dtor
    virtual ~Device();

    /// Fetch the global host device
    static &hostDevice();
  };

}  // namespace arrow

#endif  // ARROW_DEVICE_H_
