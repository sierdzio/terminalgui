cmake_minimum_required(VERSION 3.16)

project(terminalgui LANGUAGES CXX)

find_package(Qt5 COMPONENTS REQUIRED Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(terminalgui tgscreen.cpp tgscreen.h tgwidget.cpp tgwidget.h
    tglabel.cpp tglabel.h textstream.cpp textstream.h
    reversibleanimation.cpp reversibleanimation.h)

target_link_libraries(terminalgui PUBLIC backend Qt5::Core)

target_include_directories(terminalgui PUBLIC ../)
