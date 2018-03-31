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
#include "utils.h"
#include "writer.h"
#include "reader.h"
#include "writer.cc"
#include "reader.cc"

using namespace helper;

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
  std::cout << "It Looks like first run of the Program, We need to get you ready..." << std::endl;
  bool accepted = false;
  while (!accepted) {
    std::string pass;
    std::cout << "Enter a Fresh Password (min 5 characters long): " << std::endl;
    std::cin >> pass;
    if (pass.length() >= 5) {
      accepted = true;
      config config1(pass);
      config1.create_time = date::date_time(0);
      config1.last_launch = date::date_time(0);
      file::writer<config> *writer = new file::writer<config>(CONFIG_FILE_NAME, true);
      writer->write(config1);
      delete writer; //explicitly calls destructor to release mutex of owned file

    } else
      std::cout << "To short Password... Try Again" << std::endl;
  }
}
bool utils::validate_password(const std::string &s) {
  file::reader<config> reader1(CONFIG_FILE_NAME, true);
  return strcmp(reader1.read().password, s.c_str()) == 0;
}
bool utils::change_password() {
  clear_screen();
  file::reader<config> *reader1 = new file::reader<config>(CONFIG_FILE_NAME, true);
  config c = reader1->read();
  delete reader1;
  std::cout << "Enter the new Password : ";
  std::string new_pass;
  std::cin >> new_pass;
  if (new_pass.length() >= 5) {
    strcpy(c.password,new_pass.c_str());
    file::writer<config> *writer1 = new file::writer<config>(CONFIG_FILE_NAME,true);
    c.create_time = date::date_time(0);
    writer1->write(c);
    delete writer1;
  }
  else{
    std::cerr<<"Too Small Password, Falling back to previous password"<<std::endl;
  }
}
void utils::restore_and_delete_all() {
  //todo(coder3101) : Implement this
}
void utils::start_menu_run() {

  file::reader<config> *reader1 = new file::reader<config>(CONFIG_FILE_NAME, true);
  config c = reader1->read(1);
  delete reader1;

  file::writer<config> *writer1 = new file::writer<config>(CONFIG_FILE_NAME, true);
  c.last_launch = date::date_time(0);
  writer1->write(c);
  delete writer1;

  std::cout << "Started here..." << std::endl;
  //todo(coder3101) : Use the main menu here
}
void utils::clear_screen() {
#ifdef __WIN32
  std::system("cls")
#else
  std::system("clear");
#endif
}

