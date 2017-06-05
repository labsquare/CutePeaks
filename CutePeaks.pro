#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T16:19:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CutePeaks
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
        abifreader.cpp \
    AbstractSequenceTrace.cpp \
    AbifSequenceTrace.cpp \
    SequenceTraceFactory.cpp \
    TraceView.cpp

HEADERS  += \
    abifreader.h \
    SequenceTraceFactory.h \
    MainWindow.h \
    AbstractSequenceTrace.h \
    AbifSequenceTrace.h \
    TraceView.h
