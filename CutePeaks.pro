#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T16:19:21
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CutePeaks
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
        abifreader.cpp \
    PeaksView.cpp

HEADERS  += MainWindow.h \
    abifreader.h \
    PeaksView.h
