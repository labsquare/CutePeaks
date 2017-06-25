#include "MainWindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include "sequence.h"
#include "sequenceview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CutePeaks");
    a.setOrganizationName("Labsquare");
    a.setOrganizationDomain("Labsquare.org");
    a.setApplicationVersion("0.1");


    MainWindow w;
//    w.setFilename("/tmp/examples/A_forward.ab1");
    w.show();

    return a.exec();
}
