cmake_minimum_required(VERSION 3.16)

project(terminalgui-examples LANGUAGES CXX)

# This has to be below project() because it calls find_* function
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(WIN32)
  ADD_DEFINITIONS(-DUNICODE)
  ADD_DEFINITIONS(-D_UNICODE)
endif()

add_executable(animation-example animation-example.cpp)
target_link_libraries(animation-example PUBLIC terminalgui)

add_executable(widgets-example widgets-example.cpp)
target_link_libraries(widgets-example PUBLIC terminalgui)

add_executable(layouts-example layouts-example.cpp)
target_link_libraries(layouts-example PUBLIC terminalgui)

add_executable(colors-example colors-example.cpp)
target_link_libraries(colors-example PUBLIC terminalgui)

add_executable(item-views-example item-views-example.cpp)
target_link_libraries(item-views-example PUBLIC terminalgui)
