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
    utils/tgreversibleanimation.cpp utils/tgreversibleanimation.h
    utils/tghelpers.cpp utils/tghelpers.h
    styles/tgborderstyle.h
    styles/tgtableborderstyle.h
    styles/tgstyle.cpp styles/tgstyle.h
    layouts/tglayout.cpp layouts/tglayout.h
    layouts/tgchildfillsparentlayout.cpp layouts/tgchildfillsparentlayout.h
    layouts/tgcolumnlayout.cpp layouts/tgcolumnlayout.h
    layouts/tgrowlayout.cpp layouts/tgrowlayout.h
    layouts/tggridlayout.cpp layouts/tggridlayout.h
    widgets/tgwidget.cpp widgets/tgwidget.h
    widgets/tglabel.cpp widgets/tglabel.h
    widgets/tgbutton.cpp widgets/tgbutton.h
    widgets/tglineedit.cpp widgets/tglineedit.h
    widgets/tgcheckbox.cpp widgets/tgcheckbox.h
    tgscreen.cpp tgscreen.h
    )

target_link_libraries(terminalgui PUBLIC backend Qt5::Core)

target_include_directories(terminalgui PUBLIC ./)
