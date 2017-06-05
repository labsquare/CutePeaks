#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mView    = new TraceView;
    mYSlider = new QSlider(Qt::Horizontal);
    mXSlider = new QSlider(Qt::Horizontal);

    setCentralWidget(mView);

    QToolBar * bar = addToolBar("actions");
    mYSlider->setRange(0,1000);
    mXSlider->setRange(1,1000);

    mYSlider->setValue(0.2);

    bar->addWidget(mYSlider);
    bar->addWidget(mXSlider);

    connect(mYSlider, &QSlider::valueChanged, [=](){mView->setAmplitudeFactor(mYSlider->value() / 1000.0 );});
    connect(mXSlider, &QSlider::valueChanged, [=](){mView->setScaleFactor(mXSlider->value() / 100.0);});


//    connect(mYSlider,SIGNAL(valueChanged(int)),mView,SLOT(setAmplitudeFactor(int)));
//    connect(mXSlider,SIGNAL(valueChanged(int)),mView,SLOT(setScaleFactor(int)));
//    connect(mScrollBar,SIGNAL(valueChanged(int)),mView,SLOT(scrollTo(int)));


    resize(1000, 400);


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
