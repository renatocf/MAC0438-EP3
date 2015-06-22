#ifndef HPP_INPUT_ARGS_DEFINED
#define HPP_INPUT_ARGS_DEFINED

// Standard headers
#include <string>
#include <vector>
#include <sstream>

// Internal headers
#include "Philosopher.hpp"

struct InputArgs {
 public:
  std::string  				      file_path;
  unsigned int 				      number_meals;
  char         				      operation_mode;
  double       				      total_weight;

  InputArgs(int argc, char const *const *argv, std::vector<PhilosopherPtr>& philosophers);

 private:
  std::vector<std::stringstream> argstream;

  void process_input(std::vector<PhilosopherPtr>& philosophers);
  void read_input();
  void make_philosophers(std::vector<PhilosopherPtr>& hungry_philosophers, 
                         std::vector<double> weights,
                         unsigned int number_philosophers);
};

#endif
