cmake_minimum_required(VERSION 3.10)  # minimum version of CMake required

project(GrandmaScheduler)           

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

#executable to the project using the specified source files
add_executable(GrandmaScheduler src/main.c)

