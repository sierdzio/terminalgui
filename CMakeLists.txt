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
set(CPACK_PACKAGE_DESCRIPTION "Develop event-driven, customizable widget applications for terminals.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_CHECKSUM "SHA512")
set(CPACK_STRIP_FILES ON)

SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
SET(CPACK_DEB_COMPONENT_INSTALL OFF)
SET(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a")
SET(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
# https://www.debian.org/doc/debian-policy/ch-archive.html#s-subsections
SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
SET(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
SET(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")

SET(CPACK_RPM_COMPONENT_INSTALL OFF)
SET(CPACK_RPM_COMPRESSION_TYPE "xz")
SET(CPACK_RPM_FILE_NAME "RPM-DEFAULT")

INCLUDE(CPack)
