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
 * [PASSED ALL READ TEST ON STRINGS ON : 23 MARCH, 2018 : 2:00 AM]
 * [PASSED ALL READ TEST ON VALID GENERIC CLASSES ON : 23 MARCH, 2018 : 3:00 AM]
 */

/**********************************LIMITATIONS*******************************************/
//	As of now all the classes calling this API must fulfil following
//conditions.

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
 *	4. IF A WRITER HAS NOT CLOSED A CONNECTION TO THE FILE, THEN A READER
 *ATTEMPTING TO WRITE TO THAT FILE WILL FAIL.
 *	MAKE SURE TO CALL READERS AND WRITERS IN A SEPARATE SCOPE IF THEY BOTH
 *WORK WITH SAME FILE.
 *	OR USE DYNAMIC MEMORY ALLOCATION AND DELETE WRITER AND READERS AS SOON
 *AS YOU ARE DONE WITH THEM.
 *	CALL TO DESTRUCTOR WILL RELEASE THE STREAM LOCK TO THE FILE (CLOSE THE
 *CONNECTION TO FILE).
 *
 *	5. MAKE SURE THAT CLASS YOU ARE WRITING VIA THESE HELPERS MUST
 *	HAVE A NON EXPLICIT PARAMETERIZED CONSTRUCTOR WITH <std::string> AS THE
 *ONLY ARG
 */
#pragma once
#include <cstring>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

namespace file {
template <class T>
class reader {
  std::ifstream st;
  bool isbinary;
  std::string file_name;
  void initiate() {
    if (isbinary)
      st.open(file_name, std::ios::in | std::ios::binary);
    else
      st.open(file_name, std::ios::in);
    if (st.fail()) {
      char message[180];
      strcpy(message, std::strerror(errno));
      throw std::runtime_error(message);
    }
  }

 public:
  reader() = delete;
  explicit reader(std::string file_name, bool bin = false) {
    this->file_name = file_name;
    this->isbinary = bin;
    initiate();
  }

  long long tell() { return this->st.tellg(); }
  void seek_to(int pos, std::ios::seekdir type) {
    if (isbinary) {
      this->st.seekg((pos - 1) * sizeof(T), type);
    } else
      this->st.seekg(pos, type);
  }
  T read() {
    if (isbinary) {
      T res;
      st.read(reinterpret_cast<char *>(&res), sizeof(T));
      return res;
    } else {
      auto *r = new char[800];
      st.getline(r, 800, '\n');
      std::string c(r);
      delete r;
      return T(c);
    }
  }
  T read(int pos) {
    if (isbinary) {
      long long prev_point = st.tellg();
      st.seekg((pos - 1) * sizeof(T), std::ios::beg);
      T res;
      st.read(reinterpret_cast<char *>(&res), sizeof(T));
      st.seekg(prev_point, std::ios::beg);
      return res;
    } else {
      long prev_point = st.tellg();
      st.seekg(pos, std::ios::beg);

      auto *res = new char[800];
      st.getline(res, 800, '\n');
      std::string v(res);
      delete res;
      st.seekg(prev_point, std::ios::beg);
      return (T)v;
    }
  }
  void read_all(std::vector<T> &out) {
    long prev = st.tellg();
    if (isbinary) {
      st.seekg(0, std::ios::beg);
      T o;
      while (!st.eof()) {
        st.read(reinterpret_cast<char *>(&o), sizeof(T));
        out.push_back(o);
      }
      st.seekg(prev, std::ios::beg);
    } else {
      st.seekg(0, std::ios::beg);
      std::string res;
      auto *buff = new char[800];
      while (!st.eof()) {
        st.getline(buff, 800, '\n');
        std::string s(buff);
        out.push_back((T)s);
      }
      delete buff;
    }
  }
  ~reader() {
    if (this->st.is_open()) {
      this->st.close();
    }
  }
};
}
#pragma clang diagnostic pop