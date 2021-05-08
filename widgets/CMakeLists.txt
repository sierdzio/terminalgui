cmake_minimum_required(VERSION 3.16)

project(terminalgui LANGUAGES CXX)

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
endif()

add_library(terminalgui STATIC
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
  widgets/tgpopup.cpp
  models/tgcheckablestringlistmodel.cpp
  tgscreen.cpp
)

target_include_directories(terminalgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(terminalgui PUBLIC terminalgui-core)

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
