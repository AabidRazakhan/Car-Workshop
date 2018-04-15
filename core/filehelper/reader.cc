// /*
// *   Copyright (c) Ashar Khan 2018. <ashar786khan@gmail.com>
// *    This file is part of CSE202 Car Workshop Project.
// *   Car Workshop is free software : you can redistribute it and/or modify
// *    it under the terms of GNU General Public License as published by the Free Software Foundation,
// *   either version 3 of the License, or (at your option) any later version.
// *
// *   This Application is distributed in the hope that it will be useful
// *    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// *   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  Public License for more details.
// *
// *   You should have received a copy of the GNU General Public License along with this Source File.
// *   If not, see <http:www.gnu.org/licenses/>.
// */

// #include "reader.h"
// #include <cstring>
// #include <iostream>

// #pragma clang diagnostic push
// #pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// using namespace file;

// template<class T>
// reader<T>::reader(std::string file, bool bin) {
//   this->file_name = file;
//   this->isbinary = bin;
//   initiate();
// }

// template<class T>
// void reader<T>::initiate() {
//   if (isbinary)
//     st.open(file_name, std::ios::in | std::ios::binary);
//   else
//     st.open(file_name, std::ios::in);
//   if (st.fail()) {
//     char message[180];
//     strcpy(message, std::strerror(errno));
//       throw std::runtime_error(message);
//   }
// }

// template<class T>
// long long reader<T>::tell() {
//   return this->st.tellg();
// }

// template<class T>
// void reader<T>::seek_to(int pos, std::ios::seekdir type) {
//   if (isbinary) {
//     this->st.seekg((pos - 1) * sizeof(T), type);
//   } else
//     this->st.seekg(pos, type);
// }

// template<class T>
// T reader<T>::read() {
//   if (isbinary) {
//     T res;
//     st.read(reinterpret_cast<char *>(&res), sizeof(T));
//     return res;
//   } else {

//     auto *r = new char[800];
//     st.getline(r, 800, '\n');
//     std::string c(r);
//     delete r;
//     return T(c);
//   }
// }

// template<class T>
// T reader<T>::read(int pos)  {
//   if (isbinary) {
//     long long prev_point = st.tellg();
//     st.seekg((pos - 1) * sizeof(T), std::ios::beg);
//     T res;
//     st.read(reinterpret_cast<char *>(&res), sizeof(T));
//     st.seekg(prev_point, std::ios::beg);
//     return res;
//   } else {

//     long prev_point = st.tellg();
//     st.seekg(pos, std::ios::beg);

//     auto *res = new char[800];
//     st.getline(res, 800, '\n');
//     std::string v(res);
//     delete res;
//     st.seekg(prev_point, std::ios::beg);
//     return (T) v;
//   }
// }

// template<class T>
// void reader<T>::read_all(std::vector<T> &out)  {
//   long prev = st.tellg();
//   if (isbinary) {
//     st.seekg(0, std::ios::beg);
//     T o;
//     while (!st.eof()) {
//       st.read(reinterpret_cast<char *>(&o), sizeof(T));
//       out.push_back(o);
//     }
//     st.seekg(prev, std::ios::beg);
//   } else {
//     st.seekg(0, std::ios::beg);
//     std::string res;
//     auto *buff = new char[800];
//     while (!st.eof()) {
//       st.getline(buff, 800, '\n');
//       std::string s(buff);
//       out.push_back((T) s);
//     }
//     delete buff;
//   }
// }

// template<class T>
// reader<T>::~reader() {
//   if (this->st.is_open()) {
//     this->st.close();
//   }
// }
// #pragma clang diagnostic pop