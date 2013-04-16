SET(source_files
  main.cpp
  mainwindow.cpp
  realtimecontainer.cpp
  realtimesubwindow.cpp
  roicontainer.cpp
  roisubwindow.cpp
  snapshotcontainer.cpp
  snapshotsubwindow.cpp
  starttangowin.cpp
  subwindowmdi.cpp
  tangoservervariableswin.cpp
  argtable/src/arg_int.c
  argtable/src/arg_lit.c
  argtable/src/arg_end.c
  argtable/src/arg_str.c
  argtable/src/argtable2.c
)

SET(source_headers
  mainwindow.h
  realtimecontainer.h
  realtimesubwindow.h
  roicontainer.h
  roisubwindow.h
  snapshotcontainer.h
  snapshotsubwindow.h
  starttangowin.h
  subwindowmdi.h
  tangoservervariableswin.h
  ui_mainwindow.h
  argtable/src/argtable2.h
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ImageClient_SOURCE_DIR}/imageWidget
  ${TANGO_INCLUDE_DIRS}
  ${QWT_HEADERS}
)

link_directories(
  ${TANGO_LIBRARY_DIRS}
  ${QWT_LIBS}
  ${ImageClient_BINARY_DIR}/imageWidget
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

target_link_libraries(imageclient tangoImageWidget ${TANGO_LIBRARIES} ${QT_LIBRARIES} pthread qwt opencv_highgui opencv_core)

install(TARGETS imageclient
        RUNTIME
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
