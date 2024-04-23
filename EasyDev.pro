QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    deps/framelesswindow/framelesswindow.cpp \
    src/main.cpp \
    src/easydev.cpp \
    src/modules/flowlayout.cpp \
    src/utils/fontawesome.cpp

HEADERS += \
    deps/framelesswindow/framelesswindow.h \
    src/easydev.h \
    src/modules/flowlayout.h \
    src/utils/fontawesome.h

FORMS += \
    ui/easydev.ui

TRANSLATIONS += \
    i18n/EasyDev_en_HK.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc
