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
    icon64.path = $$PREFIX/share/icons/hicolor/64x64/apps
    icon64.files += cutepeaks.png

    INSTALLS += icon64
    INSTALLS += desktop
    INSTALLS += target
}

CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast


QMAKE_CXXFLAGS += -std=c++14



