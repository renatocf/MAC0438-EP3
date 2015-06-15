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

#ifndef HPP_DINNER_DEFINED
#define HPP_DINNER_DEFINED

// Standard headers
#include <atomic>
#include <memory>

// Internal headers
#include "Philosopher.hpp"

// Forward declaration
class Dinner;

// Pointer
using DinnerPtr = std::shared_ptr<Dinner>;

class Dinner {
 public:
  // Static methods
  template<typename... Args>
  static DinnerPtr make(Args... args) {
    return DinnerPtr(new Dinner(std::forward<Args>(args)...));
  }

  // Concrete methods
  void serve(int number_meals) {
    std::atomic_int atomic_number_meals{number_meals};

    std::vector<std::thread> eating;
    for (auto& philosopher : _table->philosophers())
      eating.emplace_back(*philosopher, std::ref(atomic_number_meals));

    for (auto& eating_philosopher : eating)
      eating_philosopher.join();
  }

 private:
  // Instance variables
  TablePtr _table;

  // Constructors
  Dinner(std::vector<PhilosopherPtr> philosophers)
      : _table(Table::make(philosophers)) {
  }
};

#endif
