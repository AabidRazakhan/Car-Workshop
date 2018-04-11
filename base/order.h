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
#ifndef CAR_WORKSHOP_ORDER_H
#define CAR_WORKSHOP_ORDER_H
#include <stdexcept>
#include "../utility/datetime.h"
#include "vehicle.h"
#include "problem_map.h"

#define ALL_ORDERS_NAME "all.db"
#define PAST_ORDERS_NAME "past.db"
#define ACTIVE_ORDERS_NAME "active.db"

namespace financial {
class order { // NOLINT
  date::date_time order_time, due_date;
  problem::problem_map p_map;

  char remark[100];

  char customer_name[50];

 public:
  order(){ // NOLINT
    order_time = date::date_time(0);
  };

  bool is_completed = false;
  float chargeINR = 0; //perfectly allowed in Cxx11 and later


  order(std::string dummy) { // NOLINT
    throw std::runtime_error("Reader called String implementation. Make sure that you are opening in binary mode");
  } //Should never be called
  problem::problem_map get_problem_map() const;
  void generate_receipt();
  void apply_cost();
  static order create_new_order();
};
}
#pragma clang diagonistic pop
#endif //CAR_WORKSHOP_ORDER_H
