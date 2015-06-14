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

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Table.hpp"

class APhilosopher : public testing::Test {
 protected:
  TablePtr empty_table = Table::make();
  PhilosopherPtr philosopher = Philosopher::make(80, 0);
};

TEST_F(APhilosopher, hasCorrectWeight) {
  ASSERT_EQ(philosopher->weight(), 80);
}

TEST_F(APhilosopher, hasCorrectId) {
  ASSERT_EQ(philosopher->id(), 0);
}

TEST_F(APhilosopher, canHaveTableAssigned) {
  philosopher->table(empty_table);
  ASSERT_EQ(philosopher->table(), empty_table);
}
