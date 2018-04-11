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
#include "order.h"
#include "../file_helper/writer.h"
#include "../file_helper/writer.cc" //for Linker to fix

using namespace financial;

#pragma clang diagonistic pop

problem::problem_map order::get_problem_map() const {
  return this->p_map;
}
order order::create_new_order() {
  order new_order;
  using namespace std;
  string temp;
  int temp_int;
  cout << setw(80) << "Step 1 : Customer Detail\n";
  cout << "\n1. Customer Name : ";
  cin.clear();
  cin.ignore('\n');
  getline(cin, temp);
  cin.clear();
  strcpy(new_order.customer_name, temp.c_str());
  cout << "\n2. Remark (if any) : ";
  getline(cin, temp);
  strcpy(new_order.remark, temp.c_str());

  cout << "\n\n" << setw(80) << "Step 2 : Vehicle  Detail\n";
  problem::problem_map new_map;

  cout << "\n1. Age of Vehicle (in years) : ";
  cin >> temp_int;
  assert(temp_int > -1 && temp_int < 100);
  //assert will call std::abort if user enters no integer
  new_map.set_age(temp_int);

  cout << "\n2. Registration Number of Vehicle : ";
  cin >> temp;
  new_map.set_number(temp);

  cout << "\n3. Model Number of Vehicle : ";
  cin >> temp;
  new_map.set_model_number(temp);

  cout << "\n4. Manufacturer Name : ";
  cin >> temp;
  new_map.set_manufacturer_name(temp);

  cout << "\n5. Color of Vehicle : ";
  cout
      << "\n1.   Red   \t\t\t2.  Green   \n3. Silver  \t\t\t4.  Yellow  \n5.  Black  \t\t\t6.  White  \n7.  Grey   \t\t\t8.  Purple  \n9.  Maroon  \t\t\t10.  Blue  ";
  cout<<"\nSelect appropriate index : ";

  cin >> temp_int;
  assert(temp_int > 0 && temp_int < 11);
  new_map.set_colour(static_cast<vehicle::color>(temp_int - 1));

  cout << setw(80) << "Step 3 : Problem Details\n";
  cout << "\nNumber of Problems : ";
  int size = 0;
  cin >> size;
  assert(size > 0 && size < 50);
  new_map.problem_count = size;
  for (int t = 0; t < size; t++) {
    cout << "Problem " << t + 1 << " is : ";
    cin.clear();
    cin.ignore('\n');
    getline(cin, temp);
    cin.clear();
    cout << "Expected Cost for Problem " << t + 1 << " : ";
    cin >> temp_int;
    assert(temp_int >= 0);
    new_map.costINR[t] = temp_int;
    strcpy(new_map.problems[t], temp.c_str());
  }
  new_order.p_map = new_map;
  new_order.apply_cost();
  //todo(coder3101) : vehicle::type may be used.. Skipping for now
  //todo(coder3101) : Due date is Skipping for now
  return new_order;

}
void order::generate_receipt() {
  //todo(coder3101) Here you need to call a UI helper for decorating the screen
  p_map.describe();

}
void order::apply_cost() {
  this->chargeINR = 0;
  for (int i = 0; i < p_map.problem_count; ++i)
    chargeINR += p_map.costINR[i];
}
