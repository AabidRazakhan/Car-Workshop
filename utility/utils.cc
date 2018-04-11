/*
*   Copyright (c) Ashar Khan 2018. <ashar786khan@gmail.com>
*    This file is part of CSE202 Car Workshop Project.
*   Car Workshop is free software : you can redistribute it and/or modify
*    it under the terms of GNU General Public License as published by the Free Software Foundation,
*   either version 3 of the License, or (at your option) any later version.
*
*   This Application is distributed in the hope that it will be useful
*    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
*   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with this Source File.
*   If not, see <http:www.gnu.org/licenses/>.
*/


#include <fstream>
#include <iomanip>
#include "utils.h"
#include "../file_helper/writer.h"
#include "../file_helper/reader.h"
#include "../file_helper/writer.cc"
#include "../file_helper/reader.cc"
#include "../base/order.h"

using namespace helper;

data_register data_register::get_data_register_instance() {
  try {
    std::unique_ptr<reader<financial::order>> reader1(new reader<financial::order>(PAST_ORDERS_NAME, true));
    std::unique_ptr<reader<financial::order>> reader2(new reader<financial::order>(ACTIVE_ORDERS_NAME, true));
    std::vector<financial::order> vector, vector1;
    reader1->read_all(vector);
    reader2->read_all(vector1);
    data_register dataRegister;
    dataRegister.total_completed = static_cast<int>(vector.size());
    dataRegister.total_pending = static_cast<int>(vector1.size());
    return dataRegister;
  } catch (std::runtime_error &e) {
    //NO SUCH FILE OR DIRECTORY FOUND
    return {}; //will return -1 -1 as a flag that nothing was found
  }

}

