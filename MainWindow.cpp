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
