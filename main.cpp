#include "MainWindow.h"
#include <QApplication>
#include <QScrollArea>
#include "PeaksWidget.h"
#include "SequenceTraceFactory.h"
#include "traceview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CutePeaks");
    a.setOrganizationName("Labsquare");
    a.setOrganizationDomain("Labsquare.org");
    a.setApplicationVersion("0.0.a");

    MainWindow w;
    w.setFilename("/home/sacha/Dev/CutePeaks/examples/A_forward.ab1");
    w.show();

    return a.exec();
}
