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

#ifndef CAR_WORKSHOP_VEHICLE_H
#define CAR_WORKSHOP_VEHICLE_H

#include <string>
namespace vehicle {

enum color {
  red,
  green,
  silver,
  yellow,
  black,
  white,
  grey,
  purple,
  maroon,
  blue,
};

struct type {
  const char *mini = "MINI";
  const char *sedan = "SEDAN";
  const char *suv = "SUV";
  const char *family = "FAMILY CLASS";
  const char *sports = "SPORTS";
};

typedef char compat_string[1000];
class vehicle { // NOLINT

 protected:
  int age;
  compat_string number;
  compat_string manufacturer_name;
  compat_string model_number;
  color colour;

 public:
  vehicle() = default;
  explicit vehicle(int a);
  vehicle(char *number, char*model, char*manufacturer,int age, color c);
  vehicle(color c); // NOLINT
  int get_age() const;
  const char *get_number() const;
  const char *get_manufacturer_name() const;
  const char *get_model_number() const;
  color get_colour() const;

  void set_age(int);
  void set_number(std::string);
  void set_number(compat_string);
  void set_manufacturer_name(std::string);
  void set_manufacturer_name(compat_string);
  void set_model_number(std::string);
  void set_model_number(compat_string);
  void set_colour(color);

  virtual void describe() const = 0;
  //Describes the vehicle, must be overridden by derived classes setting it a pure virtual function

  virtual ~vehicle();
};
}

#endif //CAR_WORKSHOP_VEHICLE_H

#pragma clang diagnostic pop