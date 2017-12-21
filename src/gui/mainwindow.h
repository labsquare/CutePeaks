
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSvgGenerator>
#include <QGraphicsOpacityEffect>
#include <QUndoStack>
#include "cuttracecommand.h"
#include "traceview.h"
#include "sequenceview.h"
#include "infopanelwidget.h"
#include "abstractpanelwidget.h"
#include "aboutdialog.h"

#include "sequencepanelwidget.h"
#include "infopanelwidget.h"
#include "searchbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Overriden methods
    void closeEvent(QCloseEvent*);
    void keyPressEvent(QKeyEvent *event);

public Q_SLOTS:
    void openFile();
    void setFilename(const QString& filename);
    void writeSettings();
    void restoreSettings();
    void about();
    void setTransparent(bool active);

   // Trace actions
    void removeSelection();
    void exportFile();




protected Q_SLOTS:
    void updateSelection();
    void addPanel(AbstractPanelWidget * panel, Qt::DockWidgetArea area);


protected:
    void setupActions();


private:

    TraceView * mView;
    QSlider * mYSlider;
    QSlider * mXSlider;
    QString mFile;
    SearchBar * mSearchbar;
    QList<AbstractPanelWidget*> mPanels;
    QGraphicsOpacityEffect * mOpacityEffect = nullptr;

    QUndoStack * mUndoStack;

};

#endif // MAINWINDOW_H
