cmake_minimum_required(VERSION 3.16)

project(terminalgui LANGUAGES CXX)

if (NOT WIN32)
  add_compile_options(-Wall -Werror -Wextra)
endif (NOT WIN32)

add_subdirectory(backend)
add_subdirectory(widgets)
add_subdirectory(examples)
