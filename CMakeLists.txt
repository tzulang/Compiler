cmake_minimum_required(VERSION 3.1C)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(Tests)


INCLUDE_DIRECTORIES(.)
add_executable(Main main.cpp)


