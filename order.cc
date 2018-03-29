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
#include "order.h"
#include "writer.h"
#include "writer.cc" //for Linker to fix

using namespace financial;

#pragma clang diagonistic pop

problem::problem_map order::get_problem_map() const {
  return this->p_map;
}
order order::create_new_order() {
  order new_order;
  new_order.order_time = date::date_time(0); //current_time
  //todo Here a UI helper will be called to create a new screen with details for new order
  return new_order;

}
void order::generate_receipt() {
  //todo Here you need to call a UI helper for decorating the screen
  p_map.describe();

}
void order::finalize_and_complete_order() {
  //todo Prompt for saving order yes/no
  save_order();

}
void order::save_order() {
  file::writer<order> writer1(ALL_ORDERS_NAME,true);
  file::writer<order> writer2(ACTIVE_ORDERS_NAME, true);
  writer1.write(*this);
  writer2.write(*this);
  //todo UI helper to show a order success save
}

