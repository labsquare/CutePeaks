#include "traceview.h"

TraceView::TraceView(QWidget *parent)
    :QAbstractScrollArea(parent)
{

    qDebug()<<"construct";

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    horizontalScrollBar()->setPageStep(10);
    horizontalScrollBar()->setRange(0,1000);

}

void TraceView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(viewport());
    // inverse y axis
    painter.translate(viewport()->rect().bottomLeft());
    painter.scale(1.0, -1.0);

    // draw background
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(viewport()->rect());

    // set antialiasing
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing, true);

    // loop over A,C,G,T
    QHash<QString,QColor>cols = {
                     {"DATA.9",QColor("#000000")},
                     {"DATA.10",QColor("#009000")},
                     {"DATA.11",QColor("#ff0000")},
                     {"DATA.12",QColor("#0000ff")}
    };


    auto i = mLineSeries.constBegin();
    int iColor = 0;
    while (i != mLineSeries.constEnd()) {

        // draw curves as path
        QPainterPath path;
        path.moveTo(0,0);
        QVector<QPointF> data = i.value();

        for ( int x = mXStart ; x < viewport()->rect().width() + mXStart; ++x)
        {
            if (x >= data.size())
                break;

            QPointF p = data[x];
            p.setX(p.x() - mXStart);
            path.lineTo((p.x()) * mXFactor , p.y() * mYFactor);

        }

        // draw path
        QPen pen;
        pen.setWidth(1);
        pen.setColor(cols[i.key()]);
        pen.setCosmetic(false);
        pen.setWidthF(1);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        painter.setBrush(Qt::transparent);
        painter.drawPath(path);
        ++i;
        ++iColor;
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

void TraceView::updateScrollbar()
{

    horizontalScrollBar()->setRange(0, mXSize - viewport()->width());
    horizontalScrollBar()->setPageStep(viewport()->width()/ mXFactor);

    qDebug()<<mXSize;
}

void TraceView::setFilename(const QString &filename)
{
    mFilename = filename;
    load();
    viewport()->update();
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
    qDebug()<<"load";
    mLineSeries.clear();
    // load data ===================
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
            QVector<QPointF> serie;
            // get data according key
            QVariantList datas = reader.data(key).toList();

            // fill serie with x,y values
            for (int i=0; i<datas.length(); ++i) {
                serie.append(QPointF(i, datas[i].toInt()));
                mYSize = qMax(mYSize,  datas[i].toInt());
            }
            mXSize = datas.length();
            // add serie in the chart
            mLineSeries[key] = serie;
        }
    }

    updateScrollbar();


}

