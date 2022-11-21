cmake_minimum_required(VERSION 3.23)
project(graph)

set(CMAKE_CXX_STANDARD 20)

add_executable(graph main.cpp utils/DrawingKwargs.hpp utils/ArgumentsParser.cpp utils/ArgumentsParser.hpp)
