//#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include "sequence.h"
#include "tracefactory.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CutePeaks");
    a.setOrganizationName("Labsquare");
    a.setOrganizationDomain("Labsquare.org");
    a.setApplicationVersion("0.1");

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("translations/cutepeaks_")+locale);
    a.installTranslator(&translator);


    Trace trace = TraceFactory::createTrace("/tmp/examples/A_forward.ab1");
    Trace rev = trace.reverse();


    qDebug()<<trace.data('A');
//    qDebug()<<"==============";
//    qDebug()<<rev.data('A');



//    MainWindow w;
//    w.setFilename("/tmp/examples/A_forward.ab1");
//    w.show();

    return a.exec();
}
