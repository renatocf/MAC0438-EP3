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
#include <future>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Fork.hpp"
#include "Table.hpp"
#include "Philosopher.hpp"

struct ATable : public testing::Test {
  std::vector<PhilosopherPtr> philosophers {
    Philosopher::make(65), // Descartes
    Philosopher::make(70), // Plato
    Philosopher::make(75), // Voltaire
    Philosopher::make(85), // Confucius
    Philosopher::make(100) // Socrates
  };

  TablePtr table = Table::make(philosophers);
};

TEST_F(ATable, hasRightNumberOfPhilosophers) {
  ASSERT_EQ(philosophers.size(),
            table->number_philosophers());
}

TEST_F(ATable, hasInitializedAllPhilosophers) {
  for (unsigned int position = 0; position < philosophers.size(); position++) {
    ASSERT_EQ(position, table->philosopher(position)->position());
    ASSERT_EQ(philosophers[position]->weight(),
              table->philosopher(position)->weight());
  }
}

TEST_F(ATable, hasRightNumberOfForks) {
  ASSERT_EQ(philosophers.size(), table->number_forks());
}

TEST_F(ATable, hasInitializedAllForks) {
  for (unsigned int position = 0; position < philosophers.size(); position++) {
    ASSERT_EQ(position, table->fork(position)->position());
  }
}

TEST_F(ATable, hasForksInTheRightPlace) {
  for (const auto philosopher : table->philosophers()) {
    auto position = philosopher->position();
    ASSERT_EQ(position, table->left_fork(position)->position());
    ASSERT_EQ((position+1) % table->number_forks(),
              table->right_fork(position)->position());
  }
}
