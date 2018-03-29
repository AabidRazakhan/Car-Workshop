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
#include "problem_map.h"
using namespace problem;

void problem_map::describe() {
//todo(implement the UI to Show the Problems and Vehicle Details
  //This will be called in the order.cc
}
bool problem_map::assign_problem(const char *d, int cost) {
  if (problem_count > 49)
    return false;
  else {
    strcpy(problems[problem_count], d);
    costINR[problem_count] = cost;
    problem_count++;
    return true;
  }
}
void problem_map::undo_last_problem() {
  --problem_count;
}
bool problem_map::remove_problem_named(const char *d) {
  bool found = false;
  for(int t=0;t<problem_count;t++){
    if(strcmp(d,problems[t]) == 0){
      __delete_entry(t);
      found = true;
      break;
    }
  }
  return found;

}
problem_map::problem_map(const char *t) {
  strcpy(type,t);
}
void problem_map::__delete_entry(int t) {
  strcpy(problems[t],problems[problem_count-1]);
  costINR[t] = costINR[problem_count-1];
  problem_count--;
}
