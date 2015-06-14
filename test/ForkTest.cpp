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
#include <chrono>
#include <thread>

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Fork.hpp"

// Helpers
using ::testing::ContainerEq;

struct AFork : public testing::Test {
  ForkPtr fork = Fork::make(0);
  PhilosopherPtr philosopher1 = Philosopher::make(80, 1);
  PhilosopherPtr philosopher2 = Philosopher::make(80, 2);
};

TEST_F(AFork, hasCorrectId) {
  ASSERT_EQ(fork->id(), 0);
}

TEST_F(AFork, canBeGottenByPhilosophersInTheRightOrder) {
  std::vector<unsigned int> arrive;
  std::vector<unsigned int> result { 0, 1, 2, 3, 4 };

  std::vector<std::thread> threads;
  for (unsigned int id = 0; id < 5; id++) {
    threads.emplace_back([this, id, &arrive]() {
      fork->take();
      // Sleep to avoid races just after finishing
      std::this_thread::sleep_for(std::chrono::milliseconds(id * 2));
      arrive.push_back(id);
      fork->drop();
    });
  }

  for (auto& thread : threads)
    thread.join();

  ASSERT_THAT(arrive, ContainerEq(result));
}
