cmake_minimum_required(VERSION 3.16)

project(terminalgui
  LANGUAGES CXX
  VERSION 0.1.0
  DESCRIPTION "Widgets for your terminal, powered by Qt! Create textual GUI (TUI) in your console easily."
)

if (NOT WIN32)
  add_compile_options(-Wall -Werror -Wextra)
endif (NOT WIN32)

add_subdirectory(core)
add_subdirectory(widgets)
add_subdirectory(examples)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  MyLibConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

set(CPACK_GENERATOR "DEB;RPM") # ;NSIS
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

set(DOCS_DEFAULT OFF)
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
  set(DOCS_DEFAULT ON)
endif()

option(DOCS "Build documentation" ${DOCS_DEFAULT})
if (DOCS)
  find_package(Doxygen REQUIRED dot)
  if (DOXYGEN_FOUND)
    set(DOXYGEN_FILE_PATTERNS "*.cpp;*.h")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
    set(DOXYGEN_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
    set(DOXYGEN_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/doc/img")
    set(DOXYGEN_QT_AUTOBRIEF "YES")
    doxygen_add_docs(doc
      core widgets doc LICENSE.md README.md doc/developer_guide.md
      ALL
      COMMENT "Building documentation"
    )
  else()
    message("Doxygen has not been found, cannot build the documentation")
  endif()
endif()
