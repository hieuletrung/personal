#-------------------------------------------------
#
# Project created by QtCreator 2019-08-31T08:48:21
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drum-machine
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

SOURCES += \
        BinarySerializer.cpp \
        JsonSerializer.cpp \
        PlaybackWorker.cpp \
        Serializable.cpp \
        Serializer.cpp \
        SoundEffectWidget.cpp \
        SoundEvent.cpp \
        Track.cpp \
        XmlSerializer.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        BinarySerializer.h \
        JsonSerializer.h \
        MainWindow.h \
        PlaybackWorker.h \
        Serializable.h \
        Serializer.h \
        SoundEffectWidget.h \
        SoundEvent.h \
        Track.h \
        XmlSerializer.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
