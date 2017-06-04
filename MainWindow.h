#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "peaksview.h"

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

    PeaksWidget * mView;
    QSlider * mYSlider;
    QSlider * mXSlider;
    QScrollBar * mScrollBar;
    QString mFile;

};

#endif // MAINWINDOW_H
