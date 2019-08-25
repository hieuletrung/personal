#-------------------------------------------------
#
# Project created by QtCreator 2019-08-24T11:03:07
#
#-------------------------------------------------

QT       += core widgets
QT       -= gui

TARGET = $$qtLibraryTarget(filter-plugin-blur)
TEMPLATE = lib
CONFIG += plugin

DEFINES += FILTERPLUGINBLUR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FilterBlur.cpp

HEADERS += \
        FilterBlur.h \
        filter-plugin-blur_global.h 

include(../plugins-common.pri)
include(../plugins-common-opencv.pri)

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
