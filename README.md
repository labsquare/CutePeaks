# CutePeaks

[![C/C++ CI](https://github.com/labsquare/CutePeaks/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/labsquare/CutePeaks/actions/workflows/c-cpp.yml)

https://labsquare.github.io/CutePeaks/

A simple viewer for Sanger trace file made with Qt5.
Supports AB1 and SCF 3.0 file formats.
It has regular expression pattern finder and can export trace as SVG vector image.

![Preview](https://raw.githubusercontent.com/labsquare/CutePeaks/master/cutepeaks.gif)


# Installation
## Windows 
[Download windows binary](https://github.com/labsquare/CutePeaks/releases/download/0.2.3/CutePeaks-win32.exe)

## MacOSX 
[Downlad MacOS binary](https://github.com/labsquare/CutePeaks/releases/download/0.2.3/cutepeaks-macos.dmg)

## Linux
Linux binary is available as [AppImage](http://appimage.org/).
Download the AppImage from [here](https://github.com/labsquare/CutePeaks/releases).
Run it as follow:


    chmod +x cutepeaks-0.2.0-linux-x86_64.appimage
    ./cutepeaks-0.2.0-linux-x86_64.appimage


## Compilation
### Prerequisites
#### Install Qt ≥ 5.7

**From website**: Download Qt ≥ 5.7 from https://www.qt.io/.
Don't forget to check QtChart module during installation.

**From Ubuntu**: Qt 5.7 is not yet available with Ubuntu. But you can add a PPA to your software system.
For exemple for Xenial:

    sudo add-apt-repository ppa:beineri/opt-qt57-xenial
    sudo apt install qt57base qt57charts-no-lgpl
    source /opt/qt57/bin/qt57-env.sh

**From Fedora**: Qt 5.7 is available.

    sudo dnf install qt5-qtbase-devel qt5-qtcharts-devel

### Compile CutePeaks
Be sure you have the correct version of Qt (≥ 5.7) by using qmake --version. For exemple, if you have installed Qt from ppa:beineri, you will find it under /opt/qt57/bin/qmake. Then launch the compilation from CutePeaks folder as follow.

     /opt/qt57/bin/qmake --version
     /opt/qt57/bin/qmake
     make
     sudo make install

## Usage
CutePeaks supports following trace file formats:

- *.ab1
- *.scf

Example files are available here: 
https://github.com/labsquare/CutePeaks/tree/master/examples
You can open those files from cutepeaks by clicking open from the File menu.

## Features 
Once the file is open, cutepeaks allows you to : 
- Explore the trace from a scroll area. ( Finger geasture are supported with touch screen) 
- Scale the trace horizontally or vertically using 2 sliders at the bottom right.
- Select a subsequence with the mouse as with any text editor. Then you can cut or copy to the clipboard
- Make the reverse complement from the edit menu
- Display Sequence and metadata from the view menu
- Search for a regular expression pattern. Open the "Find Sequence..." from the edit menu
- Export trace or sequence to different format. ( e.g: Fasta, CSV, SVG or PNG image ) 

