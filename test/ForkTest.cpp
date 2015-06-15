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
  ForkPtr fork = Fork::make();
  PhilosopherPtr philosopher1 = Philosopher::make(80);
  PhilosopherPtr philosopher2 = Philosopher::make(80);

  AFork() {
    fork->place(0);
    philosopher1->place(1);
    philosopher2->place(2);
  }
};

TEST_F(AFork, isInTheCorrectPlace) {
  ASSERT_EQ(0, fork->place());
}

TEST_F(AFork, canBeGottenByPhilosophersInTheRightOrder) {
  std::vector<unsigned int> arrive;
  std::vector<unsigned int> result { 0, 1, 2, 3, 4 };

  std::vector<std::thread> threads;
  for (unsigned int place = 0; place < 5; place++) {
    threads.emplace_back([this, place, &arrive]() {
      fork->take();
      // Sleep to avoid races just after finishing
      std::this_thread::sleep_for(std::chrono::milliseconds(place * 2));
      arrive.push_back(place);
      fork->drop();
    });
  }

  for (auto& thread : threads)
    thread.join();

  ASSERT_THAT(arrive, ContainerEq(result));
}
