PROJECT(ImageClient)
cmake_minimum_required(VERSION 2.6)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS} -Wall)

find_path(QWT_HEADERS qwt_plot.h HINTS /usr/include /usr/local/include /usr/local/qwt-5.2.1/include)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${QT_HEADERS}
  ${QWT_HEADERS}
  /usr/include/tango
  /usr/include/opencv
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

target_link_libraries(imageclient tango log4tango omniORB4 log4tango omniDynamic4 COS4 omnithread pthread qwt-qt4 opencv_highgui  opencv_core)
   
install(TARGETS imageclient
        RUNTIME
        DESTINATION bin)
