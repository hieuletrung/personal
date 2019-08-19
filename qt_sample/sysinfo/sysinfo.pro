#-------------------------------------------------
#
# Project created by QtCreator 2019-08-17T22:37:55
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysinfo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

COMPILE_MSG = "Compiling on"

SOURCES += \
        cpuwidget.cpp \
        main.cpp \
        mainwindow.cpp \
        memorywidget.cpp \
        sysinfo.cpp \
        sysinfowidget.cpp

HEADERS += \
        cpuwidget.h \
        mainwindow.h \
        memorywidget.h \
        sysinfo.h \
        sysinfowidget.h

windows {
    SOURCES += sysinfowindowimpl.cpp
    HEADERS += sysinfowindowimpl.h
}

linux {
    SOURCES += sysinfolinuximpl.cpp
    HEADERS += sysinfolinuximpl.h

    message($$COMPILE_MSG linux)
}

macx {
}

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
