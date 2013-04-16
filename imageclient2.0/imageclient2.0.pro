#-------------------------------------------------
#
# Project created by QtCreator 2013-03-02T20:37:53
#
#-------------------------------------------------

include(../imageClient.pri)
QT       +=  gui

TARGET = imageclient2
TEMPLATE = app

IMAGE_WIDGET_DIR =  ../imageWidget
INCLUDEPATH += $${IMAGE_WIDGET_DIR}/
LIBS += -L./ -L$${IMAGE_WIDGET_DIR}/designer/ -ltangoImageWidget

SOURCES += main.cpp\
        mainwindow.cpp \
    starttangowin.cpp \
    realtimesubwindow.cpp \
    subwindowmdi.cpp \
    snapshotsubwindow.cpp \
    tangoservervariableswin.cpp \
    roisubwindow.cpp \
    snapshotcontainer.cpp \
    roicontainer.cpp \
    realtimecontainer.cpp

HEADERS  += mainwindow.h \
    starttangowin.h \
    realtimesubwindow.h \
    subwindowmdi.h \
    snapshotsubwindow.h \
    tangoservervariableswin.h \
    roisubwindow.h \
    realtimecontainer.h \
    roicontainer.h \
    snapshotcontainer.h

FORMS    += mainwindow.ui

RESOURCES     = application.qrc
CONFIG += debug

lib.path += ./
unix:lib.files += \
    $${IMAGE_WIDGET_DIR}/designer/libtangoImageWidget.so
    #$${TANGO_DIR}/lib/libtango.so \
    #$${TANGO_DIR}/lib/liblog4tango.so \
    #$${TANGO_DIR}/lib/libomniORB4.so \
    #$${TANGO_DIR}/lib/liblog4tango.so \
    #$${TANGO_DIR}/lib/libomniDynamic4.so \
    #$${TANGO_DIR}/lib/libCOS4.so \
    #$${TANGO_DIR}/lib/libomnithread.so \
    #$${TANGO_DIR}/lib/libpthread.so \
    #${QWT_DIR}/lib/libqwt-qt4.so

unix:lib.files += \
    $${IMAGE_WIDGET_DIR}/designer/tangoImageWidget.dll \
    $${TANGO_DIR}/lib/tango.dll \
    $${TANGO_DIR}/lib/log4tango.dll \
    $${TANGO_DIR}/lib/omniORB414_rt.dll \
    $${TANGO_DIR}/lib/omniDynamic414_rt.dll \
    $${TANGO_DIR}/lib/COS414_rt.dll \
    $${TANGO_DIR}/lib/omnithread34_rt.dll \
    #$${TANGO_DIR}/lib/lib/pthread.dll \
    ${QWT_DIR}/lib/qwt5.dll


INSTALLS += lib
