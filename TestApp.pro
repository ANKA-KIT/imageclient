#-------------------------------------------------
#
# Project created by QtCreator 2012-03-13T14:58:19
#
#-------------------------------------------------

QT       += gui xml

TARGET = TestApp
TEMPLATE = app

INCLUDEPATH += -I /usr/include/tango -I .
LIBS += -L/usr/lib -ltango -llog4tango -lomniORB4 -llog4tango -lomniDynamic4 -lCOS4 -lomnithread -lpthread -lyat

SOURCES += main.cpp\
        mainwindow.cpp \
    realTimeSubwin.cpp \
    snapshotSubwin.cpp \
    menu.cpp \
    setTangoDevWin.cpp \
    setTangoDevCommandWin.cpp \
    tangoDeviceVideoSettingsWin.cpp

HEADERS  += mainwindow.h \
    enum.h

FORMS    += mainwindow.ui

CONFIG += debug

RESOURCES     = application.qrc



















