SET(source_files
    eimagebase.cpp
    eimagescreen.cpp
    etangodevice.cpp
    imagehistogram.cpp
    imagemanipulator.cpp
    imagemarker.cpp
    imagepicturemode.cpp
    imagewidgetplugin.cpp
    roiclass.cpp
    timage.cpp
    timagesnapshot.cpp
    editmarkerdialog.cpp
)

SET(source_headers
    eimagebase.h
    eimagescreen.h
    etangodevice.h
    imagehistogram.h
    imagemanipulator.h
    imagemarker.h
    imagepicturemode.h
    imagewidgetplugin.h
    roiclass.h
    timage.h
    timagesnapshot.h
    editmarkerdialog.h
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${QWT_HEADERS}
    ${TANGO_INCLUDE_DIRS}
)

SET(source_FORMS
    editmarkerdialog.ui
)

SET(tangoImageWidget_RESOURCES
    qtangoplugin.qrc
)

QT4_WRAP_CPP(tangoImageWidget_HEADERS_MOC ${source_headers})
QT4_WRAP_UI(tangoImageWidget_FORMS_HEADERS ${source_FORMS})
QT4_ADD_RESOURCES(tangoImageWidget_RESOURCES_RCC ${tangoImageWidget_RESOURCES})

add_library(tangoImageWidget ${source_files} ${tangoImageWidget_HEADERS_MOC} ${tangoImageWidget_FORMS_HEADERS} ${tangoImageWidget_RESOURCES_RCC})
target_link_libraries(tangoImageWidget ${TANGO_LIBRARIES} ${QT_LIBRARIES} pthread qwt opencv_highgui opencv_core)
