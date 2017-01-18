#include "PeaksView.h"

PeaksView::PeaksView(QWidget * parent)
    :QChartView(parent)
{

    setChart(new QChart);



   // setDragMode(QGraphicsView::RubberBandDrag);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setRubberBand( QChartView::HorizontalRubberBand);

    chart()->resize(2000,100);
}

void PeaksView::setFilename(const QString &filename)
{

    mFilename = filename;

    draw();

}

void PeaksView::draw()
{
    chart()->removeAllSeries();
    mSeries.clear();

    AbifReader reader(mFilename);

    // get A,C,G,T signals
    for (int i=0; i<=4 ; ++i)
    {
        QString key = QString("DATA.%1").arg(i);
        if (reader.directoryKeys().contains(key))
        {
            QLineSeries * serie = new QLineSeries;

            QVariantList datas = reader.data(key).toList();

            for (int i=0; i<datas.length(); ++i)
                serie->append(i, datas[i].toInt());


            chart()->addSeries(serie);
        }

    }


    chart()->createDefaultAxes();
    QValueAxis * ax = qobject_cast<QValueAxis*>(chart()->axisX());
    ax->setRange(1500,2000);



}
