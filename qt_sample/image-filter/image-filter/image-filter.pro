#-------------------------------------------------
#
# Project created by QtCreator 2019-08-24T09:57:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image-filter
TEMPLATE = app

INCLUDEPATH += ../filter-plugin-designer

win32 {
    LIBS += -L$$(QTDIR)/../../Tools/QtCreator/bin/plugins/designer -lfilter-plugin-designer
}
macx {
    LIBS += -L$$(QTDIR)/../../"QtCreator.app"/Contents/PlugIns/designer/ -lfilter-plugin-designer
}
linux {
    LIBS += -L$$(QTDIR)/../../Tools/QtCreator/lib/Qt/plugins/designer/ -lfilter-plugin-designer
}


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
