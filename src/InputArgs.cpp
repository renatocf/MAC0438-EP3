// Standard headers
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

  std::vector<unsigned int> philosophers_weight;

  for(unsigned int i = 0; i < number_philosophers; ++i) {
    unsigned int weight;
    input_file >> weight;
    //std::cout << weight << std::endl;
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
                                  std::vector<unsigned int> weights, 
                                  unsigned int number_philosophers) {
  philosophers.emplace_back(Philosopher::make(
                                weights[0],
                                Philosopher::hand_preference::left_handed));

  for (unsigned int i = 1; i < number_philosophers; ++i)
    philosophers.emplace_back(Philosopher::make(weights[i]));
}