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
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#include "vehicle.h"
namespace problem {
class problem_map : public vehicle::vehicle {
  void __delete_entry(int t);
 public:
  char problems[50][500];
  int costINR[50];
  char type[20];
  int problem_count = 0;

  explicit problem_map(const char* t) = default;

  bool assign_problem(const char *d, int cost);

  void undo_last_problem();

  bool remove_problem_named(const char* d);

  void describe() override;
};
}
#pragma clang diagonistic pop