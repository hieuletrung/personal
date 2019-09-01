TEMPLATE = subdirs

OTHER_FILES += \
    scripts/package-linux-deb.sh \
    scripts/package-linux-appimage.sh \
    scripts/package-android.sh \
    scripts/package-ios.sh

SUBDIRS += \
    gallery-core \
    gallery-desktop \
    gallery-mobile

gallery-desktop.depends = gallery-core
gallery-mobile.depends = gallery-core
