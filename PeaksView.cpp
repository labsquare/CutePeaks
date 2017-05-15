#include "PeaksView.h"

PeaksView::PeaksView(QWidget * parent)
    :QWidget(parent)
{

    mView      = new QChartView;
    mChart     = new QChart;
    mScrollBar = new QScrollBar(Qt::Horizontal);

    mA = new QSlider(Qt::Horizontal);
    mB = new QSlider(Qt::Horizontal);


    mView->setChart(mChart);

    //enable zoom mouse selection
    mView->setRubberBand( QChartView::HorizontalRubberBand);
    mChart->setBackgroundRoundness(0);
    QVBoxLayout * cLayout = new QVBoxLayout;

    QHBoxLayout * zLayout = new QHBoxLayout;
    zLayout->addWidget(mA);
    zLayout->addWidget(mB);

    cLayout->addLayout(zLayout);
    cLayout->addWidget(mView);
    cLayout->addWidget(mScrollBar);
    cLayout->setSpacing(0);

    setLayout(cLayout);
    setMaximumHeight(300);

    connect(mA,SIGNAL(valueChanged(int)),this,SLOT(ampliChanged(int)));
    connect(mB,SIGNAL(valueChanged(int)),this,SLOT(zoomChanged(int)));


}


void PeaksView::setFilename(const QString &filename)
{

    mFilename = filename;
    draw();

}

void PeaksView::rangeChanged(qreal min, qreal max)
{
    //This methods is trigger during zoom mouse action

    //    qDebug()<<min<<" "<<max;

}

void PeaksView::scrollChanged(int v)
{
    //this methods is triggered by the scrollbar
    //    int d = v- ax->min();

    qDebug()<<"scroll changed";
    qDebug()<<mChart->rect().width();


       int zoomFactor = ax->max()- ax->min();
       ax->setMin(v);
       ax->setMax(v+zoomFactor);


}

void PeaksView::ampliChanged(int v)
{
    qDebug()<<"ampli "<<v;
    ay->setMax(v*50);
}

void PeaksView::zoomChanged(int v)
{
    qDebug()<<"zoom "<<v;
}

void PeaksView::draw()
{
    // remove old series
    mChart->removeAllSeries();

    // parse ab1 file
    AbifReader reader(mFilename);


    // loop over 4 series A,C,T,G
    for (int i=9; i<=12 ; ++i)
    {
        // create DATA.x key
        QString key = QString("DATA.%1").arg(i);


        // if key exists in ab1 file
        if (reader.directoryKeys().contains(key))
        {
            // create a line serie
            QLineSeries * serie = new QLineSeries;
            // get data according key
            QVariantList datas = reader.data(key).toList();

            // fill serie with x,y values
            for (int i=0; i<datas.length(); ++i)
                serie->append(i, datas[i].toInt());

            // add serie in the chart
            mChart->addSeries(serie);

        }

    }

    QLineSeries * s  = qobject_cast<QLineSeries*>(mChart->series().first());



    // Create defaut axis X and Y
    mChart->createDefaultAxes();

    // store axisX pointer as class member
    ax = qobject_cast<QValueAxis*>(mChart->axisX());
    ay = qobject_cast<QValueAxis*>(mChart->axisY());
    ay->hide();

    // set a defaut range to sanger plot readable
    ax->setRange(0,200);




    mScrollBar->setMinimum(0);
    mScrollBar->setMaximum(s->points().size());
    mScrollBar->setPageStep(1000);


    // connect axis scale changed to class methods
    connect(ax, SIGNAL(rangeChanged(qreal,qreal)),this,SLOT(rangeChanged(qreal,qreal)));

    // connect scrollbar to class methods
    connect(mScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollChanged(int)));

}
