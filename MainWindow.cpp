#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mView    = new PeaksView;
    mYSlider = new QSlider(Qt::Horizontal);
    mXSlider = new QSlider(Qt::Horizontal);

    setCentralWidget(mView);

    QToolBar * bar = addToolBar("actions");
    mYSlider->setRange(20,100);
    mXSlider->setRange(1,10);

    bar->addWidget(mYSlider);
    bar->addWidget(mXSlider);

    connect(mYSlider,SIGNAL(valueChanged(int)),mView,SLOT(setAmplitudeFactor(int)));
    connect(mXSlider,SIGNAL(valueChanged(int)),mView,SLOT(setScaleFactor(int)));



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
