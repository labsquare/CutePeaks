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


    for (QString k : reader.directoryKeys())
    {
        if (reader.data(k).type() == QVariant::List)
        {
            qDebug()<<k<<" "<<reader.data(k).toList().size()<<" "<<reader.data(k).toList().mid(0,5);
        }

        else
            qDebug()<<k<<" "<<reader.data(k);

        if (reader.data(k).type() == QVariant::String)
        {
            qDebug()<<reader.data(k).toString().size();
        }



    }


    // AB1 SPECIFICATION TO UNDERSTAND KEY
    // get A,C,G,T signals
    for (int i=9; i<=12 ; ++i)
    {
        QString key = QString("DATA.%1").arg(i);





        if (reader.directoryKeys().contains(key))
        {
            QLineSeries * serie = new QLineSeries;
            QScatterSeries * test = new QScatterSeries;

            QVariantList datas = reader.data(key).toList();

            QVariantList peaks = reader.data("PLOC.1").toList();
            QString text = reader.data("PBAS.1").toString();


            qDebug()<<"last "<<peaks.last();




            for (int i=0; i<datas.length(); ++i)
                serie->append(i, datas[i].toInt());

            for (int i=0; i<peaks.length(); ++i){
                test->append(peaks[i].toInt(),1000 );

            }





            chart()->addSeries(serie);
            chart()->addSeries(test);
        }

    }


    chart()->createDefaultAxes();
    QValueAxis * ax = qobject_cast<QValueAxis*>(chart()->axisX());
    ax->setRange(1500,2000);



}
