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
  std::vector<Philosopher> philosophers {
    Philosopher(65), // Descartes
    Philosopher(70), // Plato
    Philosopher(75), // Voltaire
    Philosopher(85), // Confucius
    Philosopher(100) // Socrates
  };

  Table table{std::vector<Philosopher>(philosophers)};
};

TEST_F(ATable, hasRightNumberOfPhilosophers) {
  ASSERT_EQ(table.number_philosophers(), philosophers.size());
}

TEST_F(ATable, hasInitializedAllPhilosophers) {
  for (unsigned int id = 0; id < philosophers.size(); id++) {
    ASSERT_EQ(table.philosopher(id).weight(), philosophers[id].weight());
  }
}

TEST_F(ATable, hasRightNumberOfForks) {
  ASSERT_EQ(table.number_forks(), philosophers.size()+1);
}
