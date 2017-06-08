#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T16:19:21
#
#-------------------------------------------------

QT       += core gui svg
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cutepeaks
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AbstractSequenceTrace.cpp \
    AbifSequenceTrace.cpp \
    SequenceTraceFactory.cpp \
    TraceView.cpp \
    ScfSequenceTrace.cpp \
    sequence.cpp \
    proteinalphabet.cpp \
    nucleotidalphabet.cpp

HEADERS  += \
    SequenceTraceFactory.h \
    MainWindow.h \
    AbstractSequenceTrace.h \
    AbifSequenceTrace.h \
    TraceView.h \
    ScfSequenceTrace.h \
    sequence.h \
    proteinalphabet.h \
    nucleotidalphabet.h


# Installation
target.path  = /usr/local/bin
desktop.path = /usr/share/applications
desktop.files += cutepeaks.desktop
icons.path = /usr/share/icons/hicolor/48x48/apps
icons.files += cutepeaks.png

INSTALLS += target desktop icons
