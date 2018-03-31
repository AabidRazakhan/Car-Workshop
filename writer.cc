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
#include <cstring>
#include "writer.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
using namespace file;

template<class T>
writer<T>::writer(std::string file_name, bool bin) throw() {
  this->isbinary = bin;
  this->file_name = file_name;
  initiate();
}

template<class T>
long long writer<T>::tell() {
  return this->w_stream.tellp();
}

template<class T>
void file::writer<T>::write(T &obj, bool next_line) throw() {
  if (isbinary) {
    w_stream.write(reinterpret_cast<char *>(&obj), sizeof(T));
  } else {
    std::string elt = reinterpret_cast<std::string&>(obj);
    for (char a: elt)
      w_stream.put(a);
    if (next_line)
      w_stream.put('\n');
  }
}

template<class T>
void file::writer<T>::replace_write(T &obj, int pos) throw() {
  long long prev_pointer = w_stream.tellp();
  if (isbinary) {
    seek_to((pos-1)* sizeof(T), std::ios::beg);
    w_stream.write(reinterpret_cast<char *>(&obj), sizeof(T));
    w_stream.seekp(prev_pointer, std::ios::beg);
  } else {
    std::string elt = reinterpret_cast<std::string&>(obj);
    seek_to(pos, std::ios::beg);
    for (char a : elt)
      w_stream.put(a);
    w_stream.seekp(prev_pointer, std::ios::beg);
  }

}

template<class T>
void file::writer<T>::seek_to(int off, std::ios::seekdir type) throw() {
  if (isbinary) {
    int nop = (off - 1) * sizeof(T);
    this->w_stream.seekp(nop, type);
  } else this->w_stream.seekp(off, type);

}

template<class T>
void file::writer<T>::write_all(std::vector<T> &ref, bool newline) {
  if (isbinary) {
    for (T elt : ref)
      w_stream.write(reinterpret_cast<char *>(&elt), sizeof(T));
  } else {
    for (T elt:ref) {
      std::string e = reinterpret_cast<std::string&>(elt);
      for (char a:e)
        w_stream.put(a);
      if (newline)
        w_stream.put('\n');
    }
  }
}

template<class T>
writer<T>::~writer() {
  if (w_stream.is_open()) {
    w_stream.close();
  }
}

template<class T>
void writer<T>::initiate() throw() {
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
template<class T>
writer<T>::writer(std::string file_name, re_write_mode mode, bool bin) throw() {
  this->isbinary = bin;
  this->file_name = file_name;
  initiate(mode);
}

template<class T>
void writer<T>::initiate(re_write_mode mode) throw() {
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

template<class T>
bool writer<T>::file_exist_check_fail() {
  const char *name = file_name.c_str();
  std::ifstream test(name, std::ios::in);
  if (test.fail())
    return true;
  else {
    test.clear();
    return false;
  }
}

#pragma clang diagnostic pop