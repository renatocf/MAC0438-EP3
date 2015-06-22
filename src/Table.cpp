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

// Internal headers
#include "Table.hpp"
#include "Fork.hpp"
#include "Philosopher.hpp"

Table::Table(const std::vector<PhilosopherPtr>& philosophers)
    : _philosophers(philosophers), _forks(philosophers.size()) {
  for (unsigned int position = 0; position < _philosophers.size(); position++) {
    _forks[position] = Fork::make();
    _forks[position]->position(position);

    _philosophers[position]->position(position);
    _philosophers[position]->table(this);

    _eaten_meals.push_back(0);
  }
}
