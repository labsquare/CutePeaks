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


//    std::vector<int> values = {1,2,3,4,5,6,7,8};
//    std::vector<int> results;

//    qDebug()<<values;

//    auto r = std::remove_if(values.begin(), values.end(),
//                 [](int x){return x > 3 && x < 7;});
//    values.erase(r);

//    qDebug()<<values;

    MainWindow w;
    w.setFilename("/tmp/examples/A_forward.ab1");
    w.show();

    return a.exec();
}
