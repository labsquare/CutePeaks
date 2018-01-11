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

target.path = /usr/bin

INSTALLS += target


# QScintilla
#LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/ -lqscintilla2
#PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/qscintilla2.lib
#PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/libqscintilla2.a


TRANSLATIONS = translations/cutepeaks_fr.ts

RESOURCES += \
    resources/resources.qrc
