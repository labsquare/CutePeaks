#include "MainWindow.h"
#include <QApplication>
#include <QScrollArea>
#include "PeaksWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto area  = new PeaksWidget;


    area->show();


//    MainWindow w;
//    w.show();

    return a.exec();
}
