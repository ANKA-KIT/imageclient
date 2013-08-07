
include(../imageClient.pri)

DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG += release silent

QT += dbus

unix{
    CONFIG += dbus
}
#QMAKE_CXXFLAGS += -W c++0x
win32{
    QMAKE_LFLAGS += static
    DEFINES += \
            TANGO_HAS_DLL \
            LOG4TANGO_HAS_DLL

    CONFIG += static no-exceptions
}

MOC_DIR = moc
OBJECTS_DIR = obj
FORMS_DIR = ui
LANGUAGE = C++
TEMPLATE = app
UI_DIR = src
QMAKE_DEL_FILE = rm \
    -rf
QMAKE_CLEAN = moc \
    obj \
    Makefile \
    *.tag

CONFIG += warn_off
message("---------------------------------")

TEMPLATE = lib

UI_DIR = forms

RESOURCES = qtangoplugin.qrc

SOURCES	= \
    eimagebase.cpp \
    eimagescreen.cpp \
    etangodevice.cpp \
    imagehistogram.cpp \
    imagemanipulator.cpp \
    imagemarker.cpp \
    imagepicturemode.cpp \
    timage.cpp \
    timagesnapshot.cpp \
    roiclass.cpp \
    imagewidgetplugin.cpp \
    argtable/src/argtable2.c \
    argtable/src/arg_str.c \
    argtable/src/arg_rex.c \
    argtable/src/getopt1.c \
    argtable/src/getopt.c \
    argtable/src/arg_rem.c \
    argtable/src/arg_lit.c \
    argtable/src/arg_int.c \
    argtable/src/arg_file.c \
    argtable/src/arg_end.c \
    argtable/src/arg_dbl.c \
    argtable/src/arg_date.c


HEADERS	= \
    eimagebase.h \
    eimagescreen.h \
    etangodevice.h \
    imagehistogram.h \
    imagemanipulator.h \
    imagemarker.h \
    imagepicturemode.h \
    timage.h \
    TImage \
    timagesnapshot.h \
    TImageSnapshot \
    roiclass.h \
    imagewidgetplugin.h \
    argtable/src/argtable2.h \
    argtable/src/getopt.h \
    argtable/src/config.h \
    tangocommandwin.h

TARGET  = tangoImageWidget
DESTDIR = ./designer

QMAKE_CLEAN += designer

CONFIG += designer plugin qt thread debug

inc.files += $${HEADERS}
inc.path = ./release/include
unix:lib.files += $${DESTDIR}/libtangoImageWidget.so
win32:lib.files += $${DESTDIR}/tangoImageWidget.lib
lib.path = ./release/lib
# installation

INSTALLS += inc lib

OTHER_FILES += \
    argtable/src/config.h.in
