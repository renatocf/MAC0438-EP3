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

// Internal headers
#include "Fork.hpp"
#include "Philosopher.hpp"

// Forward declaration
class Table;

// Pointer
using TablePtr = std::shared_ptr<Table>;

// Class
class Table {
 public:
  // Static methods
  template<typename... Args>
  static TablePtr make(Args... args) {
    return TablePtr(new Table(std::forward<Args>(args)...));
  }

  // Concrete methods
  ForkPtr fork(unsigned int id) {
    return _forks.at(id);
  }

  PhilosopherPtr philosopher(unsigned int id) {
    return _philosophers.at(id);
  }

  unsigned int number_forks() {
    return _forks.size();
  }

  unsigned int number_philosophers() {
    return _philosophers.size();
  }

 private:
  // Instance variables
  std::vector<PhilosopherPtr> _philosophers;
  std::vector<ForkPtr> _forks;

  // Constructors
  Table() = default;

  Table(const std::vector<unsigned int> weights)
      : _forks(weights.size()+1) {
    for (unsigned int id = 0; id < weights.size(); id++)
      _philosophers.emplace_back(Philosopher::make(weights[id], id));
  }
};

#endif
