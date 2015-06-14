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

#ifndef HPP_PHILOSOPHER_DEFINED
#define HPP_PHILOSOPHER_DEFINED

// Standard headers
#include <memory>

// Cyclic dependency
class Table;
using TablePtr = std::shared_ptr<Table>;

// Forward declaration
class Philosopher;

// Pointer
using PhilosopherPtr = std::shared_ptr<Philosopher>;

// Class
class Philosopher {
 public:
  // Static methods
  template<typename... Args>
  static PhilosopherPtr make(Args... args) {
    return PhilosopherPtr(new Philosopher(std::forward<Args>(args)...));
  }

  // Concrete methods
  void table(TablePtr table) {
    _table = table;
  }

  TablePtr table() {
    return _table;
  }

  unsigned int weight() {
    return _weight;
  }

  unsigned int id() {
    return _id;
  }

 private:
  // Instance variables
  unsigned int _id;
  unsigned int _weight;
  TablePtr _table;

  // Constructors
  Philosopher(unsigned int weight, unsigned int id)
      : _weight(weight), _id(id) {
  }
};

#endif
