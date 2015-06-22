// Standard headers
#include <cstdlib>
#include <iostream>

// Internal headers
#include "Dinner.hpp"
#include "InputArgs.hpp"
#include "Philosopher.hpp"

int main(int argc, char **argv)
{
  if (argc != 4) {
    std::cerr << "USAGE: "
              << argv[0]
              << " filename R [U|P]"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<PhilosopherPtr> hungry_philosophers;
  InputArgs input_args(argc, argv, hungry_philosophers);
  DinnerPtr dinner = Dinner::make(hungry_philosophers);
  dinner->serve(input_args.number_meals);

  return EXIT_SUCCESS;
}