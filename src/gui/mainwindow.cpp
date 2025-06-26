#include "mainwindow.h"
#include "qfonticon.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mView        = new TraceView;
    mYSlider     = new QSlider(Qt::Horizontal);
    mXSlider     = new QSlider(Qt::Horizontal);
    mSearchbar   = new SearchBar();
    mUndoStack   = new QUndoStack(this);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mView);
    mainLayout->addWidget(mSearchbar);

    QWidget * mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);

    mPanel = new SequencePanelWidget;

    connect(mPanel, SIGNAL(selectionChanged(int,int)), mView, SLOT(setSelection(int,int)));

    connect(mView, SIGNAL(selectionChanged(int,int)), this, SLOT(showSelection(int,int)));
    //    connect(mSearchbar, &QLineEdit::returnPressed, [this](){

    //        QRegularExpression exp(mSearchbar->text().toUpper());
    //        QRegularExpressionMatch m = exp.match(mView->trace()->sequence().byteArray());
    //        if (m.hasMatch())
    //            mView->setSelection(m.capturedStart(), m.capturedLength());

    //    });

    setDockOptions(QMainWindow::ForceTabbedDocks|QMainWindow::AllowTabbedDocks);

    addPanel(mPanel, Qt::LeftDockWidgetArea);
    addPanel(new InfoPanelWidget, Qt::LeftDockWidgetArea);


    mYSlider->setRange(6,1000);
    mXSlider->setRange(10,1000);
    mXSlider->setToolTip(tr("Scale"));

    mXSlider->setMaximumWidth(100);
    mYSlider->setMaximumWidth(100);
    mYSlider->setValue(0);
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

    setAcceptDrops(true);


    resize(1000, 400);
    setWindowIcon(QIcon("qrc:/icons/cutepeaks.png"));
    restoreSettings();

    mSearchbar->hide();
    connect(mSearchbar, &SearchBar::previousPressed, mView, &TraceView::selectPreviousSearch);
    connect(mSearchbar, &SearchBar::nextPressed, mView, &TraceView::selectNextSearch);
    connect(mSearchbar, &SearchBar::textChanged, mView, &TraceView::search);
    connect(mView, &TraceView::matchCountChanged, mSearchbar, &SearchBar::setMatchCount);

    // disable action with empty file
    emit fileChanged(false);


}

MainWindow::~MainWindow()
{

}



void MainWindow::openFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    setFilename(file);

}

void MainWindow::setFilename(const QString &filename)
{
    mFile = filename;

    if (filename.isEmpty()) {
        setWindowTitle("Cutepeaks");
        return;
    }

    if (QFile::exists(filename)){
        mView->setFilename(filename);
        if (mView->isValid())
        {
            for (AbstractPanelWidget * panel : mPanels)
                panel->setTrace(mView->trace());

            QFileInfo info(filename);
            setWindowTitle(info.fileName());

            mXSlider->setValue(mView->xFactor() * 100);
            mYSlider->setValue(mView->yFactor() * 1000);

            saveRecentFile(QUrl::fromLocalFile(filename));

            emit fileChanged(true);

        }
        else
        {
            QMessageBox::critical(this,tr("Error reading."),tr("Cannot read file!"));
        }

    }
    else
        QMessageBox::warning(this,tr("Error."),tr("Cannot find file ") + filename);


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

void MainWindow::setTransparent(bool active)
{
    setWindowOpacity(active == 1.0 ? 0.6 : 1.0);
}

void MainWindow::removeSelection()
{

    if (mView->isValid())
        mUndoStack->push(new CutTraceCommand(this,
                                             mView->currentSelection().pos,
                                             mView->currentSelection().length));
}

void MainWindow::revert()
{
    if (mView->isValid())
    {
        mView->revert();
        mPanel->setText(mView->trace()->sequence().toString());
    }
}

void MainWindow::exportFile()
{
    QAction * action = qobject_cast<QAction*>(sender());
    QString format = action->property("format").toString();
    if (format.isEmpty())
        return;

    QString filename = QFileDialog::getSaveFileName(this,"save as "+format,QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));

    if (filename.isEmpty())
        return;

    if (format == "PNG")
        mView->toPng(filename);

    if (format == "SVG")
        mView->toSvg(filename);

    if (format == "CSV")
        mView->toCsv(filename);

    if (format == "DNA")
        mView->toFasta(filename, Sequence::Dna);

    if (format == "PROTEIN")
        mView->toFasta(filename, Sequence::Protein);

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
    panel->setParent(dock);
    dock->setVisible(false);

    if (!mPanels.isEmpty())
    {
        tabifyDockWidget(dock,qobject_cast<QDockWidget*>(mPanels.first()->parent()));
    }

}

