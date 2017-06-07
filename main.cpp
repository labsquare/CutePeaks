#include "MainWindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include "SequenceTraceFactory.h"
#include "TraceView.h"
#include "AbifSequenceTrace.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CutePeaks");
    a.setOrganizationName("Labsquare");
    a.setOrganizationDomain("Labsquare.org");
    a.setApplicationVersion("0.1-beta");

    MainWindow w;
   // w.setFilename("/home/sacha/Dev/CutePeaks/examples/A_forward.ab1");
    w.show();

    return a.exec();
}
