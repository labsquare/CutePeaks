#include "PeaksView.h"

PeaksView::PeaksView(QWidget * parent)
    :QWidget(parent)
{

    mView      = new QChartView;
    mChart     = new QChart;
    mScrollBar = new QScrollBar(Qt::Horizontal);

    mView->setChart(mChart);

    //enable zoom mouse selection
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
    //This methods is trigger during zoom mouse action

//    qDebug()<<min<<" "<<max;

}

void PeaksView::scrollChanged(int v)
{
    //this methods is triggered by the scrollbar
    int d = ax->min() - v;

    mChart->scroll(1,0);

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

    mScrollBar->setMinimum(0);
    mScrollBar->setMaximum(reader.data("DATA.1").toList().count());

    // Create defaut axis X and Y
    mChart->createDefaultAxes();

    // store axisX pointer as class member
    ax = qobject_cast<QValueAxis*>(mChart->axisX());

    // set a defaut range to sanger plot readable
    ax->setRange(0,500);


    // connect axis scale changed to class methods
    connect(ax, SIGNAL(rangeChanged(qreal,qreal)),this,SLOT(rangeChanged(qreal,qreal)));

    // connect scrollbar to class methods
    connect(mScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollChanged(int)));

}
