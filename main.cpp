#include "MainWindow.h"
#include <QApplication>

#include "PeaksWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PeaksWidget w;
    w.show();
//    MainWindow w;
//    w.show();

    return a.exec();
}
