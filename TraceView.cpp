#include "TraceView.h"

TraceView::TraceView(QWidget *parent)
    :QAbstractScrollArea(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
    QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);


    mTraceColors = {
        {'A',QColor("#009000")},    // green
        {'C',QColor("#0000ff")},    // blue
        {'G',QColor("#000000")},    // black
        {'T',QColor("#ff0000")},    // red
        {'W',QColor("#804800")},    // mix of A and T
        {'S',QColor("#000080")},    // mix of C and G
        {'M',QColor("#004880")},    // mix of A and C
        {'K',QColor("#800000")},    // mix of G and T
        {'R',QColor("#004800")},    // mix of A and G
        {'Y',QColor("#800080")},    // mix of C and T
        {'B',QColor("#550055")},    // mix of C, G, and T
        {'D',QColor("#553000")},    // mix of A, G, and T
        {'H',QColor("#553055")},    // mix of A, C, and T
        {'V',QColor("#003055")},    // mix of A, C, and G
        {'N',QColor("#999")}        // gray
    };

    setDisabled(true);
}
//-------------------------------------------------------------------------------

void TraceView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(viewport());
    // Draw empty background
    if (!mSequenceTrace){

        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));
        painter.drawRect(viewport()->rect());
        return;
    }


    // draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(viewport()->rect());

    // set antialiasing
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawBases(painter);
    drawTraces(painter);
    drawConfident(painter);
    drawSelection(painter);

}
//-------------------------------------------------------------------------------

void TraceView::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dy)
    mXStart -= dx ;
    viewport()->update();
}
//-------------------------------------------------------------------------------

void TraceView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    updateScrollbar();
}
//-------------------------------------------------------------------------------

void TraceView::mouseMoveEvent(QMouseEvent *event)
{
    QAbstractScrollArea::mouseMoveEvent(event);
}
//-------------------------------------------------------------------------------

bool TraceView::viewportEvent(QEvent *event)
{


    return QAbstractScrollArea::viewportEvent(event);
}
//-------------------------------------------------------------------------------

void TraceView::setupViewport()
{
    qDebug()<<"after";
    //    mScroller = QScroller::scroller(viewport());


}
//-------------------------------------------------------------------------------

bool TraceView::inView(int pos)
{
    return (pos >= mXStart && pos <= viewport()->rect().width()/mXFactor + mXStart);
}
//-------------------------------------------------------------------------------

void TraceView::updateScrollbar()
{
    if (!mSequenceTrace)
        return;

    int maxXSize = mSequenceTrace->traceLength();
    horizontalScrollBar()->setRange(0, maxXSize - viewport()->width()/mXFactor);
    horizontalScrollBar()->setPageStep(viewport()->width()/ mXFactor);
}
//-------------------------------------------------------------------------------

void TraceView::drawConfident(QPainter& painter)
{
    QPainterPath stepCurve;
    bool step = true; // draw Horizontal when step = 1, otherse vertical

    QPen pen;
    pen.setColor(QColor("#ced9eb"));
    pen.setWidthF(2);
    painter.setPen(pen);
    painter.setBrush(QBrush("##e9eef6"));

    for (int i = 0 ; i < mSequenceTrace->baseLocations().length(); ++i)
    {
        int pos = mSequenceTrace->baseLocations().at(i);

        if (pos >= mXStart && pos <= viewport()->rect().width()/mXFactor + mXStart)
        {
            QPointF p ((pos - mXStart) * mXFactor, 300);



            painter.drawPoint(p);

            //            // Draw Base
            //            QChar base = mSequenceTrace->sequence().at(i);

            //            QFont font;
            //            font.setPixelSize(15);
            //            font.setBold(true);
            //            painter.setFont(font);

            //            QFontMetrics metrics(font);
            //            QPointF textPos (p.x() - metrics.width(base)/2, p.y());
            //            textPos.setY(yMargin - 8);
            //            painter.setPen(QPen(mTraceColors[base]));
            //            painter.drawText(textPos, QString(base));
        }
    }






}
//-------------------------------------------------------------------------------

