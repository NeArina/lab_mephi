cmake_minimum_required(VERSION 3.20)
project(lab4 C)

set(CMAKE_C_STANDARD 99)
set(GCC_COVERAGE_LINK_FLAGS "-lreadline")

add_executable(lab4 lab_4_std.c)
add_definitions(${GCC_COVERAGE_LINK_FLAGS})



