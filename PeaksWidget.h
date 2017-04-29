#ifndef PEAKSWIDGET_H
#define PEAKSWIDGET_H
#include <QtWidgets>
#include <QDebug>
#include "abifreader.h"

class PeaksWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit PeaksWidget(QWidget *parent = 0);

    void load();


private:
    QPixmap pix;
    QHash< QString, QList<QPointF>> mLineSeries;
    QLabel * mLabel;



};

#endif // PEAKSWIDGET_H
