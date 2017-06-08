#include "MainWindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include "SequenceTraceFactory.h"
#include "TraceView.h"
#include "AbifSequenceTrace.h"
#include "ScfSequenceTrace.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CutePeaks");
    a.setOrganizationName("Labsquare");
    a.setOrganizationDomain("Labsquare.org");
    a.setApplicationVersion("0.1-beta");

    TraceView * view = new TraceView;
    view->show();

    view->setFilename("/tmp/examples/abcZ_F.scf");

//    ScfSequenceTrace trace(new QFile("/tmp/examples/abcZ_F.scf"));
//    qDebug()<<trace.version();


//    MainWindow w;
//  w.setFilename("/tmp/examples/A_forward.ab1");
//    w.show();

    return a.exec();
}
