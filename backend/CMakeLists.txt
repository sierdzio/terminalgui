cmake_minimum_required(VERSION 3.16)

project(backend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(backend
    backend.cpp backend.h
    backend_linux.cpp
    )

target_include_directories(backend PUBLIC ../)
