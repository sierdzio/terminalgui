cmake_minimum_required(VERSION 3.16)

project(terminalgui-backend LANGUAGES CXX)

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

add_library(terminalgui-backend SHARED
  backend.cpp backend.h
  ${BACKEND_SRC}
)

target_include_directories(terminalgui-backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(terminalgui-backend PUBLIC Qt5::Core)

set_target_properties(terminalgui-backend PROPERTIES PUBLIC_HEADER backend.h)

install(TARGETS terminalgui-backend
  #CONFIGURATIONS Release
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
  PUBLIC_HEADER DESTINATION include/terminalgui
  INCLUDES DESTINATION include/terminalgui
)
