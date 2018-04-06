#include <iostream>
#include <iomanip>
#include "utils.h"

int main() {

  if (helper::utils::check_install_status()) {
    helper::utils::initialize_first_time();
    helper::utils::start_menu_run();
  } else {
    std::cout << std::setw(50) << "Enter the Password : ";
    std::string p;
    std::cin >> p;
    if (helper::utils::validate_password(p))
      helper::utils::start_menu_run();
    else {
      std::cerr << "Incorrect Password.." << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}