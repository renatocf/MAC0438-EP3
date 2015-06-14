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

#ifndef HPP_TABLE_DEFINED
#define HPP_TABLE_DEFINED

// Standard headers
#include <memory>
#include <thread>
#include <vector>

// Forward declaration
class Fork;
class Table;
class Philosopher;

// Pointer
using ForkPtr = std::shared_ptr<Fork>;
using TablePtr = std::shared_ptr<Table>;
using PhilosopherPtr = std::shared_ptr<Philosopher>;

// Class
class Table {
 public:
  // Static methods
  template<typename... Args>
  static TablePtr make(Args... args) {
    return TablePtr(new Table(std::forward<Args>(args)...));
  }

  // Concrete methods
  unsigned int number_forks() const {
    return _forks.size();
  }

  ForkPtr fork(unsigned int fork_id) {
    return _forks.at(fork_id);
  }

  ForkPtr left_fork(unsigned int philosopher_id) {
    return _forks.at(philosopher_id);
  }

  ForkPtr right_fork(unsigned int philosopher_id) {
    return _forks.at((philosopher_id + 1) % number_forks());
  }

  PhilosopherPtr philosopher(unsigned int philosopher_id) {
    return _philosophers.at(philosopher_id);
  }

  unsigned int number_philosophers() const {
    return _philosophers.size();
  }

  const std::vector<PhilosopherPtr> &philosophers() const {
    return _philosophers;
  }

 private:
  // Instance variables
  std::vector<PhilosopherPtr> _philosophers;
  std::vector<ForkPtr> _forks;

  // Constructors
  Table() = default;

  Table(const std::vector<unsigned int> weights);
};

#endif
