// Standard headers
#include <cmath>
#include <fstream>

// Internal headers
#include "InputArgs.hpp"



InputArgs::InputArgs(int argc, char const *const *argv, 
                     std::vector<PhilosopherPtr>& philosophers)
    : argstream(argv, argv + argc), total_weight(0) {
  read_input();
  process_input(philosophers);
}

void InputArgs::process_input(std::vector<PhilosopherPtr>& philosophers) {
  std::ifstream input_file;
  int number_philosophers = 0;

  input_file.open(file_path);  
  if (!input_file.is_open()) {
    std::cerr << "Problem reading file!" << std::endl;
  }

  input_file >> number_philosophers;
  if (number_philosophers < 3) {
    std::cerr << "Not enough philosophers for a real dinner!" << std::endl;
  }

  std::vector<double> philosophers_weight;

  for(unsigned int i = 0; i < number_philosophers; ++i) {
    double weight;
    input_file >> weight;
    total_weight+= weight;
    philosophers_weight.push_back(weight);
  }

  make_philosophers(philosophers, philosophers_weight, number_philosophers);
}

void InputArgs::read_input() {
  argstream[1] >> file_path;
  argstream[2] >> number_meals;
  argstream[3] >> operation_mode;
}

void InputArgs::make_philosophers(std::vector<PhilosopherPtr>& philosophers, 
                                  std::vector<double> weights, 
                                  unsigned int number_philosophers) {

  for (unsigned int i = 0; i < number_philosophers; ++i) {
    double hunger;
    if (operation_mode == 'U') {
      hunger = number_meals;
    } else if (operation_mode == 'P') {
      hunger = ceil(number_meals * (weights[i]/total_weight));
    } else {
      std::cerr << "Invalid operation mode!" << std::endl;
    }
    philosophers.emplace_back(
                   Philosopher::make(
                      hunger,
                      (i==0) ? Philosopher::hand_preference::left_handed 
                             : Philosopher::hand_preference::right_handed));
  }
}