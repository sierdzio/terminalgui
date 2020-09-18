cmake_minimum_required(VERSION 3.16)

project(terminalgui-examples LANGUAGES CXX)

find_package(Qt5 COMPONENTS REQUIRED Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
    ADD_DEFINITIONS(-DUNICODE)
    ADD_DEFINITIONS(-D_UNICODE)
endif()

add_executable(terminalgui-example terminalgui-example.cpp)
target_link_libraries(terminalgui-example PUBLIC terminalgui Qt5::Core)

add_executable(showcase-example showcase-example.cpp)
target_link_libraries(showcase-example PUBLIC terminalgui Qt5::Core)

add_executable(layouts-example layouts-example.cpp)
target_link_libraries(layouts-example PUBLIC terminalgui Qt5::Core)
