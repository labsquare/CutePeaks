//#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include <iostream>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("CutePeaks");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("Labsquare.org");
    app.setApplicationVersion("0.1");

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("translations/cutepeaks_")+locale);
    app.installTranslator(&translator);



    MainWindow w;
    w.setFilename("/tmp/examples/A_forward.ab1");
    w.show();

    return app.exec();
}
