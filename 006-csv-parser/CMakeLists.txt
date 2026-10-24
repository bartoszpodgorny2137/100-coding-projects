cmake_minimum_required(VERSION 4.3)
project(006_csv_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(006_csv_parser main.cpp)
configure_file(${CMAKE_SOURCE_DIR}/data.csv ${CMAKE_BINARY_DIR}/data.csv COPYONLY)