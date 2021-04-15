#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T16:19:21
#
#-------------------------------------------------

QT       += core gui svg network
CONFIG   += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cutepeaks
TEMPLATE = app

INCLUDEPATH += QFontIcon

include(core/core.pri)
include(gui/gui.pri)
include(QFontIcon/QFontIcon.pri)

SOURCES += main.cpp



TRANSLATIONS = translations/cutepeaks_fr.ts

RESOURCES += \
    resources/resources.qrc


unix {
desktop.files += ../cutepeaks.desktop
desktop.path = /usr/share/applications/

icons.files += ../cutepeaks.png
icons.path = /usr/share/icons/hicolor/64x64/apps

target.path = /usr/bin/

INSTALLS += desktop icons target



}

win32{
RC_ICONS = ../cutepeaks.ico
}


