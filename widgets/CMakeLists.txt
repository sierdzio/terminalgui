cmake_minimum_required(VERSION 3.16)

project(terminalgui LANGUAGES CXX)

find_package(Qt5 COMPONENTS REQUIRED Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
  ADD_DEFINITIONS(-DUNICODE)
  ADD_DEFINITIONS(-D_UNICODE)
endif()

add_library(terminalgui SHARED
  utils/tgreversibleanimation.cpp
  utils/tghelpers.cpp
  styles/tgstyle.cpp
  layouts/tglayout.cpp
  layouts/tgchildfillsparentlayout.cpp
  layouts/tgcolumnlayout.cpp
  layouts/tgrowlayout.cpp
  layouts/tggridlayout.cpp
  widgets/tgwidget.cpp
  widgets/tglabel.cpp
  widgets/tgbutton.cpp
  widgets/tglineedit.cpp
  widgets/tgcheckbox.cpp
  widgets/tgradiobutton.cpp
  widgets/tgscrollbar.cpp
  widgets/tgscrollarea.cpp
  widgets/tglistview.cpp
  tgscreen.cpp
)

target_include_directories(terminalgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(terminalgui PUBLIC terminalgui-backend Qt5::Core)

install(TARGETS terminalgui
  #CONFIGURATIONS Release
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(FILES tgscreen.h
  #CONFIGURATIONS Release
  DESTINATION include/terminalgui
)

install(DIRECTORY utils styles layouts widgets
  #CONFIGURATIONS Release
  DESTINATION include/terminalgui
  PATTERN *.h
)
