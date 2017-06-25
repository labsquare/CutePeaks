# CutePeaks

![](https://travis-ci.org/labsquare/CutePeaks.svg?branch=master)
[![Join the chat at https://gitter.im/labsquare/CutePeaks](https://badges.gitter.im/labsquare/CutePeaks.svg)](https://gitter.im/labsquare/CutePeaks?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


A simple viewer for Sanger trace file made with Qt5. 
Support AB1 and SCF 3.0 file format. 

![Preview](https://raw.githubusercontent.com/labsquare/CutePeaks/master/cutepeaks.gif)


# Installation 
## Linux 
For now, only Linux binary has been done. 
Download the appimage from [here](https://github.com/labsquare/CutePeaks/releases) 
Run it as follow : 


    chmod +x cutepeaks-0.1.0-linux-x86_64.appimage
    ./cutepeaks-0.1.0-linux-x86_64.appimage

    
## Compilation 
### Prerequisites - Install KArchive
### Install Qt >5.7

**From website** : Download Qt > 5.7 from https://www.qt.io/.   
Don't forget to check QtChart module during installation. 

**From ubuntu** : Qt 5.7 is not yet avaible with ubuntu. But you can add PPA to your software system. 
For exemple from xenial 

    sudo add-apt-repository ppa:beineri/opt-qt57-xenial
    sudo apt-get install qt57base qt57charts-no-lgpl
    source /opt/qt57/bin/qt57-env.sh

**From fedora** : Qt 5.7 is avaible

    sudo dnf install qt5-qtbase-devel qt5-qtcharts-devel 

### Compile FastQt 
Be sure you have the correct version of Qt (>5.7) by using qmake --version. For exemple, if you have installed Qt from ppa:beineri, you will find it under /opt/qt57/bin/qmake. Then launch the compilation from FastQC folder as follow.

     /opt/qt57/bin/qmake --version
     /opt/qt57/bin/qmake 
     make 
     sudo make install 

## Usage

Cutepeaks support following trace file:

- *.ab1
- *.scf

## How to cite CutePeaks 
Labsquare Team, et al (2017). FastQt: a simple sanger trace file avaible at https://github.com/labsquare/CutePeaks
