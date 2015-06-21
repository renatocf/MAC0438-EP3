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
#include <atomic>
#include <chrono>
#include <memory>
#include <random>
#include <thread>
#include <iostream>

// Internal headers
#include "Fork.hpp"
#include "Table.hpp"


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
  // Alias
  enum class hand_preference { left_handed, right_handed };

  // Static methods
  template<typename... Args>
  static PhilosopherPtr make(Args... args) {
    return PhilosopherPtr(new Philosopher(std::forward<Args>(args)...));
  }

  // Overloaded operators
  void operator()(std::atomic_int &atomic_number_meals) {
    while (atomic_number_meals --> 0) {
      think();
      eat();
    }
  }

  // Concrete methods
  auto think() -> decltype(std::chrono::milliseconds()) {
    std::mt19937_64 eng{_seed};
    std::uniform_int_distribution<> dist(10, 20);
    auto time = std::chrono::milliseconds{dist(eng)};
    std::this_thread::sleep_for(time);
    return time;
  }

  void eat() {
    _behavior->eat();
    std::cerr << "Philosopher " << _position << " eating!" << std::endl;
  }

  void table(Table *table) {
    _table = table;
  }

  Table *table() {
    return _table;
  }

  unsigned int weight() {
    return _weight;
  }

  void position(unsigned int position) {
    _position = position;
  }

  unsigned int position() {
    return _position;
  }

 private:
  // Inner classes
  class Behavior {
   public:
    virtual void eat() = 0;
    virtual ~Behavior() {}
  };
  using BehaviorPtr = std::shared_ptr<Behavior>;

  class RightHanded : public Behavior {
    Philosopher *philosopher;

   public:
    RightHanded(Philosopher *p) : philosopher(p) {
    }
    void eat() override;
    ~RightHanded() override {}
  };

  class LeftHanded : public Behavior {
    Philosopher *philosopher;

   public:
    LeftHanded(Philosopher *p) : philosopher(p) {
    }
    void eat() override;
    ~LeftHanded() override {}
  };

  // Instance variables
  unsigned int _weight;
  unsigned int _position;
  unsigned int _seed;

  std::shared_ptr<Philosopher::Behavior> _behavior;
  Table *_table;

  // Constructors
  Philosopher(unsigned int weight,
              hand_preference preference = hand_preference::right_handed,
              unsigned int seed = std::random_device{}())
      : _weight(weight), _seed(seed) {

    switch (preference) {
      case hand_preference::right_handed:
        _behavior = std::make_shared<RightHanded>(this);
        break;
      case hand_preference::left_handed:
        _behavior = std::make_shared<LeftHanded>(this);
        break;
    }
  }
};

#endif
