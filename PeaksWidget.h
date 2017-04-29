#ifndef PEAKSWIDGET_H
#define PEAKSWIDGET_H
#include <QtWidgets>
#include "abifreader.h"

class PeaksWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit PeaksWidget(QWidget *parent = 0);


    void draw();

private:
    QPixmap pix;



};

#endif // PEAKSWIDGET_H
