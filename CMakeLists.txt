cmake_minimum_required(VERSION 3.0)
project(bomberman)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(bomberman src/main.cpp)
