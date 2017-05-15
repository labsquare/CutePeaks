#ifndef PEAKSVIEW_H
#define PEAKSVIEW_H
#include <QtCharts>
#include "abifreader.h"

using namespace QT_CHARTS_NAMESPACE;

class PeaksView : public QWidget
{
    Q_OBJECT
public:
    PeaksView(QWidget * parent = Q_NULLPTR);

public Q_SLOTS:
    void setFilename(const QString& filename);

    void rangeChanged(qreal min, qreal max);
    void scrollChanged(int v);

    void ampliChanged(int v);
    void zoomChanged(int v);

protected:
    void draw();


private:
    QString mFilename;
    QList<QLineSeries*> mSeries;
    QChart * mChart;
    QChartView * mView;
    QScrollBar * mScrollBar;
    QValueAxis * ax ;
    QValueAxis * ay ;

    bool scrolling = false;
    int sv = 0;
    QSlider * mA;
    QSlider * mB;



};

#endif // PEAKSVIEW_H