void MainWindow::showSelection(int pos, int length)
{
    if (mView->matchCount() == 0 )
        statusBar()->showMessage(QString("position: %1 length: %2").arg(pos).arg(length));
    else
        statusBar()->showMessage(QString("position: %1 length: %2 match: %3").arg(pos).arg(length).arg(mView->matchCount()));

}

void MainWindow::showUpdater()
{
    UpdateDialog dialog;
    dialog.exec();
}

void MainWindow::setActionAvaible(bool /*avaible*/)
{

}

void MainWindow::saveRecentFile(const QUrl &url)
{
    QSettings settings;
    QList<QUrl> listUrl = recentFiles();

    if (listUrl.contains(url))
        return;

    listUrl.prepend(url);
    settings.beginWriteArray("recents");

    int size = qMin(listUrl.size(), 10);

    for (int i=0 ; i<size; ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("url", listUrl[i]);
    }

    settings.endArray();
}

QList<QUrl> MainWindow::recentFiles() const
{
    QSettings settings;
    QList<QUrl> urls;

    int size = settings.beginReadArray("recents");

    for (int i=0 ; i<size; ++i)
    {
        settings.setArrayIndex(i);
        urls.append(settings.value("url").toUrl());
    }
    settings.endArray();
    return urls ;
}

void MainWindow::setupActions()
{
    QMenuBar * bar = new QMenuBar;
    setMenuBar(bar);

    // Create app menus
    // file Menu
    QMenu * fileMenu       = bar->addMenu(tr("&File"));
    //    QAction * openAction   =
    fileMenu->addAction(FIcon(0xf115),tr("&Open"), this, SLOT(openFile()), QKeySequence::Open);
    //    QAction * saveAction   =

    // fichier recents
    if (!recentFiles().isEmpty())
    {
        QAction * recentAction = fileMenu->addAction(tr("Recent Files"));
        recentAction->setMenu(new QMenu);
        for (const QUrl& url : recentFiles())
            recentAction->menu()->addAction(url.toString(QUrl::PreferLocalFile), [this,url](){setFilename(url.toLocalFile());});
    }

    // TODO : file saving
    //fileMenu->addAction(FIcon(0xf0c7),tr("&Save"), this, SLOT(openFile()), QKeySequence::Save);
    QAction * exportAction = fileMenu->addAction(tr("Export As"));
    exportAction->setMenu(new QMenu);
    QAction * exportPng    = exportAction->menu()->addAction(FIcon(0xf1c5),tr("PNG Image"),this,SLOT(exportFile()));
    QAction * exportSvg    = exportAction->menu()->addAction(FIcon(0xf1c5),tr("SVG Image"),this,SLOT(exportFile()));
    QAction * exportCsv    = exportAction->menu()->addAction(FIcon(0xf0f6),tr("CSV Dataset"),this,SLOT(exportFile()));
    QAction * exportDna    = exportAction->menu()->addAction(FIcon(0xf0f6),tr("FASTA DNA"),this,SLOT(exportFile()));
    QAction * exportProtein= exportAction->menu()->addAction(FIcon(0xf0f6),tr("FASTA Protein"),this,SLOT(exportFile()));

    exportPng->setProperty("format", "PNG");
    exportSvg->setProperty("format", "SVG");
    exportCsv->setProperty("format", "CSV");
    exportDna->setProperty("format", "DNA");
    exportProtein->setProperty("format", "PROTEIN");

    fileMenu->addSeparator();
    fileMenu->addAction(FIcon(0xf00d), tr("Close"), qApp, SLOT(closeAllWindows()));

    // disable export if no file
    connect(this, &MainWindow::fileChanged, exportAction, &QAction::setEnabled);

    // edit Menu
    QMenu * editMenu       = bar->addMenu(tr("&Edit"));

    QAction * undoAction = mUndoStack->createUndoAction(this,"Undo");
    QAction * redoAction = mUndoStack->createRedoAction(this,"Redo");

    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setIcon(FIcon(0xf0e2));
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setIcon(FIcon(0xf01e));

    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    editMenu->addSeparator();
    editMenu->addAction(FIcon(0xf0c5),tr("Copy Selection"), mView, SLOT(copySequence()),QKeySequence::Copy);
    editMenu->addSeparator();
    editMenu->addAction(tr("Select All"), mView,SLOT(selectAll()), QKeySequence::SelectAll);
    editMenu->addSeparator();
    //    QAction * remAction =
    editMenu->addAction(FIcon(0xf0c4),tr("Remove Selection"),this,SLOT(removeSelection()),QKeySequence::Delete);
    //    QAction * revAction =
    editMenu->addAction(FIcon(0xf0ec),tr("Revert Sequence"), this,SLOT(revert()),  QKeySequence(Qt::CTRL + Qt::Key_I));
    editMenu->addSeparator();
    QActionGroup * frameGroup = new QActionGroup(this);
    frameGroup->addAction(editMenu->addAction("Frame 1",[this](){mView->setFrameShift(Sequence::Frame1);},QKeySequence(Qt::CTRL + Qt::Key_1)));
    frameGroup->addAction(editMenu->addAction("Frame 2",[this](){mView->setFrameShift(Sequence::Frame2);},QKeySequence(Qt::CTRL + Qt::Key_2)));
    frameGroup->addAction(editMenu->addAction("Frame 3",[this](){mView->setFrameShift(Sequence::Frame3);},QKeySequence(Qt::CTRL + Qt::Key_3)));;
    editMenu->addSeparator();

    frameGroup->setExclusive(true);
    for (auto a : frameGroup->actions())
        a->setCheckable(true);

    frameGroup->actions().first()->setChecked(true);


    editMenu->addSeparator();
    QAction * findAction = mSearchbar->createSearchAction("Find Sequence");
    findAction->setShortcut(QKeySequence::Find);
    findAction->setIcon(FIcon(0xf002));
    editMenu->addAction(findAction);



    // disable edit menu if no file
    connect(this, &MainWindow::fileChanged, editMenu, &QMenu::setEnabled);
    // disable edit actions ..
    for (QAction * a : editMenu->actions())
        connect(this, &MainWindow::fileChanged, a, &QAction::setEnabled);



    // view Menu
    QMenu * viewMenu             = bar->addMenu(tr("&View"));
    QAction * showQualAction     = viewMenu->addAction(tr("Show Quality"));
    QAction * showAminoAction    = viewMenu->addAction(tr("Show Amino Acid"));
    showQualAction->setCheckable(true);
    showAminoAction->setCheckable(true);

    showQualAction->setChecked(true);
    showAminoAction->setChecked(true);

    connect(showQualAction, &QAction::triggered, mView, &TraceView::showQuality);
    connect(showAminoAction, &QAction::triggered, mView, &TraceView::showAminoAcid);
    viewMenu->addSeparator();

    for (auto panel : mPanels)
    {
        auto dock = qobject_cast<QDockWidget*>(panel->parent());
        viewMenu->addAction(dock->toggleViewAction());
    }

    showQualAction->setCheckable(true);
    showAminoAction->setCheckable(true);
    viewMenu->addSeparator();

    QAction * transpAction = viewMenu->addAction("Window Transparency");
    transpAction->setCheckable(true);
    connect(transpAction, &QAction::triggered, this, &MainWindow::setTransparent);

    // disable view menu if no file
    connect(this, &MainWindow::fileChanged, viewMenu, &QMenu::setEnabled);


    QMenu * helpMenu = bar->addMenu(tr("&Help"));
    helpMenu->addAction(tr("Check Update"),this, SLOT(showUpdater()));
    helpMenu->addAction(tr("Open Issue"), [](){QDesktopServices::openUrl(QUrl("https://github.com/labsquare/CutePeaks/issues/new"));});
    helpMenu->addSeparator();
    helpMenu->addAction(tr("Join Labsquare"), [](){QDesktopServices::openUrl(QUrl("http://www.labsquare.org"));});
    helpMenu->addAction(tr("Donate"), [](){QDesktopServices::openUrl(QUrl("http://www.labsquare.org"));});
    helpMenu->addSeparator();
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

void MainWindow::wheelEvent(QWheelEvent *event)
{

    if (mView->rect().contains(event->pos()))
    {
        int factor = 1;
        if (event->modifiers() == Qt::ControlModifier)
            factor = 6;

        auto scale = mXSlider->value() + factor * event->delta()/120;

        mXSlider->setValue(scale);
    }

}

SequencePanelWidget *MainWindow::panel() const
{
    return mPanel;
}

TraceView *MainWindow::view() const
{
    return mView;
}
