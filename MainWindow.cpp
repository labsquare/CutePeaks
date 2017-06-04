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
    mYSlider->setRange(0,100);
    mXSlider->setRange(1,100);

    mYSlider->setValue(0.2);




    bar->addWidget(mYSlider);
    bar->addWidget(mXSlider);

    connect(mYSlider,SIGNAL(valueChanged(int)),mView,SLOT(setAmplitudeFactor(int)));
    connect(mXSlider,SIGNAL(valueChanged(int)),mView,SLOT(setScaleFactor(int)));
    connect(mScrollBar,SIGNAL(valueChanged(int)),mView,SLOT(scrollTo(int)));


    resize(1000, 400);



    bar->addAction(tr("File"), this, SLOT(openFile()));
    bar->addWidget(mYSlider);
    bar->addWidget(mXSlider);


    connect(mYSlider,SIGNAL(valueChanged(int)),mView,SLOT(setAmplitudeFactor(int)));
    connect(mXSlider,SIGNAL(valueChanged(int)),mView,SLOT(setScaleFactor(int)));

    restoreSettings();

}

MainWindow::~MainWindow()
{

}



void MainWindow::openFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath());
    setFilename(file);

    QSettings settings;
    settings.endGroup();
}

void MainWindow::setFilename(const QString &filename)
{
    mFile = filename;

    if (filename.isEmpty()) return;

    if (QFile::exists(filename))
        mView->setFilename(filename);
    else
        QMessageBox::warning(this,"error","cannot find file " + filename);

    qDebug()<< mView->dataCount();
    mScrollBar->setRange(0, mView->dataCount());
    mScrollBar->setPageStep(mView->width() / mView->mXFactor);
//    mScrollBar->setSingleStep(10);



}






void MainWindow::closeEvent(QCloseEvent *)
{
    writeSettings();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup("Main");
    settings.setValue("currentFile", mFile);
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}


void MainWindow::restoreSettings()
{
    QSettings settings;
    settings.beginGroup("Main");
    setFilename(settings.value("currentFile", "").toString());
    resize(settings.value("size", QSize(800, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}
