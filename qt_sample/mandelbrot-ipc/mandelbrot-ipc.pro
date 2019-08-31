TEMPLATE = subdirs

CONFIG += c++14

OTHER_FILES += \
    sdk/Message.h \
    sdk/JobRequest.h \
    sdk/JobResult.h \
    sdk/MessageUtils.h

SUBDIRS += \
    mandelbrot-app \
    mandelbrot-worker

