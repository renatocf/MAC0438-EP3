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

// Libraries
#include "Philosopher.hpp"

void Philosopher::RightHanded::eat() {
	philosopher->table()->right_fork(philosopher->position())->take();
	philosopher->table()->left_fork(philosopher->position())->take();
}

void Philosopher::RightHanded::drop_forks() {
	philosopher->table()->right_fork(philosopher->position())->drop();
	philosopher->table()->left_fork(philosopher->position())->drop();
}

void Philosopher::LeftHanded::eat() {
  philosopher->table()->left_fork(philosopher->position())->take();
  philosopher->table()->right_fork(philosopher->position())->take();
}

void Philosopher::LeftHanded::drop_forks() {
  philosopher->table()->left_fork(philosopher->position())->drop();
  philosopher->table()->right_fork(philosopher->position())->drop();
}