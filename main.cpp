//#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include "mainwindow.h"

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

//    QVector<int> a1 = {1,2,3,4,5,6};
//    QVector<int> b = {0,0,0,0};

//    qDebug()<<a1;
//    std::copy(b.begin(), b.end(), std::inserter(a1, a1.begin()+1));

//    qDebug()<<a1;


    MainWindow w;
    w.setFilename("/tmp/examples/A_forward.ab1");
    w.show();

    return a.exec();
}
