#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mView        = new TraceView;
    mYSlider     = new QSlider(Qt::Horizontal);
    mXSlider     = new QSlider(Qt::Horizontal);
    mSearchbar   = new QLineEdit;


    setCentralWidget(mView);

    //    addPanel(new SequencePanelWidget, Qt::BottomDockWidgetArea);
    addPanel(new InfoPanelWidget, Qt::LeftDockWidgetArea);


    mSearchbar->setMaximumWidth(200);
    mSearchbar->setPlaceholderText("Sequence ...");
    mSearchbar->setVisible(false);


    mYSlider->setRange(6,1000);
    mXSlider->setRange(10,1000);
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
    //    connect(mSeqView, &SequenceView::selectionChanged, this, &MainWindow::updateSelection);

    setupActions();

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

    if (QFile::exists(filename)){
        mView->setFilename(filename);
        if (mView->isValid())
        {
            for (AbstractPanelWidget * panel : mPanels)
                panel->setTrace(mView->sequenceTrace());

            QFileInfo info(filename);
            setWindowTitle(info.fileName());


        }

    }
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

void MainWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::updateSelection()
{

    //    QTextCursor cursor = mSeqView->textCursor();
    //    if (cursor.hasSelection())
    //    {
    //        int start  = cursor.selectionStart();
    //        int length = cursor.selectionEnd() + start;

    //        mView->setSelection(start, length);
    //    }


}

void MainWindow::addPanel(AbstractPanelWidget *panel, Qt::DockWidgetArea area)
{

    mPanels.append(panel);
    QDockWidget * dock = new QDockWidget;
    dock->setWidget(panel);
    dock->setWindowTitle(panel->windowTitle());
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(area,dock);
}

void MainWindow::setupActions()
{
    QMenuBar * bar = new QMenuBar;
    setMenuBar(bar);

    QMenu * openMenu = bar->addMenu("&File");
    openMenu->addAction("&Open", this, SLOT(openFile()), QKeySequence::Open);
    openMenu->addAction("Quit", qApp, SLOT(quit()));

    QMenu * helpMenu = bar->addMenu("&Help");
    helpMenu->addAction("&About", this, SLOT(about()));
    helpMenu->addAction("About Qt", qApp, SLOT(aboutQt()));



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
