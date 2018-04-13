cmake_minimum_required(VERSION 3.9)
project(Car_Workshop)

set(CMAKE_CXX_STANDARD 11)

add_executable(Car_Workshop main.cc file_helper/writer.cc file_helper/writer.h file_helper/reader.cc file_helper/reader.h utility/datetime.cc utility/datetime.h base/vehicle.cc base/vehicle.h base/order.cc base/order.h base/problem_map.cc base/problem_map.h utility/utils.cc utility/utils.h base/bad_input.h)