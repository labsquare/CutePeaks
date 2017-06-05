#include "TraceView.h"

TraceView::TraceView(QWidget *parent)
    :QAbstractScrollArea(parent)
{

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);

    mTraceColors = {
        {'A',"#009000"},    // green
        {'C',"#0000ff"},    // blue
        {'G',"#000000"},    // black
        {'T',"#ff0000"},    // red
        {'W',"#804800"},    // mix of A and T
        {'S',"#000080"},    // mix of C and G
        {'M',"#004880"},    // mix of A and C
        {'K',"#800000"},    // mix of G and T
        {'R',"#004800"},    // mix of A and G
        {'Y',"#800080"},    // mix of C and T
        {'B',"#550055"},    // mix of C, G, and T
        {'D',"#553000"},    // mix of A, G, and T
        {'H',"#553055"},    // mix of A, C, and T
        {'V',"#003055"},    // mix of A, C, and G
        {'N',"#999"}        // gray
    };

}

void TraceView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!mSequenceTrace)
        return;

    QPainter painter(viewport());


    // draw bases



    // inverse y axis


    // draw background
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(viewport()->rect());

    // set antialiasing
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing, true);


    // draw base
    int yMargin = 40;

    for (int i = 0 ; i < mSequenceTrace->baseLocations().length(); ++i)
    {
        int pos = mSequenceTrace->baseLocations().at(i);

        if (pos >= mXStart && pos <=  viewport()->rect().width() + mXStart )
        {
            QPointF p ((pos - mXStart) * mXFactor, 15);

            // Draw Base
            QChar base = mSequenceTrace->baseCalls().at(i);
            QFontMetrics metrics(painter.font());
            QPointF textPos (p.x() - metrics.width(base)/2, p.y());
            textPos.setY(viewport()->height() - yMargin + 20);
            painter.setPen(QPen(mTraceColors[base]));
            painter.drawText(textPos, QString(base));
        }


    }



    painter.translate(viewport()->rect().bottomLeft());
    painter.scale(1.0, -1.0);
    // Draw traces
    for (QChar base : mSequenceTrace->bases())
    {

        // load paths to draw
        QPainterPath path;
        path.moveTo(0,0);
        QVector<int> data = mSequenceTrace->traces(base);

        for ( int x = mXStart ; x < viewport()->rect().width() + mXStart; ++x)
        {
            if (x >= data.size())
                break;

            QPointF p ( x - mXStart, data[x]);
            path.lineTo((p.x()) * mXFactor , p.y() * mYFactor + yMargin);

        }

        // draw path
        QPen pen;
        pen.setWidth(1);
        pen.setColor(mTraceColors[base]);
        pen.setCosmetic(false);
        pen.setWidthF(1);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        painter.setBrush(Qt::transparent);
        painter.drawPath(path);





    }

}

void TraceView::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dy)
    mXStart -= dx ;
    viewport()->update();
}

void TraceView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    updateScrollbar();
}

void TraceView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        qDebug()<< event->x();
    }
}

bool TraceView::viewportEvent(QEvent *event)
{


    return QAbstractScrollArea::viewportEvent(event);
}

void TraceView::updateScrollbar()
{
    int maxXSize = mSequenceTrace->traceLength();
    horizontalScrollBar()->setRange(0, maxXSize - viewport()->width());
    horizontalScrollBar()->setPageStep(viewport()->width()/ mXFactor);
}

void TraceView::setFilename(const QString &filename)
{
    mFilename = filename;
    mSequenceTrace = SequenceTraceFactory::loadTraceFile(filename);

    if (!mSequenceTrace){
        qCritical()<<Q_FUNC_INFO<<"Cannot read the file";
        return ;
    }


    viewport()->update();
    updateScrollbar();


}

void TraceView::setAmplitudeFactor(float factor)
{
    mYFactor = factor;
    viewport()->update();
    updateScrollbar();
}

void TraceView::setScaleFactor(float factor)
{
    mXFactor = factor;
    viewport()->update();
    updateScrollbar();
}

void TraceView::load()
{
    //    qDebug()<<"load";
    //    mLineSeries.clear();
    //    // load data ===================
    //    AbifReader reader(mFilename);


    //    // loop over 4 series A,C,T,G
    //    for (int i=9; i<=12 ; ++i)
    //    {
    //        // create DATA.x key
    //        QString key = QString("DATA.%1").arg(i);


    //        // if key exists in ab1 file
    //        if (reader.directoryKeys().contains(key))
    //        {
    //            // create a line serie
    //            QVector<QPointF> serie;
    //            // get data according key
    //            QVariantList datas = reader.data(key).toList();

    //            // fill serie with x,y values
    //            for (int i=0; i<datas.length(); ++i) {
    //                serie.append(QPointF(i, datas[i].toInt()));
    //                mYSize = qMax(mYSize,  datas[i].toInt());
    //            }
    //            mXSize = datas.length();
    //            // add serie in the chart
    //            mLineSeries[key] = serie;
    //        }
    //    }

    //    updateScrollbar();


}

