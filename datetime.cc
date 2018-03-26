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

#include "datetime.h"
#include <iomanip> //for put_time
#include <sstream>
#include <iostream>
#include <cstring>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
using namespace date;

date_time::date_time() : month(1), year(1970), date(1) {
  minute = 0;
  second = 0;
  hour = 0;
  strcpy(str_time, "01-01-1970 00:00:00");
  create_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch()).count();
}

date_time::date_time(int) {
  auto t = std::time(nullptr);
  std::ostringstream oss;
  oss << std::put_time(localtime(&t), "%d-%m-%Y %H:%M:%S");
  std::string str(oss.str());
  strcpy(str_time, str.c_str());
  date = static_cast<int>(std::stoll(str.substr(0, 2)));
  month = static_cast<int>(std::stoll(str.substr(3, 2)));
  year = static_cast<int>(std::stoll(str.substr(6, 4)));

  hour = static_cast<int>(std::stoll(str.substr(11, 2)));
  minute = static_cast<int>(std::stoll(str.substr(14, 2)));
  second = static_cast<int>(std::stoll(str.substr(17, 2)));

}

std::string date::date_time::get_timestamp() {
  std::string s;
  s += "[ ";
  s += std::string(str_time).substr(11);
  s += " ]";
  return s;
}

std::string date::date_time::get_date_timestamp() {
  std::string s;
  s += "[ ";
  s += str_time;
  s += " ]";
  return s;
}

long long date::date_time::get_milisecond_since_epoch() {
  long long time;
  using namespace std::chrono;
  time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  return time;
}

int date::date_time::get_date() const {
  return this->date;
}

int date::date_time::get_sec() const {
  return this->second;
}

int date::date_time::get_min() const {
  return this->minute;
}

int date::date_time::get_hour() const {
  return this->hour;
}

int date::date_time::get_month() const {
  return this->month;
}

int date::date_time::get_year() const {
  return this->year;
}

void date::date_time::set_date(int date, int month, int year) {
  this->date = date;
  this->month = month;
  this->year = year;
}

void date::date_time::set_time(int hour, int min, int sec) {
  this->hour = hour;
  this->minute = min;
  this->second = sec;
}

void date::date_time::set_str_time(char *k) {
  strcpy(this->str_time, k);
}
#pragma clang diagnostic pop