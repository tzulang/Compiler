cmake_minimum_required(VERSION 3.1C)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-reorder")


#add_definitions(-DPARSE_WSTRING)
#add_definitions(-DPARSE_U16)
#add_definitions(-DPARSE_U16)
#add_definitions(-DPARSE_U32)

add_subdirectory(Tests)

INCLUDE_DIRECTORIES(.)


add_executable(Main main.cpp)


