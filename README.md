# CutePeaks

![](https://travis-ci.org/labsquare/CutePeaks.svg?branch=master)
[![Join the chat at https://gitter.im/labsquare/CutePeaks](https://badges.gitter.im/labsquare/CutePeaks.svg)](https://gitter.im/labsquare/CutePeaks?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.824555.svg)](https://doi.org/10.5281/zenodo.824555)


A simple viewer for Sanger trace file made with Qt5.
Supports AB1 and SCF 3.0 file formats.

![Preview](https://raw.githubusercontent.com/labsquare/CutePeaks/master/cutepeaks.gif)


# Installation
## Windows 
[Download windows binary 32 bits](https://github.com/labsquare/CutePeaks/releases/download/0.2.0/cutepeaks-0.2.0-win32.exe)

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

## How to cite CutePeaks
Labsquare Team (2017). CutePeaks: a simple Sanger trace file. Available online at https://github.com/labsquare/CutePeaks doi:10.5281/zenodo.824555
