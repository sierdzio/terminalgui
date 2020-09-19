cmake_minimum_required(VERSION 3.16)

project(terminalgui LANGUAGES CXX)

if (NOT WIN32)
  add_compile_options(-Wall -Werror -Wextra)
endif (NOT WIN32)

add_subdirectory(backend)
add_subdirectory(widgets)
add_subdirectory(examples)

install(TARGETS backend terminalgui
  COMPONENT terminalgui
  LIBRARY DESTINATION "/usr/lib"
)

#RUNTIME DESTINATION "/home/"
#DESTINATION "/home/"

SET(CPACK_GENERATOR "DEB") # ;RPM;NSIS
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "sierdzio")
SET(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a")
INCLUDE(CPack)
