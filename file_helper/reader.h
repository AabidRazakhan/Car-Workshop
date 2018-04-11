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

/*
 * [PASSED ALL READ TEST ON STRINGS ON : 23 MARCH, 2018 : 2:00 AM]
 * [PASSED ALL READ TEST ON VALID GENERIC CLASSES ON : 23 MARCH, 2018 : 3:00 AM]
 */

/**********************************LIMITATIONS*******************************************/
//	As of now all the classes calling this API must fulfil following conditions.


/*	1. NOTE : BECAUSE THIS IMPLEMENTS TEMPLATES
 *	ALL THE FILES INCLUDING READER.H MUST INCLUDE
 *	READER.CPP IN ORDER TO AVOID LINKER ERROR.
 *
 *	2. READING TO CLASS CONTAINING DYNAMIC DATA MEMBERS. MUST NOT EXIST.
 *	For example : std::string ==> const char * , std::vector<?> ==> []. they just cause sizeof(T) to fail.
 *
 *	3. TO READ SIMPLE STRINGS, PASS <std::string> AS GENERIC TYPE INDICATOR.
 *
 *	4. IF A WRITER HAS NOT CLOSED A CONNECTION TO THE FILE, THEN A READER ATTEMPTING TO WRITE TO THAT FILE WILL FAIL.
 *	MAKE SURE TO CALL READERS AND WRITERS IN A SEPARATE SCOPE IF THEY BOTH WORK WITH SAME FILE.
 *	OR USE DYNAMIC MEMORY ALLOCATION AND DELETE WRITER AND READERS AS SOON AS YOU ARE DONE WITH THEM.
 *	CALL TO DESTRUCTOR WILL RELEASE THE STREAM LOCK TO THE FILE (CLOSE THE CONNECTION TO FILE).
 *
 *	5. MAKE SURE THAT CLASS YOU ARE WRITING VIA THESE HELPERS MUST
 *	HAVE A NON EXPLICIT PARAMETERIZED CONSTRUCTOR WITH <std::string> AS THE ONLY ARG
 */
#pragma once
#include<fstream>
#include<vector>
#include<string>
#include <cwchar>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

namespace file {
template<class T>
class reader {

  std::ifstream st;
  bool isbinary;
  std::string file_name;
  void initiate();

 public:
  reader() = delete;
  explicit reader(std::string file_name, bool bin = false);
  long long tell();
  void seek_to(int off, std::ios::seekdir type);
  T read();
  T read(int pos);
  void read_all(std::vector<T> &);
  ~reader();
};
}
#pragma clang diagnostic pop