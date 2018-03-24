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

#pragma once
#include <chrono>
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
namespace date {
class date_time {
  int month:6, year, date:6;
  int hour:6, second:8, minute:8;
  long long create_time;
  char str_time[21];
 public:
  date_time();
  date_time(std::string s) {}; // NOLINT
  //This constructor is required to restore data back from file using reader class
  explicit date_time(int); //just don't create automatically. Safety check
  std::string get_timestamp();
  std::string get_date_timestamp();

  static long long get_milisecond_since_epoch();

  int get_date() const;
  int get_sec() const;
  int get_min() const;
  int get_hour() const;
  int get_month() const;
  int get_year() const;

  void set_date(int date, int month, int year);
  void set_time(int hour, int min, int sec);
  void set_str_time(char *n);
};
}
#pragma clang diagnostic pop