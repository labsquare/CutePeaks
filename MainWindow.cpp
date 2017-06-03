#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mView    = new PeaksWidget;
    mYSlider = new QSlider(Qt::Horizontal);
    mXSlider = new QSlider(Qt::Horizontal);
    mScrollBar = new QScrollBar(Qt::Horizontal);


    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mView);
    mainLayout->addWidget(mScrollBar);

    QWidget * mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);


    setCentralWidget(mainWidget);

    QToolBar * bar = addToolBar("actions");
    mYSlider->setRange(20,100);
    mXSlider->setRange(1,10);
    mScrollBar->setRange(0,10014 - mainWidget->width());


    bar->addWidget(mYSlider);
    bar->addWidget(mXSlider);

    connect(mYSlider,SIGNAL(valueChanged(int)),mView,SLOT(setAmplitudeFactor(int)));
    connect(mXSlider,SIGNAL(valueChanged(int)),mView,SLOT(setScaleFactor(int)));
    connect(mScrollBar,SIGNAL(valueChanged(int)),mView,SLOT(scrollTo(int)));


    resize(1000, 400);


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