bool utils::check_install_status() {
  clear_screen();
  //returns true on new install/ when fail to find config file
  std::ifstream stream(CONFIG_FILE_NAME, std::ios::in | std::ios::binary);
  bool stat = stream.fail();
  if (stream.is_open())
    stream.close();
  return stat;
}
void utils::initialize_first_time() {
  clear_screen();
  std::string username;
  std::cout << "It Looks like first run of the Program, We need to get you ready..." << std::endl;
  std::cout << "Who is the Admin User : ";
  getline(std::cin, username);
  bool accepted = false;
  while (!accepted) {
    std::string pass;
    std::cout << std::endl << "Enter a Fresh Password (min 5 characters long) for user " << username << " : ";
    std::cin >> pass;
    if (pass.length() >= 5) {
      accepted = true;
      config config1(pass);
      config1.create_time = date::date_time(0);
      config1.last_launch = date::date_time(0);
      strcpy(config1.admin_name, username.c_str());
      file::writer<config> *writer = new file::writer<config>(CONFIG_FILE_NAME, true);
      writer->write(config1);
      delete writer; //explicitly calls destructor to release mutex of owned file

    } else
      std::cout << "To short Password... Try Again" << std::endl;
  }
}
bool utils::validate_password(const std::string &s) {
  std::unique_ptr<file::reader<config>> r(new file::reader<config>(CONFIG_FILE_NAME, true));
  return strcmp(r->read().password, s.c_str()) == 0;
}
bool utils::change_password() {
  clear_screen();
  file::reader<config> *reader1 = new file::reader<config>(CONFIG_FILE_NAME, true);
  config c = reader1->read();
  delete reader1;
  std::cout << "Enter the new Password for " << c.admin_name << " : ";
  std::string new_pass;
  std::cin >> new_pass;
  if (new_pass.length() >= 5) {
    strcpy(c.password, new_pass.c_str());
    file::writer<config> *writer1 = new file::writer<config>(CONFIG_FILE_NAME, true);
    c.create_time = date::date_time(0);
    writer1->write(c);
    delete writer1;
    std::cout << "Password changed Successfully.." << std::endl;
    re_authenticate();
  } else {
    std::cerr << "Too Small Password, Falling back to previous password" << std::endl;
  }
}
bool utils::change_username() {
  clear_screen();
  file::reader<config> *reader1 = new file::reader<config>(CONFIG_FILE_NAME, true);
  config c = reader1->read();
  delete reader1;
  std::cout << "Enter the new username (no space): ";
  std::string new_name;
  std::cin >> new_name;
  strcpy(c.admin_name, new_name.c_str());
  file::writer<config> *writer1 = new file::writer<config>(CONFIG_FILE_NAME, true);
  writer1->write(c);
  delete writer1;
  start_menu_run();
}
void utils::restore_and_delete_config() {
  clear_screen();
  std::cout << "This action cannot be Undone. (Type yes to proceed) : ";
  std::string s;
  std::cin >> s;
  if (!(s == "yes")) {
    std::cout << std::endl << "Aborted the Delete Command." << std::endl;
    utils::start_menu_run();
  }

#ifdef __WIN32
  std::system((std::string("del ") + std::string(CONFIG_FILE_NAME)).c_str());
#else
  std::system((std::string("rm -rf ") + std::string(CONFIG_FILE_NAME)).c_str());
#endif

  exit(0);
}
void utils::start_menu_run() {

  file::reader<config> *reader1 = new file::reader<config>(CONFIG_FILE_NAME, true);
  config c = reader1->read(1);
  delete reader1;

  file::writer<config> *writer1 = new file::writer<config>(CONFIG_FILE_NAME, true);
  c.last_launch = date::date_time(0);
  writer1->write(c);
  delete writer1;
  ui::show_main_menu(c);
}
void utils::clear_screen() {
#ifdef __WIN32
  std::system("cls")
#else
  std::system("clear");
#endif
}
void utils::re_authenticate() {
  clear_screen();
  if (check_install_status()) {
    initialize_first_time();
    start_menu_run();
  } else {
    std::cout << std::setw(50) << " Re-authenticate with the Password : ";
    std::string p;
    std::cin >> p;
    if (validate_password(p))
      start_menu_run();
    else {
      std::cerr << std::setw(50) << "Incorrect Password.." << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

}
void utils::_exit() {
  file::reader<config> *reader1 = new file::reader<config>(CONFIG_FILE_NAME, true);
  config c = reader1->read();
  delete reader1;
  file::writer<config> *writer1 = new file::writer<config>(CONFIG_FILE_NAME, true);
  c.last_launch = date::date_time(0);
  writer1->write(c);
  delete writer1;
  exit(0);

}

void ui::show_main_menu(config c) {
  utils::clear_screen();
  c.admin_name[0] = static_cast<char>(toupper(c.admin_name[0]));

  data_register aRegister = data_register::get_data_register_instance();
  std::string s, s2;
  if (aRegister.total_pending == -1 || aRegister.total_completed == -1) {
    s = "N/A";
    s2 = "N/A";
  } else {
    s = std::to_string(aRegister.total_completed);
    s2 = std::to_string(aRegister.total_pending);
  }
  using namespace std;
  cout << setw(60) << "Welcome " << c.admin_name << endl << endl << endl;
  cout << setw(50) << "Last Login at : " << c.last_launch.get_date_timestamp() << " by " << c.admin_name << endl << endl
       << endl;
  cout << setw(66) << "Active Orders : " << s2 << endl;
  cout << setw(67) << "Pending Orders  : " << s << endl << endl << endl;
  cout << setw(70) << "1. Take a new Order" << endl;
  cout << setw(70) << "2. Modify the Order" << endl;
  cout << setw(70) << "3. Show  all  Order" << endl;
  cout << setw(70) << "4. Settings & Utils" << endl;
  cout << setw(70) << "5. Save  and   Exit" << endl;
  cout << endl << endl << "Press respective keys to perform ops : ";
  size_t x = 0;
  while (!x) {
    cin >> x;
    if (x > 5) {
      x = 0;
      cout << "\nOops Unrecognized. Retry : ";
    } else {
      ui::launch_option(static_cast<int>(x));
    }
  }
}
void ui::launch_option(int x) {
  switch (x) {
    case 1 : ui::options::take_order();
      break;
    case 2 : ui::options::modify_order();
      break;
    case 3 : ui::options::show_all();
      break;
    case 4 : ui::options::settings_and_utils();
      break;
    case 5 : utils::_exit();
      break;
    default:std::cerr << std::setw(60) << "Unknown Option : Exiting";
      utils::_exit();
      break;
  }
}

void ui::options::settings_and_utils() {
  utils::clear_screen();
  using namespace std;
  int c;
  cout << setw(80) << "Settings and Utilities\n\n\n";
  cout << setw(84) << "1. Change Administrator Password\n";
  cout << setw(84) << "2. Change Administrator Username\n";
  cout << setw(78) << "3. Reset and delete config\n";
  cout << setw(75) << "4. Reset all datafiles\n\n";
  cout << setw(78) << "5. -------   Back  -------\n";

  cout << endl << endl << "Press respective keys to perform ops : ";
  cin >> c;

  if (c == 1) {
    utils::change_password();
  } else if (c == 2) {
    utils::change_username();
  } else if (c == 3) {
    cout << "\n\nThe application will terminate  after this operation. Still Continue (yes/no) : ";
    string c2;
    cin >> c2;
    if (c2 == "yes") {
      utils::restore_and_delete_config();
      utils::_exit();
    } else {
      utils::start_menu_run();
    }

  } else if (c == 4) {

    cout
        << "\n\nThe application will terminate after this operation and all Data will be lost. Still Continue (yes/no) : ";
    string c2;
    cin >> c2;
    if (c2 == "yes") {
#ifdef __WIN32
      std::system((std::string("del ") + std::string(ACTIVE_ORDERS_NAME)).c_str());
      std::system((std::string("del ") + std::string(PAST_ORDERS_NAME)).c_str());
      std::system((std::string("del ") + std::string(ACTIVE_ORDERS_NAME)).c_str());

#else
      std::system((std::string("rm -rf ") + std::string(ACTIVE_ORDERS_NAME)).c_str());
      std::system((std::string("rm -rf ") + std::string(PAST_ORDERS_NAME)).c_str());
      std::system((std::string("rm -rf ") + std::string(ACTIVE_ORDERS_NAME)).c_str());

#endif
      utils::_exit();
    } else {
      utils::start_menu_run();
    }

  } else if (c == 5) {
    utils::start_menu_run();
  } else {
    cerr << "Falling back to old settings. Invalid Key Press";
    utils::start_menu_run();
  }

}
void ui::options::take_order() {

}
void ui::options::modify_order() {

}
void ui::options::show_all() {

}
