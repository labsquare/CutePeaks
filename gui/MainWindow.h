
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSvgGenerator>
#include "TraceView.h"
#include "sequenceview.h"
#include "infopanelwidget.h"
#include "abstractpanelwidget.h"

#include "sequencepanelwidget.h"
#include "infopanelwidget.h"

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


protected Q_SLOTS:
    void updateSelection();
    void addPanel(AbstractPanelWidget * panel, Qt::DockWidgetArea area);


private:

    TraceView * mView;
    QSlider * mYSlider;
    QSlider * mXSlider;
    QString mFile;
    QLineEdit * mSearchbar;

    QList<AbstractPanelWidget*> mPanels;


};

#endif // MAINWINDOW_H
