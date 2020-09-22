cmake_minimum_required(VERSION 3.16)

project(terminalgui
  LANGUAGES CXX
  VERSION 0.1.0
)

if (NOT WIN32)
  add_compile_options(-Wall -Werror -Wextra)
endif (NOT WIN32)

add_subdirectory(backend)
add_subdirectory(widgets)
add_subdirectory(examples)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  MyLibConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

SET(CPACK_GENERATOR "DEB;RPM") # ;NSIS
set(CPACK_PACKAGE_VENDOR "sierdzio")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Qt-based widgets for terminal")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "sierdzio")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Qt-based widgets for terminal")
SET(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a")
INCLUDE(CPack)
