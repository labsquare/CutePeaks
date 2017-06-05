#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "TraceView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Overriden methods
    void closeEvent(QCloseEvent*);

public Q_SLOTS:
    void openFile();
    void setFilename(const QString& filename);
    void writeSettings();
    void restoreSettings();


private:

    TraceView * mView;
    QSlider * mYSlider;
    QSlider * mXSlider;
    QString mFile;

};

#endif // MAINWINDOW_H
