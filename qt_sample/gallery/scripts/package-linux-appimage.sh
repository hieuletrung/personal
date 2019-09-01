#!/bin/bash

QTDIR=/opt/Qt/5.12.3/gcc_64/
DIST_DIR=dist/desktop-linux

BUILD_DIR=build

mkdir -p $DIST_DIR && cd $DIST_DIR
mkdir -p $BUILD_DIR

pushd $BUILD_DIR
$QTDIR/bin/qmake \
    -spec linux-g++ \
    "CONFIG += release" \
    ../../../gallery.pro
make qmake_all

pushd gallery-core && make ; popd
pushd gallery-desktop && make ; popd
popd

export QT_PLUGIN_PATH=$QTDIR/plugins/
export LD_LIBRARY_PATH=$QTDIR/lib:$(pwd)/build/gallery-core

linuxdeployqt \
    build/gallery-desktop/gallery-desktop \
    -appimage

mv build/gallery-desktop.AppImage .
