#-------------------------------------------------
#
# Project created by QtCreator 2019-08-19T20:23:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gallery-desktop
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

CONFIG += c++11

SOURCES += \
        albumlistwidget.cpp \
        albumwidget.cpp \
        gallerywidget.cpp \
        main.cpp \
        mainwindow.cpp \
        picturedelegate.cpp \
        picturewidget.cpp \
        thumbnailproxymodel.cpp

HEADERS += \
        albumlistwidget.h \
        albumwidget.h \
        gallerywidget.h \
        mainwindow.h \
        picturedelegate.h \
        picturewidget.h \
        thumbnailproxymodel.h

FORMS += \
        albumlistwidget.ui \
        albumwidget.ui \
        gallerywidget.ui \
        mainwindow.ui \
        picturewidget.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core
else:unix: LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core

INCLUDEPATH += $$PWD/../gallery-core
DEPENDPATH += $$PWD/../gallery-core

RESOURCES += \
    resource.qrc

linux {
    target.path = $$_PRO_FILE_PWD_/../dist/desktop-linux/root/usr/bin/
    INSTALLS += target
}
