cmake_minimum_required(VERSION 3.16)

project(terminalgui LANGUAGES CXX)

find_package(Qt5 COMPONENTS REQUIRED Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(terminalgui
    reversibleanimation.cpp reversibleanimation.h
    textstream.cpp textstream.h
    tghelpers.cpp tghelpers.h
    tgstyle.cpp tgstyle.h
    tgscreen.cpp tgscreen.h
    tgwidget.cpp tgwidget.h
    tglabel.cpp tglabel.h
    tgbutton.cpp tgbutton.h
    tglineedit.cpp tglineedit.h)

target_link_libraries(terminalgui PUBLIC backend Qt5::Core)

target_include_directories(terminalgui PUBLIC ../)
