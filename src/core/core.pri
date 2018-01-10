INCLUDEPATH += core

HEADERS += \
    $$PWD/nucleotidalphabet.h \
    $$PWD/proteinalphabet.h \
    $$PWD/sequence.h \
    $$PWD/trace.h \
    $$PWD/abstracttracereader.h \
    $$PWD/tracefactory.h \
#    $$PWD/commandlineinterpreter.h \
    $$PWD/abstracttracewriter.h \
    $$PWD/scftracereader.h \
    $$PWD/abiftracereader.h \
    $$PWD/scftracewriter.h \
    $$PWD/scfheader.h

SOURCES += \
    $$PWD/nucleotidalphabet.cpp \
    $$PWD/proteinalphabet.cpp \
    $$PWD/sequence.cpp \
    $$PWD/trace.cpp \
    $$PWD/abstracttracereader.cpp \
    $$PWD/tracefactory.cpp \
#    $$PWD/commandlineinterpreter.cpp \
    $$PWD/abstracttracewriter.cpp \
    $$PWD/scftracereader.cpp \
    $$PWD/abiftracereader.cpp \
    $$PWD/scftracewriter.cpp
