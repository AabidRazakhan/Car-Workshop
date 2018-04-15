/*
*   Copyright (c) Ashar Khan 2018. <ashar786khan@gmail.com>
*    This file is part of CSE202 Car Workshop Project.
*   Car Workshop is free software : you can redistribute it and/or modify
*    it under the terms of GNU General Public License as published by the Free
* Software Foundation,
*   either version 3 of the License, or (at your option) any later version.
*
*   This Application is distributed in the hope that it will be useful
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY
*   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  Public License for
* more details.
*
*   You should have received a copy of the GNU General Public License along with
* this Source File.
*   If not, see <http:www.gnu.org/licenses/>.
*/

/*
 * [PASSED ALL WRITE TEST ON STRINGS ON : 23 MARCH, 2018 : 2:00 AM]
 * [PASSED ALL WRITE TEST ON VALID GENERIC CLASSES ON : 23 MARCH, 2018 : 3:00
 * AM]
 */

/**********************************LIMITATIONS*******************************************/
//	As of now all the classes calling this API must fulfil following
// conditions.

/*	1. NOTE : BECAUSE THIS IMPLEMENTS TEMPLATES
 *	ALL THE FILES INCLUDING READER.H MUST INCLUDE
 *	READER.CPP IN ORDER TO AVOID LINKER ERROR.
 *
 *	2. READING TO CLASS CONTAINING DYNAMIC DATA MEMBERS. MUST NOT EXIST.
 *	For example : std::string ==> const char * , std::vector<?> ==> []. they
 *just cause sizeof(T) to fail.
 *
 *	3. TO READ SIMPLE STRINGS, PASS <std::string> AS GENERIC TYPE INDICATOR.
 *
 *	4. IF A READER HAS NOT CLOSED A CONNECTION TO THE FILE, THEN A WRITER
 *ATTEMPTING TO WRITE TO THAT FILE WILL FAIL.
 *	MAKE SURE TO CALL READERS AND WRITERS IN A SEPARATE SCOPE IF THEY BOTH
 *WORK WITH SAME FILE.
 *	OR USE DYNAMIC MEMORY ALLOCATION AND DELETE WRITER AND READERS AS SOON
 *AS YOU ARE DONE WITH THEM.
 *	CALL TO DESTRUCTOR WILL RELEASE THE STREAM LOCK TO THE FILE (CLOSE THE
 *CONNECTION TO FILE).
 *
 *  5. MAKE SURE THAT CLASS YOU ARE WRITING VIA THESE HELPERS MUST
 *	HAVE A NON EXPLICIT PARAMETERIZED CONSTRUCTOR WITH <std::string> AS THE
 *ONLY ARG
 */

#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
namespace file {

enum re_write_mode { no_create, append, attenuate };

template <class T>
class writer {
  std::ofstream w_stream;
  bool isbinary;
  std::string file_name;
  void initiate() {
    if (isbinary)
      w_stream.open(file_name, std::ios::out | std::ios::binary);
    else
      w_stream.open(file_name, std::ios::out);
    if (w_stream.fail()) {
      char message[180];
      strcpy(message, std::strerror(errno));
      throw std::runtime_error(message);
    }
  }
  void initiate(re_write_mode mode) {
    if (file_exist_check_fail()) {
      throw std::runtime_error("Failed to write to a file that does not exist");
    } else {
      if (isbinary) {
        if (mode == append)
          w_stream.open(file_name, std::ios::app | std::ios::binary);
        else
          w_stream.open(file_name, std::ios::ate | std::ios::binary);
      } else {
        if (mode == append)
          w_stream.open(file_name, std::ios::app);
        else
          w_stream.open(file_name, std::ios::ate);
      }
    }
  }
  bool file_exist_check_fail() {
    const char *name = file_name.c_str();
    std::ifstream test(name, std::ios::in);
    if (test.fail())
      return true;
    else {
      test.clear();
      return false;
    }
  }

 public:
  writer() = delete;
  explicit writer(std::string file_name, re_write_mode mode, bool bin = false) {
    this->isbinary = bin;
    this->file_name = file_name;
    initiate(mode);
  }  // writes to existing file in any mode
  explicit writer(std::string file_name, bool bin = false) {
    this->isbinary = bin;
    this->file_name = file_name;
    initiate();
  }  // creates a new file always and clear and rewrites its contents
  long long tell() { return this->w_stream.tellp(); }
  void write(T &obj, bool move_next_line = false) {
    if (isbinary) {
      w_stream.write(reinterpret_cast<char *>(&obj), sizeof(T));
    } else {
      std::string elt = reinterpret_cast<std::string &>(obj);
      for (char a : elt) w_stream.put(a);
      if (move_next_line) w_stream.put('\n');
    }
  }
  void replace_write(T &obj, int pos) {
    long long prev_pointer = w_stream.tellp();
    if (isbinary) {
      seek_to((pos - 1) * sizeof(T), std::ios::beg);
      w_stream.write(reinterpret_cast<char *>(&obj), sizeof(T));
      w_stream.seekp(prev_pointer, std::ios::beg);
    } else {
      std::string elt = reinterpret_cast<std::string &>(obj);
      seek_to(pos, std::ios::beg);
      for (char a : elt) w_stream.put(a);
      w_stream.seekp(prev_pointer, std::ios::beg);
    }
  }
  void seek_to(int off, std::ios::seekdir type) {
    if (isbinary) {
      int nop = (off - 1) * sizeof(T);
      this->w_stream.seekp(nop, type);
    } else
      this->w_stream.seekp(off, type);
  }
  void write_all(std::vector<T> &ref, bool newline = false) {
    if (isbinary) {
      for (T &elt : ref)
        w_stream.write(reinterpret_cast<char *>(&elt), sizeof(T));
    } else {
      for (T elt : ref) {
        std::string e = reinterpret_cast<std::string &>(elt);
        for (char a : e) w_stream.put(a);
        if (newline) w_stream.put('\n');
      }
    }
  }
  ~writer() {
    if (w_stream.is_open()) {
      w_stream.close();
    }
  }
};
}
#pragma clang diagnostic pop
