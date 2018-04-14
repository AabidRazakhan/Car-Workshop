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
#include <thread>
#include "utils.h"
#include "../file_helper/writer.h"
#include "../file_helper/reader.h"
#include "../file_helper/writer.cc"
#include "../file_helper/reader.cc"
#include "../base/order.h"
#include "../base/bad_input.h"

using namespace helper;

data_register data_register::get_data_register_instance() {
  try {
    std::unique_ptr<reader<financial::order>> reader1(new reader<financial::order>(ALL_ORDERS_NAME, true));
    std::unique_ptr<reader<financial::order>> reader2(new reader<financial::order>(ACTIVE_ORDERS_NAME, true));
    std::vector<financial::order> vector, vector1;
    reader1->read_all(vector);
    reader2->read_all(vector1);
    data_register dataRegister;
    dataRegister.total_completed = static_cast<int>(vector1.size() / 2);
    dataRegister.total_order = static_cast<int>(vector.size() / 2);
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
void utils::show_from_vector(const std::vector<financial::order> &vector) {
  using namespace std;
  if (vector.empty()) {
    cout << "No Data Found.. Redirecting to Main Menu in 2 sec";
    this_thread::sleep_for(chrono::seconds(2));
    utils::start_menu_run();
  } else {
    utils::clear_screen();
    cout << "Hint : Press any key to view next item or 0 to leave";
    int key = 1; //some dummy init
    int index = 0;
    while (key != 0 && index < vector.size()) {
      clear_screen();
      financial::order r = vector[index];
      index +=
          2; //fixme(coder3101) Some BUG is causing vector to include each object twice: Not my issue maybe inheritance is causing this or too large size of order
      r.generate_receipt();
      cin >> key;
    }
    utils::start_menu_run();
  }

}

void utils::modify_present_and_save(std::vector<financial::order> &vector, int t) {
  using namespace std;
  cout << "\nWhat do you want to modify in the entry ?";
  cout << "\n1. Order Status \t\t\t\t 2. Back";
  cout << "\n\nSelect the appropriate entry : ";
  int t2;
  cin >> t2;
  if (t2 > 2 || t2 < 1) {
    cerr << "Invalid Input : Nothing will be changed...Redirecting to main menu\n";
    this_thread::sleep_for(chrono::seconds(3));
    utils::start_menu_run();
  } else {

#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"
    switch (t2) {
      case 1: {
        cout << "\nAre you sure to mark the order as completed (yes/no) : ";
        std::string ch;
        cin >> ch;
        if (ch == "yes") {
          vector[t].is_completed = true;
          vector[t + 1].is_completed = true;
          std::vector<financial::order> older;
          try {
            file::reader<financial::order> *old = new file::reader<financial::order>(PAST_ORDERS_NAME, true);
            old->read_all(older);
            delete old;
          } catch (...) {}
          file::writer<financial::order> *past = new file::writer<financial::order>(PAST_ORDERS_NAME, true);
          older.push_back(vector[t]);
          vector.erase(vector.begin() + t);
          vector.erase(vector.begin() + t + 1);
          file::writer<financial::order> *active = new file::writer<financial::order>(ACTIVE_ORDERS_NAME, true);
          file::writer<financial::order> *all = new file::writer<financial::order>(ALL_ORDERS_NAME, true);
          std::vector<financial::order> temp;
          temp.reserve(older.size() + vector.size());
          temp.insert(temp.end(), vector.begin(), vector.end());
          temp.insert(temp.end(), older.begin(), older.end());
          past->write_all(older);
          all->write_all(temp);
          active->write_all(vector);

          delete past;
          delete all;
          delete active;

          cout << "\nOrder status changed.. Redirecting to main menu";
          std::this_thread::sleep_for(chrono::seconds(3));
          utils::start_menu_run();
          break;

        } else {
          cout << "\n\nAborting change status... Redirecting to main menu";
          this_thread::sleep_for(chrono::seconds(3));
          utils::start_menu_run();
          break;
          //fixme(coder3101) : It will be good to fix {this} issue but i wont fix this time
          //{this} : Moving order from active to past does  not removes order from active at
        }
      }
      case 2: {
        utils::start_menu_run();
        break;
      }
    }
#pragma clang diagnostic pop

  }

}

void ui::show_main_menu(config c) {
  utils::clear_screen();
  c.admin_name[0] = static_cast<char>(toupper(c.admin_name[0]));

  data_register aRegister = data_register::get_data_register_instance();
  std::string s, s2;

  s = std::to_string(aRegister.total_completed);
  s2 = std::to_string(aRegister.total_order);
  using namespace std;
  cout << setw(60) << "Welcome " << c.admin_name << endl << endl << endl;
  cout << setw(50) << "Last Login at : " << c.last_launch.get_date_timestamp() << " by " << c.admin_name << endl << endl
       << endl;
  cout << setw(68) << "Active Orders : " << s << endl;
  cout << setw(68) << "Total Orders  : " << s2 << endl << endl << endl;
  cout << setw(70) << "1. Take a new Order" << endl;
  cout << setw(70) << "2. Modify the Order" << endl;
  cout << setw(70) << "3. Show  all  Order" << endl;
  cout << setw(70) << "4. Order  to  Look " << endl;
  cout << setw(70) << "5. Settings & Utils" << endl;
  cout << setw(70) << "6. Save  and   Exit" << endl;
  cout << endl << endl << "Press respective keys to perform ops : ";
  size_t x = 0;
  while (!x) {
    cin >> x;
    if (x > 6) {
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
    case 4 :
      try { ui::options::look_order(); } catch (std::runtime_error &e) {
        std::cerr << "\nYou must take some order before looking for them. Redirecting to main menu..";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        utils::start_menu_run();
      }
      break;
    case 5 : ui::options::settings_and_utils();
      break;
    case 6 : utils::_exit();
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
      std::system("rm -rf *.db");

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
  utils::clear_screen();
  try {
    financial::order new_order = financial::order::create_new_order();
    std::cout << "Are you sure you want to add this order : ";
    std::string s;
    std::cin >> s;
    if (s == "yes") {

      std::vector<financial::order> all_active, all_order;
      try {
        file::reader<financial::order> *reader1 = new file::reader<financial::order>(ACTIVE_ORDERS_NAME, true);
        file::reader<financial::order> *reader2 = new file::reader<financial::order>(ALL_ORDERS_NAME, true);

        reader1->read_all(all_active);
        reader2->read_all(all_order);

        delete reader1;
        delete reader2;

      } catch (std::runtime_error &e) {
        //ignore it simple means this is first install
      }

      all_active.push_back(new_order);
      all_order.push_back(new_order);

      file::writer<financial::order> *writer1 = new file::writer<financial::order>(ACTIVE_ORDERS_NAME, true);
      file::writer<financial::order> *writer2 = new file::writer<financial::order>(ALL_ORDERS_NAME, true);

      writer1->write_all(all_active);
      writer2->write_all(all_order);

      delete writer1;
      delete writer2;

      std::cout << "\n\nThe Order was saved and will be visible soon...";

      //Equivalent for delay from dos.h
      std::this_thread::sleep_for(std::chrono::seconds(2));
      utils::start_menu_run();

    } else {
      utils::start_menu_run();
    }
  } catch (error::bad_input &e) {
    std::cerr << "Invalid input : Reason --> " << e.what();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    utils::start_menu_run();
  }

}
void ui::options::modify_order() {
  utils::clear_screen();
  using namespace std;
  string target;
  cout << setw(50) << "Enter the Car Number to look for : ";
  cin >> target;
  file::reader<financial::order> *ptr = new file::reader<financial::order>(ACTIVE_ORDERS_NAME, true);
  vector<financial::order> vector1;
  ptr->read_all(vector1);
  delete ptr;
  bool found = false;
  for (int t = 0; t < vector1.size(); t++) { //returns first occupancy of target, next is also a target
    if (target == vector1[t].get_problem_map().get_number()) {
      found = true;
      utils::modify_present_and_save(vector1, t);
      break;
    }
  }
  if (!found) {
    cerr << "No such car is in the workshop. Car Number looked for : " << target << "\nRedirecting to main menu in 3s";
    this_thread::sleep_for(chrono::seconds(3));
    utils::start_menu_run();
  }

}
void ui::options::show_all() {
  utils::clear_screen();
  using namespace std;
  cout << setw(72) << "Showing All Orders\n\n";
  cout << setw(70)
       << "Choose view type : \n\t\t\t\t1. View only Completed orders \n\t\t\t\t2. View all the orders \n\t\t\t\t3. Back";
  cout << "\nYour choice : ";
  int s;
  cin >> s;
  if (s > 3 || s < 0) {
    cout << "\n\nA bad value provided\n\n\n";
    this_thread::sleep_for(chrono::seconds(1));
    utils::start_menu_run();
  } else {
    if (s == 3) utils::start_menu_run();
    if (s == 2) {
      try {
        std::vector<financial::order> orders;
        file::reader<financial::order> *reader1 = new file::reader<financial::order>(ALL_ORDERS_NAME, true);
        reader1->read_all(orders);
        delete reader1;
        utils::show_from_vector(orders);

      } catch (std::runtime_error &ignore) {
        cerr
            << "\n\nEither Database file is missing or no order was created (for total order)... Moving to Main Menu\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        utils::start_menu_run();
      };
    }
    if (s == 1) {
      try {
        std::vector<financial::order> orders;
        file::reader<financial::order> *reader1 = new file::reader<financial::order>(PAST_ORDERS_NAME, true);
        reader1->read_all(orders);
        delete reader1;
        utils::show_from_vector(orders);
      } catch (std::runtime_error &w) {
        cerr
            << "\n\nEither Database file is missing or no order has been completed till this date (for past order)... Moving to Main Menu\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        utils::start_menu_run();
      }
    }
  }
}
void ui::options::look_order() {
  utils::clear_screen();
  using namespace std;
  string target;
  cout << setw(50) << "Enter the Car Number to look for : ";
  cin >> target;
  file::reader<financial::order> *ptr = new file::reader<financial::order>(ACTIVE_ORDERS_NAME, true);
  vector<financial::order> vector1;
  ptr->read_all(vector1);
  delete ptr;
  bool found = false;
  for (financial::order &r : vector1) {
    if (target == r.get_problem_map().get_number()) {
      found = true;
      cout << endl;
      r.generate_receipt();
      cout << "\n\nEnter Any Key to go back to last menu.";
      break;
    }
  }
  if (!found) {
    cerr << "No such car is in the workshop. Car Number looked for : " << target << "\nRedirecting to main menu in 3s";
    this_thread::sleep_for(chrono::seconds(3));
    utils::start_menu_run();
  } else {
    int s;
    cin >> s; //dummy entry get in not here.
    cin.clear(); //just reset the buffer state to original just in case user entered something else apart from int.
    utils::start_menu_run();
  }

}
