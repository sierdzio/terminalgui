cmake_minimum_required(VERSION 3.16)

project(backend LANGUAGES CXX)

find_package(Qt5 COMPONENTS REQUIRED Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    ADD_DEFINITIONS(-DUNICODE)
    ADD_DEFINITIONS(-D_UNICODE)
    SET(BACKEND_SRC backend_windows.cpp)
else()
    SET(BACKEND_SRC backend_linux.cpp)
endif()

add_library(backend
    backend.cpp backend.h
    ${BACKEND_SRC}
    )

target_include_directories(backend PUBLIC ../)

target_link_libraries(backend PUBLIC Qt5::Core)
