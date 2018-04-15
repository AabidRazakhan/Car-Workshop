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

#ifndef CAR_WORKSHOP_BAD_INPUT_H
#define CAR_WORKSHOP_BAD_INPUT_H

#include <bits/exception.h>
#include <string>
#include <cstring>
namespace error {
class bad_input : public std::exception {
  char reason[100];
 public:
  explicit bad_input(const std::string &msg) { strcpy(const_cast<char *>(reason), msg.c_str()); } // NOLINT
  const char* what() const noexcept final { return reason; }
  ~bad_input() noexcept final{ // NOLINT
    //destructor should possibly not throw any exceptions
  }
};
}

#endif //CAR_WORKSHOP_BAD_INPUT_H
