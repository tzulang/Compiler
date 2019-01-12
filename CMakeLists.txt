cmake_minimum_required(VERSION 3.1C)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

aux_source_directory(. SRC_LIST)
aux_source_directory(Lexer SRC_LIST)

INCLUDE_DIRECTORIES(.)
add_executable(${PROJECT_NAME} ${SRC_LIST})
