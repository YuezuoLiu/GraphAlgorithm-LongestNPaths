cmake_minimum_required(VERSION 3.22)
project(Assignment_1)


set(SOURCES src/main.cc src/Graph.cc src/Utils.cc)
add_executable(main ${SOURCES})
target_include_directories(main PUBLIC include)