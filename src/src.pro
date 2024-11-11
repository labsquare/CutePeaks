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
desktop.files += ../io.github.labsquare.CutePeaks.desktop
desktop.path = $$PREFIX/share/applications/

icons.files += ../io.github.labsquare.CutePeaks.png
icons.path = $$PREFIX/share/icons/hicolor/64x64/apps

appdata.files += ../io.github.labsquare.CutePeaks.metainfo.xml
appdata.path = $$PREFIX/share/metainfo

target.path = $$PREFIX/bin/

INSTALLS += desktop icons appdata target



}

win32{
RC_ICONS = ../cutepeaks.ico
}


