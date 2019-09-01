#-------------------------------------------------
#
# Project created by QtCreator 2019-08-18T10:50:34
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = gallery-core
TEMPLATE = lib

DEFINES += GALLERYCORE_LIBRARY

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
        album.cpp \
        albumdao.cpp \
        albummodel.cpp \
        databasemanager.cpp \
        picture.cpp \
        picturedao.cpp \
        picturemodel.cpp

HEADERS += \
        album.h \
        albumdao.h \
        albummodel.h \
        databasemanager.h \
        gallery-core_global.h  \
        picture.h \
        picturedao.h \
        picturemodel.h

unix {
    target.path = $$_PRO_FILE_PWD_/../dist/desktop-linux/root/usr/lib/
    INSTALLS += target
}
