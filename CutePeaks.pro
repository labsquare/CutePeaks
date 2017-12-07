#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T16:19:21
#
#-------------------------------------------------

QT       += core gui svg
CONFIG   += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cutepeaks
TEMPLATE = app


include(core/core.pri)
include(gui/gui.pri)
include(QFontIcon/QFontIcon.pri)

SOURCES += main.cpp

# Installation
target.path  = /usr/local/bin
desktop.path = /usr/share/applications
desktop.files += cutepeaks.desktop
icons.path = /usr/share/icons/hicolor/48x48/apps
icons.files += cutepeaks.png

INSTALLS += target desktop icons

RESOURCES += \
    resource.qrc

TRANSLATIONS = translations/cutepeaks_fr.ts
