#ifndef HPP_INPUT_ARGS_DEFINED
#define HPP_INPUT_ARGS_DEFINED

// Standard headers
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Philosopher.hpp"

struct InputArgs {
 public:
  std::string  				      file_path;
  unsigned int 				      number_meals;
  char         				      operation_mode;
  unsigned int 				      total_weight;

  InputArgs(int argc, char const *const *argv, std::vector<PhilosopherPtr>& philosophers);

  void make_philosophers(std::vector<PhilosopherPtr>& hungry_philosophers, 
                         std::vector<unsigned int> weights,
                         unsigned int number_philosophers);

 private:
  std::vector<std::stringstream> argstream;

  void process_input(std::vector<PhilosopherPtr>& philosophers);
  void read_input();
};

#endif
