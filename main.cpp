#include "MainWindow.h"
#include <QApplication>
#include <QScrollArea>
#include "PeaksWidget.h"
#include "SequenceTraceFactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


//    w.setFilename("/home/sacha/Dev/CutePeaks/examples/A_forward.ab1");

//    w.show();

    return a.exec();
}
