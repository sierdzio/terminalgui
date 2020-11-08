cmake_minimum_required(VERSION 3.16)

project(terminalgui-core LANGUAGES CXX)

# This has to be below project() because it calls find_* function
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

if(WIN32)
  ADD_DEFINITIONS(-DUNICODE)
  ADD_DEFINITIONS(-D_UNICODE)
  SET(BACKEND_SRC tgterminal_windows.cpp)
else()
  SET(BACKEND_SRC tgterminal_linux.cpp)
endif()

add_library(terminalgui-core SHARED
  tgkey.h
  tgcommand.cpp tgcommand.h
  tgcolor.cpp tgcolor.h
  tgterminal.cpp tgterminal.h
  ${BACKEND_SRC}
)

target_include_directories(terminalgui-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(terminalgui-core PUBLIC Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(terminalgui-core
  PROPERTIES PUBLIC_HEADER "tgterminal.h tgcolor.h tgcommand.h tgkey.h")

install(TARGETS terminalgui-core
  #CONFIGURATIONS Release
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
  PUBLIC_HEADER DESTINATION include/terminalgui
  INCLUDES DESTINATION include/terminalgui
)
