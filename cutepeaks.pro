TEMPLATE = subdirs

#https://doi.org/10.1684/bdc.2014.1942SUBDIRS += qscintilla/Qt4Qt5/qscintilla.pro
SUBDIRS += src/src.pro

linux-g++ {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    target.path = $$PREFIX/bin

    desktop.path = $$PREFIX/share/applications/
    desktop.files += CutePeaks.desktop
    icon512.path = $$PREFIX/share/icons/hicolor/512x512/apps
    icon512.files += cutepeaks.png

    INSTALLS += icon512
    INSTALLS += desktop
    INSTALLS += target
}

CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast


QMAKE_CXXFLAGS += -std=c++14



