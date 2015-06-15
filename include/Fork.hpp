/******************************************************************************/
/*  Copyright 2015 Lucas Dário and Renato Cordeiro Ferreira                   */
/*                                                                            */
/*  Licensed under the Apache License, Version 2.0 (the "License");           */
/*  you may not use this file except in compliance with the License.          */
/*  You may obtain a copy of the License at                                   */
/*                                                                            */
/*      http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                            */
/*  Unless required by applicable law or agreed to in writing, software       */
/*  distributed under the License is distributed on an "AS IS" BASIS,         */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  */
/*  See the License for the specific language governing permissions and       */
/*  limitations under the License.                                            */
/******************************************************************************/

#ifndef HPP_FORK_DEFINED
#define HPP_FORK_DEFINED

// Standard headers
#include <queue>
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>
#include <condition_variable>

// Internal headers
#include "Philosopher.hpp"

// Forward declaration
class Fork;

// Pointer
using ForkPtr = std::shared_ptr<Fork>;

// Class
class Fork {
 public:
  // Static methods
  template<typename... Args>
  static ForkPtr make(Args... args) {
    return ForkPtr(new Fork(std::forward<Args>(args)...));
  }

  // Synchronized methods
  void take() {
    std::unique_lock<std::mutex> lock(_mutex);
    wait(lock, not_using);
  }

  void drop() {
    std::unique_lock<std::mutex> lock(_mutex);
    signal(not_using);
  }

  // Concrete methods
  unsigned int place() const {
    return _place;
  }

  void place(unsigned int place) {
    _place = place;
  }

 private:
  // Instance variables
  unsigned int _place;

  // Monitor variables
  std::mutex _mutex;
  std::queue<std::thread::id> _waiting;
  std::condition_variable not_using;

  // Monitor methods
  void wait(std::unique_lock<std::mutex> &lock,
            std::condition_variable &cv) {

    _waiting.push(std::this_thread::get_id());
    cv.wait(lock, [this]() { return _waiting.front() == std::this_thread::get_id(); });
    _waiting.pop();
  }

  void signal(std::condition_variable &cv) {
    cv.notify_all();
  }
};

#endif
