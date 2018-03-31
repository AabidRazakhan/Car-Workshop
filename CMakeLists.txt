cmake_minimum_required(VERSION 3.9)
project(Car_Workshop)

set(CMAKE_CXX_STANDARD 11)

add_executable(Car_Workshop main.cc writer.cc writer.h reader.cc reader.h datetime.cc datetime.h vehicle.cc vehicle.h order.cc order.h problem_map.cc problem_map.h utils.cc utils.h)