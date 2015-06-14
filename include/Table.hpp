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
#include <vector>
#include <thread>

// Internal headers
#include "Fork.hpp"
#include "Philosopher.hpp"

class Table {
 public:
  // Constructors
  Table() = default;

  Table(std::vector<Philosopher> &&philosophers)
      : _philosophers(std::move(philosophers)),
        _forks(_philosophers.size()+1) {
  }

  // Concrete methods
  Fork &fork(unsigned int id) {
    return _forks.at(id);
  }

  Philosopher &philosopher(unsigned int id) {
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
  std::vector<Philosopher> _philosophers;
  std::vector<Fork> _forks;
};

#endif
