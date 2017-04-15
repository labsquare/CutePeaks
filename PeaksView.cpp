#include "PeaksView.h"

PeaksView::PeaksView(QWidget * parent)
    :QWidget(parent)
{

    mView      = new QChartView;
    mChart     = new QChart;
    mScrollBar = new QScrollBar(Qt::Horizontal);

    mView->setChart(mChart);

    // setDragMode(QGraphicsView::RubberBandDrag);
    mView->setRubberBand( QChartView::HorizontalRubberBand);
    mChart->setBackgroundRoundness(0);
    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mView);
    cLayout->addWidget(mScrollBar);
    cLayout->setSpacing(0);

    setLayout(cLayout);

    setMaximumHeight(300);

}


void PeaksView::setFilename(const QString &filename)
{

    mFilename = filename;

    draw();

}

void PeaksView::rangeChanged(qreal min, qreal max)
{
    if (scrolling) return;  // Scrolling causes range changes, but we don't have to do anything.

    QChart          *c = mChart;
    QAbstractAxis   *x = ax;
    qreal            avg = (min + max) / 2.0;
    bool             range_fixed = false;

    /*
        * Make sure the new range is sane; fix if not.
        */
    if ((max - min) < 0.1) {    // Avoid overzooming
        min = avg - 0.05;
        max = avg + 0.05;
        range_fixed = true;
    }

    if (min < 0.0) { min = 0.0; range_fixed = true; }

    if (max > 4.0) { max = 4.0; range_fixed = true; }

    if (range_fixed) {
        x->setRange( min, max );    // will re-signal with the fixed range
        return;
    }

    qreal    vis_width = c->plotArea( ).width( );
    qreal    all_width = vis_width * (4.0 - 0.0) / (max - min);

    //    cerr << "range " << min << " ... " << max << " in " << vis_width << " pixels" << endl;
    //    cerr << "full width requires " << all_width << " pixels" << endl;;

    if (max - min < 4.0) {
        //        cerr << "set scroll parameters" << endl;
        scrolling = true;
        mScrollBar->setMaximum( all_width - vis_width );
        sv = min / (4.0 - 0.0) * all_width;
        mScrollBar->setValue( sv );
        scrolling = false;
    } else {
        //        cerr << "disable scroll bar" << endl;
        scrolling = true;
        mScrollBar->setMaximum( 0 );
        mScrollBar->setValue( sv );
        scrolling = false;
    }

}

void PeaksView::scrollChanged(int v)
{
    if (!scrolling) {
          scrolling = true;
  //      cerr << "scroll " << v << endl;
          mChart->scroll( v - sv, 0 );
          sv = v;
          scrolling = false;
      }
}

void PeaksView::draw()
{
    mChart->removeAllSeries();
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





            mChart->addSeries(serie);
            mChart->addSeries(test);
        }

    }


    mChart->createDefaultAxes();
    ax = qobject_cast<QValueAxis*>(mChart->axisX());
    ax->setRange(1500,2000);


    connect(ax, SIGNAL(rangeChanged(qreal,qreal)),this,SLOT(rangeChanged(qreal,qreal)));
    connect(mScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollChanged(int)));

}
