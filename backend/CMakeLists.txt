cmake_minimum_required(VERSION 3.16)

project(backend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(backend backend.cpp backend.h)

target_include_directories(backend PUBLIC ../)
