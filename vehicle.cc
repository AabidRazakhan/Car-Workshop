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
#include <cstring>
#include "vehicle.h"

using namespace vehicle;

int vehicle::vehicle::get_age() const {
  return this->age;
}
const char *vehicle::vehicle::get_number() const {
  return this->number;
}
const char *vehicle::vehicle::get_manufacturer_name() const {
  return this->manufacturer_name;
}
const char *vehicle::vehicle::get_model_number() const {
  return this->model_number;
}

vehicle::color vehicle::vehicle::get_colour() const {
  return this->colour;
}
void vehicle::vehicle::set_age(int a) {
  this->age = a;
}
void vehicle::vehicle::set_number(std::string n) {
  strcpy(this->number, n.c_str());

}
void vehicle::vehicle::set_number(char *s) {
  strcpy(this->number, s);
}
void vehicle::vehicle::set_manufacturer_name(std::string n) {
  strcpy(this->manufacturer_name, n.c_str());
}
void vehicle::vehicle::set_manufacturer_name(char *n) {
  strcpy(this->manufacturer_name, n);
}
void vehicle::vehicle::set_model_number(std::string n) {
  strcpy(this->model_number, n.c_str());
}
void vehicle::vehicle::set_model_number(char *n) {
  strcpy(this->model_number, n);
}

void vehicle::vehicle::set_colour(color c) {
  this->colour = c;
}

vehicle::vehicle::~vehicle() = default;

#pragma clang diagnostic pop

