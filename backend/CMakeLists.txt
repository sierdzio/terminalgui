cmake_minimum_required(VERSION 3.16)

project(backend LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Waarning: GPLv2! Consider other backends...
find_library(newt newt)

add_library(backend backend.h)

set_target_properties(backend PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(backend PRIVATE newt)
