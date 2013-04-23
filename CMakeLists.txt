PROJECT(ImageClient)
cmake_minimum_required(VERSION 2.6)

set(VERSION "2.0.1")

FIND_PACKAGE(Qt4 REQUIRED)
find_package(PkgConfig)
pkg_check_modules(TANGO tango>=7.2.6 REQUIRED)

# check for 64 bit
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIB_INSTALL_DIR "lib64")
else()
  set(LIB_INSTALL_DIR "lib")
endif()

SET(QT_USE_QTDESIGNER ON)
INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS} -Wall -std=c++0x)

find_path(QWT_HEADERS qwt_plot.h HINTS /usr/include /usr/include/qwt5 /usr/local/qwt-5.2.1/include)
find_path(QWT_LIBS libqwt.so HINTS /usr/${LIB_INSTALL_DIR} /usr/local/qwt-5.2.1/lib)

add_subdirectory(imageWidget)
add_subdirectory(imageclient2.0)

if (UNIX)
  set(CPACK_PACKAGE_VERSION ${VERSION})
  set(CPACK_GENERATOR "RPM")
  set(CPACK_PACKAGE_NAME "imageclient")
  set(CPACK_PACKAGE_RELEASE 1)
  set(CPACK_PACKAGE_CONTACT "Mihael Koep")
  set(CPACK_PACKAGE_VENDOR "ANKA Computing Group")
  set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
  set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
  set(SMARACT_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/imageclient.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/imageclient.spec" @ONLY IMMEDIATE)
  set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/imageclient.spec")

  include(CPack)
endif()