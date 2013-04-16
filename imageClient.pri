##Path to TANGO and QWT library

unix{
    TANGO_DIR =  /usr
    QWT_DIR = /usr/include/qwt-qt4
    #OPENCV_DIR  = /usr/include

    INCLUDEPATH += -I $${TANGO_DIR}/include/tango \
            -I $${QWT_DIR}/# \
           #-I $${OPENCV_DIR}/

    LIBS += -L$${TANGO_DIR}/lib -ltango -llog4tango -lomniORB4 -lomniDynamic4 -lCOS4 -lomnithread -lpthread \
                -L$${QWT_DIR}/lib  -lqwt-qt4
            #    -L$${OPENCV_DIR}/lib  -lopencv_highgui  -lopencv_core

    #CONFIG += debug
    CONFIG(debug, debug|release) {
        QMAKE_CXXFLAGS_DEBUG += -g3 -O0
        message("DEBUG!")
    } else {
        DEFINES += QT_NO_DEBUG
        DEFINES += QT_NO_DEBUG_OUTPUT
        message("RELEASE!")
    }

}

win32{
    TANGO_DIR =  "C:\Program Files (x86)\tango\win32_vc9\win32_dll"
    QWT_DIR = "C:/Qwt-5.2.1"
    #OPENCV_DIR  = /usr/include

    INCLUDEPATH += $${TANGO_DIR}/include \
                    $${QWT_DIR}/include
                    #$${OPENCV_DIR}/include

    LIBS = -L$${TANGO_DIR}/lib -ltango -llog4tango -lomniORB414_rt -lomniDynamic414_rt -lCOS414_rt -lomnithread34_rt \
            -L$${QWT_DIR}/lib -lqwt5
            #    -L$${OPENCV_DIR}/lib  -lopencv_highgui  -lopencv_core

}
