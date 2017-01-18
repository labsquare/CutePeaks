#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mView = new PeaksView;
    setCentralWidget(mView);

    setFilename("/home/sacha/CutePeaks/data/A_reverse.ab1");


}

MainWindow::~MainWindow()
{

}

void MainWindow::setFilename(const QString &filename)
{

    mView->setFilename(filename);

}
