#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mView        = new TraceView;
    mYSlider     = new QSlider(Qt::Horizontal);
    mXSlider     = new QSlider(Qt::Horizontal);
    mSearchbar   = new QLineEdit;


    setCentralWidget(mView);


    SequencePanelWidget * panel = new SequencePanelWidget;

    connect(panel, SIGNAL(selectionChanged(int,int)), mView, SLOT(setSelection(int,int)));


    addPanel(panel, Qt::BottomDockWidgetArea);
    addPanel(new InfoPanelWidget, Qt::LeftDockWidgetArea);


    mSearchbar->setMaximumWidth(200);
    mSearchbar->setPlaceholderText(tr("Sequence..."));
    mSearchbar->setVisible(false);


    mYSlider->setRange(6,1000);
    mXSlider->setRange(10,1000);
    mXSlider->setToolTip(tr("Scale"));

    mXSlider->setMaximumWidth(100);
    mYSlider->setMaximumWidth(100);
    mYSlider->setValue(0.2);
    mYSlider->setToolTip(tr("Amplitude"));

    QStatusBar * statusBar = new QStatusBar;

    statusBar->addPermanentWidget(new QLabel(tr("Scale")));
    statusBar->addPermanentWidget(mXSlider);
    statusBar->addPermanentWidget(new QLabel(tr("Amplitude")));
    statusBar->addPermanentWidget(mYSlider);
    setStatusBar(statusBar);


    connect(mYSlider, &QSlider::valueChanged, [=](){mView->setAmplitudeFactor(mYSlider->value() / 1000.0 );});
    connect(mXSlider, &QSlider::valueChanged, [=](){mView->setScaleFactor(mXSlider->value() / 100.0);});
    //    connect(mSeqView, &SequenceView::selectionChanged, this, &MainWindow::updateSelection);

    setupActions();

    resize(1000, 400);
    setWindowIcon(QIcon("qrc:/icons/cutepeaks.png"));
    restoreSettings();
}

MainWindow::~MainWindow()
{

}



void MainWindow::openFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
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
                panel->setTrace(mView->trace());

            QFileInfo info(filename);
            setWindowTitle(info.fileName());
        }
        else
        {
            QMessageBox::critical(this,tr("Error reading"),tr("Cannot read file"));
        }

    }
    else
        QMessageBox::warning(this,tr("Error"),tr("Cannot find file ") + filename);


//    mView->toPng("/tmp/cutepeaks.png");
//    mView->toSvg("/tmp/cutepeaks.svg");


}


void MainWindow::closeEvent(QCloseEvent *)
{
    writeSettings();
}

void MainWindow::writeSettings()
{

    QSettings settings;
    settings.setValue("size", rect().size());
    settings.setValue("pos", pos());


}

void MainWindow::restoreSettings()
{

    QSettings settings;
    resize(settings.value("size", QSize(800,400)).toSize());
    move(settings.value("pos").toPoint());

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
    //dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(area,dock);
    //mMetaDock->setVisible(false);
}

void MainWindow::setupActions()
{
    QMenuBar * bar = new QMenuBar;
    setMenuBar(bar);

    QMenu * openMenu = bar->addMenu(tr("&File"));
    openMenu->addAction(tr("&Open"), this, SLOT(openFile()), QKeySequence::Open);
    openMenu->addAction(tr("Quit"), qApp, SLOT(quit()));

 //   QMenu * viewMenu = bar->addMenu(tr("&View"));
//    QAction * viewMetaAction = viewMenu->addAction(tr("&Show metadata"), mMetaDock, SLOT(setVisible(bool)));
//    viewMetaAction->setCheckable(true);
//    viewMetaAction->setChecked(false);



    QMenu * helpMenu = bar->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
    helpMenu->addAction(tr("About Qt"), qApp, SLOT(aboutQt()));



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
