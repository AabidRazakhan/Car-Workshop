cmake_minimum_required(VERSION 3.9)
project(Car_Workshop)

set(CMAKE_CXX_STANDARD 11)

add_executable(Car_Workshop main.cpp writer.cpp writer.h reader.cpp reader.h datetime.cpp datetime.h)