TEMPLATE = subdirs

#https://doi.org/10.1684/bdc.2014.1942SUBDIRS += qscintilla/Qt4Qt5/qscintilla.pro
SUBDIRS += src/src.pro


CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast


QMAKE_CXXFLAGS += -std=c++14



# Installation

desktop.path = /usr/share/applications
desktop.files += cutepeaks.desktop
icons.path = /usr/share/icons/hicolor/48x48/apps
icons.files += cutepeaks.png

INSTALLS += desktop icons

 
