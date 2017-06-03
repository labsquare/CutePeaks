#ifndef PEAKSWIDGET_H
#define PEAKSWIDGET_H
#include <QtWidgets>
#include <QDebug>
#include "abifreader.h"

class PeaksWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PeaksWidget(QWidget *parent = 0);
    void setFilename(const QString& filename);
public Q_SLOTS:
    void setAmplitudeFactor(int factor);
    void setScaleFactor(int factor);

   protected:
        void load();
        void draw();
        void paintEvent(QPaintEvent * event);


private:
    QString mFilename;

    // data
    QHash< QString, QVector<QPointF>> mLineSeries;
    int mXSize = 0; // max X
    int mYSize = 0; // max Y

    // draw
    QPixmap mPix;
    QList<QPainterPath> mPaths;

    // scaling
    float mYFactor = 0.2;
    float mXFactor = 1;

    // widget
    QLabel * mLabel;



};

#endif // PEAKSWIDGET_H
