PROJECT(ImageClient)
cmake_minimum_required(VERSION 2.6)

set(VERSION "1.0.0")

FIND_PACKAGE(Qt4 REQUIRED)
find_package(PkgConfig)
pkg_check_modules(TANGO tango>=7.2.6 REQUIRED)

# check for 64 bit
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIB_INSTALL_DIR "lib64")
else()
  set(LIB_INSTALL_DIR "lib")
endif()

INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS} -Wall -std=c++0x)

find_path(QWT_HEADERS qwt_plot.h HINTS /usr/include /usr/include/qwt5 /usr/local/qwt-5.2.1/include)
find_path(QWT_LIBS libqwt.so HINTS /usr/${LIB_INSTALL_DIR} /usr/local/qwt-5.2.1/lib)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${QT_HEADERS}
  ${QWT_HEADERS}
  ${TANGO_INCLUDE_DIRS}
# TODO: use OpenCVConfig.cmake later
  /usr/include/opencv
)

link_directories(
  ${TANGO_LIBRARY_DIRS}
  ${QWT_LIBS}
)
SET(source_files
  main.cpp
  mainwindow.cpp
  my_device.cpp
  starttangowin.cpp
  subwindow.cpp
  subwindowrealtime.cpp
  imagewidget.cpp
  subwindowsnapshot.cpp
  imgmanipulation.cpp
  tangosettingswin.cpp
  menutab.cpp
  tangovariables.cpp
  mythread.cpp
  histogram_item.cpp
  imagehistogram.cpp
  mylineedit.cpp
  picturemode.cpp
  bgcpl_wgt.cpp
  slidermanip.cpp
  propertymanipulation.cpp
  manipulator.cpp
  rsfl_wgt.cpp
  mydevproperty.cpp
  argtable/src/arg_int.c
  argtable/src/arg_lit.c
  argtable/src/arg_end.c
  argtable/src/arg_str.c
  argtable/src/argtable2.c
)

SET(source_headers
  mainwindow.h
  my_device.h
  starttangowin.h
  subwindow.h
  subwindowrealtime.h
  imagewidget.h
  subwindowsnapshot.h
  imgmanipulation.h
  tangosettingswin.h
  enum.h
  menutab.h
  tangovariables.h
  mythread.h
  imagehistogram.h
  histogram_item.h
  mylineedit.h
  picturemode.h
  mydevproperty.h
  bgcpl_wgt.h
  slidermanip.h
  propertymanipulation.h
  manipulator.h
  rsfl_wgt.h
  argtable/src/argtable2.h
)

SET(source_FORMS
  mainwindow.ui
)
SET(imageclient_RESOURCES
  application.qrc
)

QT4_WRAP_CPP(imageclient_HEADERS_MOC ${source_headers})
QT4_WRAP_UI(imageclient_FORMS_HEADERS ${source_FORMS})
QT4_ADD_RESOURCES(imageclient_RESOURCES_RCC ${imageclient_RESOURCES})

add_executable(imageclient ${source_files}  ${imageclient_HEADERS_MOC} ${imageclient_FORMS_HEADERS} ${imageclient_RESOURCES_RCC})

target_link_libraries(imageclient ${TANGO_LIBRARIES} ${QT_LIBRARIES} pthread qwt opencv_highgui opencv_core)
   
install(TARGETS imageclient
        RUNTIME
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
if (UNIX)
  set(CPACK_PACKAGE_VERSION ${VERSION})
  set(CPACK_GENERATOR "RPM")
  set(CPACK_PACKAGE_NAME "imageclient")
  set(CPACK_PACKAGE_RELEASE 4)
  set(CPACK_PACKAGE_CONTACT "Mihael Koep")
  set(CPACK_PACKAGE_VENDOR "ANKA Computing Group")
  set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
  set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
  set(SMARACT_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/imageclient.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/imageclient.spec" @ONLY IMMEDIATE)
  set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/imageclient.spec")

  include(CPack)
endif()