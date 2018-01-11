TEMPLATE = subdirs

#https://doi.org/10.1684/bdc.2014.1942SUBDIRS += qscintilla/Qt4Qt5/qscintilla.pro
SUBDIRS += src/src.pro


CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast


QMAKE_CXXFLAGS += -std=c++14


unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

target.path = $$PREFIX/bin
target.files = src/cutepeaks

desktop.files += cutepeaks.desktop
desktop.path = $$PREFIX/share/applications/

icons.files += cutepeaks.png
icons.path = $$PREFIX/share/icons/hicolor/48x48/apps

INSTALLS += target desktop icons

}

 
