
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSvgGenerator>
#include "TraceView.h"
#include "sequenceview.h"
#include "InfoView.h"

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

protected:
    void addDock(QWidget * widget);

private:

    TraceView * mView;
    QSlider * mYSlider;
    QSlider * mXSlider;
    QString mFile;
    QLineEdit * mSearchbar;
    SequenceView * mSeqView;


};

#endif // MAINWINDOW_H
