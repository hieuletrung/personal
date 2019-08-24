TEMPLATE = subdirs

CONFIG += c++14

OTHER_FILES += \
    sdk/Filter.h \
    plugins-common.pri \
    plugins-common-opencv.pri

SUBDIRS += \
    filter-plugin-blur \
    filter-plugin-grayscale \
    filter-plugin-original \
    image-animation
