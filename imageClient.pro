#-------------------------------------------------
#
# Project created by QtCreator 2012-05-15T10:25:55
#
#-------------------------------------------------

QT       +=  gui
TARGET = imageClient
TEMPLATE = app

#The $() "$$()" operator accesses environment variables, not .pro file variables.

unix{
    TANGO_DIR =  /usr
    QWT_DIR = /usr/local/qwt-5.2.1
    #QWT_DIR = /usr/local/qwt5
    #QWT_DIR = /usr/include/qwt5     #set   -I $${QWT_DIR}/
    OPENCV_DIR  = /usr/local
    ARGTABLE_DIR = argtable/nix

    INCLUDEPATH += -I $${TANGO_DIR}/include/tango \
            -I $${QWT_DIR}/include \
           -I $${OPENCV_DIR}/include \
            -I $${ARGTABLE_DIR}/include
    LIBS += -L$${TANGO_DIR}/lib -ltango -llog4tango -lomniORB4 -llog4tango -lomniDynamic4 -lCOS4 -lomnithread -lpthread \
                -L$${QWT_DIR}/lib  -lqwt \
                -L$${ARGTABLE_DIR}/lib64  -largtable2 \
                -L$${OPENCV_DIR}/lib  -lopencv_highgui  -lopencv_core
#-lopencv_photo -lopencv_contrib -lopencv_calib3d -lopencv_imgproc
    #CONFIG += debug
    CONFIG(debug, debug|release) {
        QMAKE_CXXFLAGS_DEBUG += -g3 -O0
        message("DEBUG!")
    } else {
        DEFINES += QT_NO_DEBUG
        DEFINES += QT_NO_DEBUG_OUTPUT
        message("RELEASE!")
    }
    #CONFIG      += warn_off release qt app_bundle
}

win32{
    TANGO_DIR =  "C:/Program Files/tango/win32_vc9/win32_dll"
    QWT_DIR = "C:/Qwt-5.2.1"
    OPENCV_DIR  = "C:/Users/ISS/Downloads/opencv/opencv/install"
    ARGTABLE_DIR = argtable/Win
    #IMAGEFORMATS = "C:/Qt/4.8.1/plugins"

    INCLUDEPATH += $${TANGO_DIR}/include \
                    $${QWT_DIR}/include \
                    $${ARGTABLE_DIR}  \
                    $${OPENCV_DIR}/include
    LIBS = -L$${TANGO_DIR}/lib -ltango -llog4tango -lomniORB414_rt -lomniDynamic414_rt -lCOS414_rt -lomnithread34_rt \
            -L$${QWT_DIR}/lib -lqwt5 \
            -L$${ARGTABLE_DIR}/  -largtable2 \
            -L$${OPENCV_DIR}/lib   -lopencv_highgui242d  -lopencv_core242d
   #         -L.$${IMAGEFORMATS}/ -lqgif4 -lqjpeg4  -lqtiff4
    DEFINES += \
            TANGO_HAS_DLL \
            LOG4TANGO_HAS_DLL

    CONFIG(debug, debug|release) {
        QMAKE_CXXFLAGS_DEBUG += -g3 -O0
        message("DEBUG!")
    } else {
        DEFINES += QT_NO_DEBUG
        DEFINES += QT_NO_DEBUG_OUTPUT
        message("RELEASE!")
    }

}

SOURCES += main.cpp\
        mainwindow.cpp \
    my_device.cpp \
    starttangowin.cpp \
    subwindow.cpp \
    subwindowrealtime.cpp \
    imagewidget.cpp \
    subwindowsnapshot.cpp \
    imgmanipulation.cpp \
    tangosettingswin.cpp \
    menutab.cpp \
    tangovariables.cpp \
    mythread.cpp \
    histogram_item.cpp \
    imagehistogram.cpp \
    mylineedit.cpp \
    picturemode.cpp \
    bgcpl_wgt.cpp \
    slidermanip.cpp \
    propertymanipulation.cpp \
    manipulator.cpp \
    rsfl_wgt.cpp \
    mydevproperty.cpp

HEADERS  += mainwindow.h \
    my_device.h \
    starttangowin.h \
    subwindow.h \
    subwindowrealtime.h \
    imagewidget.h \
    subwindowsnapshot.h \
    imgmanipulation.h \
    tangosettingswin.h \
    enum.h \
    menutab.h \
    tangovariables.h \
    mythread.h \
    imagehistogram.h \
    histogram_item.h \
    mylineedit.h \
    picturemode.h \
    mydevproperty.h \
    bgcpl_wgt.h \
    slidermanip.h \
    propertymanipulation.h \
    manipulator.h \
    rsfl_wgt.h

FORMS    += mainwindow.ui

RESOURCES     = application.qrc


















































































