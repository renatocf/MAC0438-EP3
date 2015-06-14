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
#include "Table.hpp"

struct ATable : public testing::Test {
  std::vector<PhilosopherPtr> philosophers {
    Philosopher::make(65,  0), // Descartes
    Philosopher::make(70,  1), // Plato
    Philosopher::make(75,  2), // Voltaire
    Philosopher::make(85,  3), // Confucius
    Philosopher::make(100, 4)  // Socrates
  };

  TablePtr table = Table::make(std::vector<PhilosopherPtr>(philosophers));
};

TEST_F(ATable, hasRightNumberOfPhilosophers) {
  ASSERT_EQ(table->number_philosophers(), philosophers.size());
}

TEST_F(ATable, hasInitializedAllPhilosophers) {
  for (unsigned int id = 0; id < philosophers.size(); id++) {
    ASSERT_EQ(table->philosopher(id)->id(), philosophers[id]->id());
    ASSERT_EQ(table->philosopher(id)->weight(), philosophers[id]->weight());
  }
}

TEST_F(ATable, hasRightNumberOfForks) {
  ASSERT_EQ(table->number_forks(), philosophers.size()+1);
}
