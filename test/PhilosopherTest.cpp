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

// Standard headers
#include <thread>
#include <future>
#include <iostream>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Philosopher.hpp"

// Helpers
using ::testing::NotNull;
using ::testing::Pointee;

class APhilosopher : public testing::Test {
 protected:
  TablePtr empty_table = Table::make();
  PhilosopherPtr philosopher = Philosopher::make(80);
};

class ADinningPhilosopher : public testing::Test {
 protected:

  PhilosopherPtr philosopher = Philosopher::make(
    80, Philosopher::hand_preference::right_handed, 42);

  TablePtr table = Table::make(std::vector<PhilosopherPtr>{
    philosopher
  });
};

class DinningPhilosophers : public testing::Test {
 protected:

  PhilosopherPtr philosopher1 = Philosopher::make(
    80, Philosopher::hand_preference::right_handed, 42);
  PhilosopherPtr philosopher2 = Philosopher::make(
    40, Philosopher::hand_preference::right_handed, 1729);
  PhilosopherPtr philosopher3 = Philosopher::make(
    60, Philosopher::hand_preference::right_handed, 31415);
  


  TablePtr table = Table::make(std::vector<PhilosopherPtr>{
    philosopher1, philosopher2, philosopher3
  });
};

TEST_F(APhilosopher, hasCorrectHunger) {
  ASSERT_EQ(80, philosopher->hunger());
}

TEST_F(APhilosopher, canHaveTableAssigned) {
  philosopher->table(empty_table.get());
  ASSERT_EQ(empty_table.get(), philosopher->table());
}

TEST_F(ADinningPhilosopher, isInTheCorrectPlace) {
  ASSERT_EQ(0, philosopher->position());
}

TEST_F(ADinningPhilosopher, hasTableAssigned) {
  ASSERT_THAT(philosopher->table(), NotNull());
}

TEST_F(DinningPhilosophers, canEatWithNoMeals) {
  std::atomic_int number_meals(0);
  for (auto philosopher : table->philosophers()) {
    philosopher->eat(number_meals);
  }
}

TEST_F(DinningPhilosophers, canEatWithOneMealPerPhilosopher) {
  std::atomic_int number_meals(table->number_philosophers());
  for (auto philosopher : table->philosophers()) {
    philosopher->eat(number_meals);
  }
}

TEST_F(DinningPhilosophers, canEatWithTwoMealsPerPhilosopher) {
  std::atomic_int number_meals(2 * table->number_philosophers());
  for (auto philosopher : table->philosophers()) {
    philosopher->eat(number_meals);
  }
}

TEST_F(ADinningPhilosopher, canThink) {
  for (auto philosopher : table->philosophers()) {
    std::mt19937_64 eng{42};
    std::uniform_int_distribution<> dist(10, 20);
    auto time = std::chrono::milliseconds{dist(eng)};

    ASSERT_EQ(time, philosopher->think());
  }
}
