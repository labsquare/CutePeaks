#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mView = new PeaksView;
    setCentralWidget(mView);

    setFilename("/home/sacha/Dev/CutePeaks/examples/A_forward.ab1");


}

MainWindow::~MainWindow()
{

}

void MainWindow::setFilename(const QString &filename)
{
    if (QFile::exists(filename))
    mView->setFilename(filename);
    else
        QMessageBox::warning(this,"error","cannot find file " + filename);

}
