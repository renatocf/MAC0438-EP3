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

// External headers
#include "gmock/gmock.h"

// Internal headers
#include "Dinner.hpp"
#include "Philosopher.hpp"

struct ADinner : public testing::Test {
  std::vector<PhilosopherPtr> philosophers {
    Philosopher::make(65, Philosopher::hand_preference::left_handed), // Descartes
    Philosopher::make(70), // Plato
    Philosopher::make(75), // Voltaire
    Philosopher::make(85), // Confucius
    Philosopher::make(100) // Socrates
  };

  DinnerPtr dinner = Dinner::make(philosophers);
};

TEST_F(ADinner, canBeServedWithNoMeals) {
  dinner->serve(0);
}

TEST_F(ADinner, canBeServedWithOneMeal) {
  dinner->serve(1);
}

TEST_F(ADinner, canBeServedWithOneMealPerPhilosopher) {
  dinner->serve(philosophers.size());
}

TEST_F(ADinner, canBeServedWithTwoMealsPerPhilosopher) {
  dinner->serve(2 * philosophers.size());
}
