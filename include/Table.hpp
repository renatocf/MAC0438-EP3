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
#include <ctime>
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
class Table : public std::enable_shared_from_this<Table> {
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

  ForkPtr fork(unsigned int fork_position) {
    return _forks.at(fork_position);
  }

  ForkPtr left_fork(unsigned int philosopher_position) {
    return _forks.at(philosopher_position);
  }

  ForkPtr right_fork(unsigned int philosopher_position) {
    return _forks.at((philosopher_position + 1) % number_forks());
  }

  unsigned int number_philosophers() const {
    return _philosophers.size();
  }

  PhilosopherPtr philosopher(unsigned int philosopher_position) {
    return _philosophers.at(philosopher_position);
  }

  void philosopher_has_eaten(unsigned int position) {
    _eaten_meals[position]++;
  }

  unsigned int meals_eaten_by(unsigned int position) {
    return _eaten_meals[position];
  }

  void start_dinner() {
    dinner_init_time = clock();
  }

  clock_t init_time() {
    return dinner_init_time;
  }

  const std::vector<PhilosopherPtr> &philosophers() const {
    return _philosophers;
  }

 private:
  // Instance variables
  std::vector<PhilosopherPtr> _philosophers;
  std::vector<ForkPtr> _forks;
  std::vector<unsigned int> _eaten_meals;
  clock_t dinner_init_time;

  // Constructors
  Table(const std::vector<PhilosopherPtr>& philosophers = {});
};

#endif
