#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mView    = new TraceView;
    mYSlider = new QSlider(Qt::Horizontal);
    mXSlider = new QSlider(Qt::Horizontal);
    mSearchbar = new QLineEdit;
    mSeqEdit   = new QTextEdit;
    mSearchbar->setVisible(false);

    QToolBar * bar = addToolBar("actions");

    setCentralWidget(mView);

    mSearchbar->setMaximumWidth(200);
    mSearchbar->setPlaceholderText("Sequence ...");

    QAction * openAction = bar->addAction("Open");
    QWidget * spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    bar->addWidget(spacer);
    bar->addWidget(mSearchbar);

    mYSlider->setRange(1,1000);
    mXSlider->setRange(1,1000);
    mXSlider->setToolTip("Scale");

    mXSlider->setMaximumWidth(100);
    mYSlider->setMaximumWidth(100);
    mYSlider->setValue(0.2);
    mYSlider->setToolTip("Amplitude");

    QStatusBar * statusBar = new QStatusBar;

    statusBar->addPermanentWidget(new QLabel("Scale"));
    statusBar->addPermanentWidget(mXSlider);
    statusBar->addPermanentWidget(new QLabel("Amplitude"));
    statusBar->addPermanentWidget(mYSlider);
    setStatusBar(statusBar);

    connect(mYSlider, &QSlider::valueChanged, [=](){mView->setAmplitudeFactor(mYSlider->value() / 1000.0 );});
    connect(mXSlider, &QSlider::valueChanged, [=](){mView->setScaleFactor(mXSlider->value() / 100.0);});
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    resize(1000, 400);
}

MainWindow::~MainWindow()
{

}



void MainWindow::openFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath());
    setFilename(file);

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
}

void MainWindow::writeSettings()
{

}

void MainWindow::restoreSettings()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

        QSvgGenerator generator;
        generator.setFileName("/tmp/capture.svg");
        generator.setTitle("test");
        generator.setDescription("description");
        render(&generator);


    return QMainWindow::keyPressEvent(event);

}
