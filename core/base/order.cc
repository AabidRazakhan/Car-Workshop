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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#include <iomanip>
#include <cassert>
#include <iostream>
#include <cstring>
#include "order.h"
#include "bad_input.h"

using namespace financial;

#pragma clang diagonistic pop

problem::problem_map order::get_problem_map() const {
  return this->p_map;
}
order order::create_new_order() {
  //fixme(coder3101) : Name is including half name and same with problem name
  order new_order;
  using namespace std;
  string temp;
  int temp_int;
  cout << setw(80) << "Step 1 : Customer Detail\n";
  cout << "\n1. Customer Name : ";
  cin.ignore();
  getline(cin, temp);
  strcpy(new_order.customer_name, temp.c_str());
  if (temp.empty()) throw error::bad_input("Name must not be empty");
  cout << "\n2. Remark (if any) : ";
  cin.ignore();
  getline(cin, temp);
  strcpy(new_order.remark, temp.c_str());

  cout << "\n\n" << setw(80) << "Step 2 : Vehicle  Detail\n";
  problem::problem_map new_map;

  cout << "\n1. Age of Vehicle (in years) : ";
  cin >> temp_int;
  if (temp_int > -1 && temp_int < 100)
    new_map.set_age(temp_int);
  else throw error::bad_input("Age should be in range 0-100");

  cout << "\n2. Registration Number of Vehicle : ";
  cin >> temp;
  new_map.set_number(temp);
  if (temp.empty()) throw error::bad_input("Registration number is a required field");

  cout << "\n3. Model Number of Vehicle : ";
  cin >> temp;
  new_map.set_model_number(temp);
  if (temp.empty()) throw error::bad_input("Model number is a required field");

  cout << "\n4. Manufacturer Name : ";
  cin >> temp;
  new_map.set_manufacturer_name(temp);
  if (temp.empty()) throw error::bad_input("Manufacturer Name is a required field");

  cout << "\n5. Color of Vehicle : ";
  cout
      << "\n1.   Red   \t\t\t2.  Green   \n3. Silver  \t\t\t4.  Yellow  \n5.  Black  \t\t\t6.  White  \n7.  Grey   \t\t\t8.  Purple  \n9.  Maroon  \t\t\t10.  Blue  ";
  cout << "\nSelect appropriate index : ";

  cin >> temp_int;
  if (temp_int > 0 && temp_int < 11)
    new_map.set_colour(static_cast<vehicle::color>(temp_int - 1));
  else throw error::bad_input("Color index is out of range");
  cout << setw(80) << "Step 3 : Problem Details\n";
  cout << "\nNumber of Problems : ";
  int size = 0;
  cin >> size;
  if (size > 0 && size < 50)
    new_map.problem_count = size;
  else throw error::bad_input("Problem size must be in range 0-50");
  for (int t = 0; t < size; t++) {
    cout << "Problem " << t + 1 << " is : ";
    cin.ignore();
    getline(cin, temp);
    cout << "Expected Cost for Problem " << t + 1 << " : ";
    cin >> temp_int;
    if (temp_int >= 0)
      new_map.costINR[t] = temp_int;
    else throw error::bad_input("Cost must be a positive value");
    strcpy(new_map.problems[t], temp.c_str());
  }
  new_order.p_map = new_map;
  new_order.apply_cost();
  //todo(coder3101) : vehicle::type may be used.. Skipping for now
  //todo(coder3101) : Due date is Skipping for now
  return new_order;

}
void order::generate_receipt() {
  using namespace std;
  cout << "\n\n" << setw(110) << "================================================================================\n\n";
  cout.width(50);
  cout << std::right << "Customer Name : " << customer_name;
  cout.width(30);
  cout << std::right << " Remark : " << this->remark << endl;
  cout.width(50);
  string status = "Work in Progress";
  if (this->is_completed)
    status = "Completed";
  cout << std::right << "Date of Order : " << this->order_time.get_date() << "-" << this->order_time.get_month()
       << "-" << this->order_time.get_year();
  cout.width(30);
  cout << std::right << "Order Status : " << status << endl;
  cout.width(50);
  cout << std::right << "Vehicle Number : " << this->p_map.get_number();
  cout.width(40);
  cout << std::right << "Manufacturer Name : "
       << this->p_map.get_manufacturer_name() << endl;
  cout.width(50);
  cout << std::right << "Model Number : " << this->p_map.get_model_number();
  cout.width(30);
  cout << std::right << "Color : "
       << parse_color(this->p_map.get_colour());
  this->p_map.describe();
  cout << endl;
  apply_cost();
  cout << "\n\n" << setw(75) << "------------------- GRAND TOTAL : " << this->chargeINR
       << " ------------------------\n\n\n";

}
void order::apply_cost() {
  this->chargeINR = 0;
  for (int i = 0; i < p_map.problem_count; ++i)
    chargeINR += p_map.costINR[i];
}
std::string order::parse_color(int i) {
  assert(i >= 0);
  switch (i) {
    case vehicle::color::red : return "Red";
    case vehicle::color::green : return "Green";
    case vehicle::color::silver : return "Silver";
    case vehicle::color::yellow : return "Yellow";
    case vehicle::color::black : return "Black";
    case vehicle::color::white : return "White";
    case vehicle::color::grey : return "Grey";
    case vehicle::color::purple : return "Purple";
    case vehicle::color::maroon : return "Maroon";

    default: throw std::runtime_error("Color parse got unexpected index");
  }
}