void TraceView::drawBases(QPainter& painter)
{

    int yMargin = 27;
    QPen pen;
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.setBrush(QBrush("#F5F5F5"));
    painter.drawRect(0, 0, viewport()->width(), yMargin);


    for (int i = 0 ; i < mSequenceTrace->baseLocations().length(); ++i)
    {
        int pos = mSequenceTrace->baseLocations().at(i);

        if (pos >= mXStart && pos <= viewport()->rect().width()/mXFactor + mXStart)
        {
            QPointF p ((pos - mXStart) * mXFactor, 15);

            // Draw Base
            QChar base = mSequenceTrace->sequence().at(i);

            QFont font;
            font.setPixelSize(15);
            font.setBold(true);
            painter.setFont(font);

            QFontMetrics metrics(font);
            QPointF textPos (p.x() - metrics.width(base)/2, p.y());
            textPos.setY(yMargin - 8);
            painter.setPen(QPen(mTraceColors[base]));
            painter.drawText(textPos, QString(base));
        }
    }



}
//-------------------------------------------------------------------------------
void TraceView::drawTraces(QPainter& painter)
{
    // inverse y axis
    painter.translate(viewport()->rect().bottomLeft());
    painter.scale(1.0, -1.0);

    for (QChar base : mSequenceTrace->bases())
    {
        // load paths to draw
        QPainterPath path;
        path.moveTo(0,0);
        QVector<int> data = mSequenceTrace->traces()[base];

        for ( int x = mXStart ; x < viewport()->rect().width()/mXFactor + mXStart; ++x)
        {
            if (x >= data.size())
                break;

            QPointF p ( x - mXStart, data[x]);
            path.lineTo((p.x()) * mXFactor , p.y() * mYFactor);

        }
        // draw path
        QPen pen;
        pen.setColor(mTraceColors[base]);
        pen.setWidthF(1);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        painter.setBrush(Qt::transparent);
        painter.drawPath(path);
    }
}
//-------------------------------------------------------------------------------
void TraceView::drawSelection(QPainter &painter)
{
    QPainterPath stepCurve;
    bool step = true; // draw Horizontal when step = 1, otherse vertical

    QPen pen;
    QColor highlight = palette().brush(QPalette::Highlight).color();
    pen.setColor(highlight);
    pen.setWidthF(2);
    painter.setPen(pen);
    highlight.setAlphaF(0.1);
    QBrush bgBrush = QBrush(highlight);
    painter.setBrush(bgBrush);


    if (mCurrentSelection.length >= mSequenceTrace->baseLocations().length())
        return;


    int start = mSequenceTrace->baseLocations().at(mCurrentSelection.pos);
    int end = mSequenceTrace->baseLocations().at(mCurrentSelection.pos + mCurrentSelection.length);

    QPointF up   ((start - mXStart) * mXFactor, 0);
    QPointF down ((end - mXStart) * mXFactor, viewport()->height());

    QRectF area;
    area.setTopLeft(up);
    area.setBottomRight(down);

    painter.drawRect(area);









}
//-------------------------------------------------------------------------------

void TraceView::setFilename(const QString &filename)
{
    mFilename = filename;
    mSequenceTrace = SequenceTraceFactory::loadTraceFile(filename);

    if (!mSequenceTrace){
        qCritical()<<Q_FUNC_INFO<<"Cannot read the file";
        setDisabled(true);
        return ;
    }

    setDisabled(false);
    viewport()->update();
    updateScrollbar();
}
//-------------------------------------------------------------------------------

AbstractSequenceTrace *TraceView::sequenceTrace()
{
    return mSequenceTrace;
}
//-------------------------------------------------------------------------------

void TraceView::setAmplitudeFactor(float factor)
{
    mYFactor = factor;
    viewport()->update();
    updateScrollbar();
}
//-------------------------------------------------------------------------------

void TraceView::setScaleFactor(float factor)
{
    mXFactor = factor;
    viewport()->update();
    updateScrollbar();
}
//-------------------------------------------------------------------------------
void TraceView::setSelection(int pos, int length)
{

    mCurrentSelection = {pos, length};
    viewport()->update();

}

