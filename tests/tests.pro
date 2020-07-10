QT += testlib
QT += gui core
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"

SOURCES +=  tst_cutepeaks.cpp \
    ../src/core/abifsequencetrace.cpp \
    ../src/core/abstracttracereader.cpp \
    ../src/core/nucleotidalphabet.cpp \
    ../src/core/proteinalphabet.cpp \
    ../src/core/scfsequencetrace.cpp \
    ../src/core/sequence.cpp \
    ../src/core/trace.cpp

#include(../src/core/core.pri)
INCLUDEPATH += ../src/core

HEADERS += \
    ../src/core/abifsequencetrace.h \
    ../src/core/abstracttracereader.h \
    ../src/core/nucleotidalphabet.h \
    ../src/core/proteinalphabet.h \
    ../src/core/scfsequencetrace.h \
    ../src/core/sequence.h \
    ../src/core/trace.h
