#ifndef PEAKSVIEW_H
#define PEAKSVIEW_H
#include <QtCharts>
#include "abifreader.h"

using namespace QT_CHARTS_NAMESPACE;

class PeaksView : public QChartView
{
    Q_OBJECT
public:
    PeaksView(QWidget * parent = Q_NULLPTR);

public Q_SLOTS:
    void setFilename(const QString& filename);

protected:
    void draw();


private:
    QString mFilename;
    QList<QLineSeries*> mSeries;
    QChart * mChart;


};

#endif // PEAKSVIEW_H
