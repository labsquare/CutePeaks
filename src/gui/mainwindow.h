
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSvgGenerator>
#include <QDesktopServices>
#include <QGraphicsOpacityEffect>
#include <QUndoStack>
#include "cuttracecommand.h"
#include "traceview.h"
#include "sequenceview.h"
#include "infopanelwidget.h"
#include "abstractpanelwidget.h"
#include "aboutdialog.h"
#include "updatedialog.h"

#include "sequencepanelwidget.h"
#include "infopanelwidget.h"
#include "searchbar.h"

class TraceView;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TraceView *view() const;

    SequencePanelWidget *panel() const;

public Q_SLOTS:
    void openFile();
    void setFilename(const QString& filename);
    void writeSettings();
    void restoreSettings();
    void about();
    void setTransparent(bool active);

   // Trace actions
    void removeSelection();
    void revert();
    void exportFile();


protected Q_SLOTS:
    void updateSelection();
    void addPanel(AbstractPanelWidget * panel, Qt::DockWidgetArea area);

    void showSelection(int pos, int length);
    void showUpdater();

    void setActionAvaible(bool avaible);

    void saveRecentFile(const QUrl& url);
    QList<QUrl> recentFiles() const;

Q_SIGNALS:
    void fileChanged(bool valid);

protected:
    void setupActions();
    // Overriden methods
    void closeEvent(QCloseEvent*);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent * event);

private:

    TraceView * mView;
    QSlider * mYSlider;
    QSlider * mXSlider;
    QString mFile;
    SearchBar * mSearchbar;
    QList<AbstractPanelWidget*> mPanels;
    QGraphicsOpacityEffect * mOpacityEffect = nullptr;
    SequencePanelWidget * mPanel;
    QUndoStack * mUndoStack;

};

#endif // MAINWINDOW_H
