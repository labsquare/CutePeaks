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

protected:
    void draw();


private:
    QString mFilename;
    QList<QLineSeries*> mSeries;
    QChart * mChart;
    QChartView * mView;
    QScrollBar * mScrollBar;
    QValueAxis * ax ;
    bool scrolling = false;
    int sv = 0;


};

#endif // PEAKSVIEW_H
