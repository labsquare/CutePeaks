//#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QtCore>
#include <iostream>
#include "mainwindow.h"
#include "qfonticon.h"
#include "commandlineinterpreter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("CutePeaks");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("Labsquare.org");
    app.setApplicationVersion("0.2.2");

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("translations/cutepeaks_")+locale);
    app.installTranslator(&translator);


    CommandLineInterpreter cli(&app);

    if (cli.needCLI())
        return cli.process();

    else {
        QFontIcon::instance()->addFont(":/font/fontawesome.ttf");
        MainWindow w;
        w.setFilename(cli.filename());
        w.show();
        return app.exec();

    }

}
