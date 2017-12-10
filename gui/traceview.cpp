#include "traceview.h"

TraceView::TraceView(QWidget *parent)
    :QAbstractScrollArea(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // setup scroll animation
    mScrollAnimation = new QPropertyAnimation(horizontalScrollBar(),"value", this);


    // enable touch screen
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
    //QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);

    setDisabled(true);

    //    setMouseTracking(true);
    //    viewport()->setMouseTracking(true);

}
//-------------------------------------------------------------------------------
void TraceView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(viewport());
    // Draw empty background

    if (!isValid()){
        drawEmpty(painter);
    }
    // otherwise draw trace
    else
        drawAll(painter);
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
    qDebug()<<event->button();
    if (event->button() == Qt::LeftButton)
    {

        int pos = locationFromView(event->pos().x());
        qDebug()<<"move";

    }


    QAbstractScrollArea::mouseMoveEvent(event);
}

void TraceView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug()<<mCurrentSelection.pos<<" "<<mCurrentSelection.length;
        // if in header section
        if ( event->pos().y() <= mHeaderHeight * 2)
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                int before = mCurrentSelection.pos;
                int now    = locationFromView(event->pos().x());
                setSelection(before,now - before + 1);
            }
            else
            {
                int pos = locationFromView(event->pos().x());
                setSelection(pos);
            }

        }


    }

    QAbstractScrollArea::mousePressEvent(event);

}
//-------------------------------------------------------------------------------
bool TraceView::viewportEvent(QEvent *event)
{
    return QAbstractScrollArea::viewportEvent(event);
}
//-------------------------------------------------------------------------------
void TraceView::keyPressEvent(QKeyEvent *event)
{


    return QAbstractScrollArea::keyPressEvent(event);

}
//-------------------------------------------------------------------------------
void TraceView::setupViewport()
{
    qDebug()<<"after";
}
//-------------------------------------------------------------------------------
bool TraceView::inView(int pos, int margin) const
{
    // if base pos is in the viewport
    return (pos >= mXStart - margin && pos <= viewport()->rect().width()/mXFactor + mXStart + margin);
}
//-------------------------------------------------------------------------------
void TraceView::updateScrollbar()
{
    if (!isValid())
        return;

    int maxXSize = trace()->length();
    horizontalScrollBar()->setRange(0, maxXSize - viewport()->width()/mXFactor);
    horizontalScrollBar()->setPageStep(viewport()->width()/ mXFactor);
}
//-------------------------------------------------------------------------------
void TraceView::drawAll(QPainter &painter)
{
    // draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(viewport()->rect());

    // set antialiasing
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (isValid()){
        // draw elements
        drawBases(painter);
        drawAminoAcid(painter);
        drawPositions(painter);

        drawTraces(painter);
        drawConfident(painter);
        drawSelection(painter);
    }
}
//-------------------------------------------------------------------------------
void TraceView::drawConfident(QPainter& painter)
{
    QPainterPath stepCurve;
    QColor color("#ced9eb");
    QPen pen;
    pen.setColor(color);
    pen.setWidthF(2);
    painter.setPen(pen);
    //    painter.setBrush(Qt::transparent);
    color.setAlphaF(0.4);
    painter.setBrush(color);

    QPainterPath path;

    QPointF oldPoint;

    path.moveTo(0,-100);

    for (int i = 0 ; i < trace()->baseLocations().length(); ++i)
    {
        int pos = trace()->baseLocations().at(i);
        int score  = trace()->baseScores().at(i);

        if (inView(pos, 10))
        {
            QPointF p     = QPointF(traceToView(pos), score * 5 );
            QPointF delta = QPointF(oldPoint.x() +(p.x() - oldPoint.x())/2, 100);

            // draw step

            //            path.moveTo(oldPoint);
            path.lineTo(QPoint(delta.x(), oldPoint.y()));
            path.lineTo(delta.x(), p.y());
            path.lineTo(p);
            oldPoint = p;
        }
    }

    path.lineTo(oldPoint.x(), -100);
    path.setFillRule(Qt::OddEvenFill);
    painter.drawPath(path);

}
//-------------------------------------------------------------------------------

void TraceView::drawBases(QPainter& painter)
{
    int yMargin = 27;
    QPen pen;
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.setBrush(QBrush("#F5F5F5"));
    //    painter.drawRect(0, 0, viewport()->width(), yMargin);
    int codonCounter = 0;
    QPointF oldPos;
    bool swapBgColor = false;

    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    QFontMetrics metrics(font);
    painter.setFont(font);

    int previousPos = 0;

    QVector <int> diffBaseLocation = adjacentBaseLocation();

    bool alternColor = true;
    for (int i=0; i<diffBaseLocation.length()-1; ++i, alternColor = !alternColor)
    {
        int pos = diffBaseLocation.at(i);

        if (inView(pos, 10))
        {
            int a   = traceToView(diffBaseLocation.at(i));
            int b   = traceToView(diffBaseLocation.at(i+1));

            QChar base = trace()->sequence().at(i);

            QRect rect;
            rect.setLeft(a);
            rect.setRight(b);
            rect.setY(0);
            rect.setHeight(mHeaderHeight);

            QPen pen;
            pen.setWidthF(0.5);
            pen.setColor(Qt::lightGray);
            painter.setPen(pen);
            painter.setBrush(QBrush(alternColor ? QColor("#F5F5F5"): QColor("#EAEAEA")));

            painter.drawRect(rect);


            painter.setPen(QPen(TraceColor::color(base)));
            font.setBold(false);
            painter.setFont(font);

            painter.drawText(rect, Qt::AlignCenter, base);


            //            if ( !(i % 10)){
            //                painter.setPen(QPen(Qt::lightGray));
            //                painter.drawText(textPos + QPoint(0,50), QString::number(i));
            //            }
        }
    }
}
//-------------------------------------------------------------------------------

void TraceView::drawAminoAcid(QPainter &painter)
{
    QPen pen;
    pen.setColor(Qt::gray);
    painter.setPen(pen);

    QVector <int> diffBaseLocation = adjacentBaseLocation();

    for (int i=0; i<diffBaseLocation.length()-3; i+=3)
    {
        int pos = diffBaseLocation.at(i);

        if (inView(pos,40))
        {

            int a = traceToView(diffBaseLocation.at(i));
            int b = traceToView(diffBaseLocation.at(i+3));

            QRect rect;
            rect.setLeft(a);
            rect.setRight(b);
            rect.setY(mHeaderHeight);
            rect.setHeight(mHeaderHeight);

            QPen pen;
            pen.setWidthF(0.5);
            pen.setColor(Qt::lightGray);


            QLinearGradient linearGrad(QPointF(rect.x(), rect.top()), QPointF(rect.x(), rect.bottom()));
            linearGrad.setColorAt(0, QColor("#312FC1"));
            linearGrad.setColorAt(1, QColor("#151451"));

            painter.setPen(pen);
            painter.setBrush(Qt::red);

            painter.setBrush(QBrush(linearGrad));

            painter.drawRect(rect);


            QByteArray codon = trace()->sequence().byteArray().mid(i,3);
            Sequence seq(codon);
            QString aa = seq.translate().toString(Sequence::ShortFormat);

            QFont font;
            font.setBold(true);
            font.setPixelSize(12);
            painter.setFont(font);

            pen.setColor(Qt::white);
            painter.setPen(pen);

            QFontMetrics metrics(font);
            painter.drawText(rect,Qt::AlignCenter, aa);

        }
    }

}
//-------------------------------------------------------------------------------
void TraceView::drawTraces(QPainter& painter)
{
    // inverse y axis
    painter.translate(viewport()->rect().bottomLeft());
    painter.scale(1.0, -1.0);

    for (QChar base : trace()->basesAvaible())
    {
        // load paths to draw
        QPainterPath path;
        path.moveTo(0,0);
        QVector<int> data = trace()->datas()[base];

        for ( int x = mXStart ; x < viewport()->rect().width()/mXFactor + mXStart; ++x)
        {
            if (x >= data.size())
                break;

            QPointF p ( x - mXStart, data[x]);
            path.lineTo((p.x()) * mXFactor , p.y() * mYFactor);

        }
        // draw path
        QPen pen;
        pen.setColor(TraceColor::color(base));
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

    QVector<int> adjBaseLocation = adjacentBaseLocation();

    // TODO : avoid copy
    int start = adjacentBaseLocation().at(mCurrentSelection.pos);
    int end   = adjacentBaseLocation().at(mCurrentSelection.pos + mCurrentSelection.length);

    // curbe
    QColor highlight = palette().brush(QPalette::Highlight).color();

    highlight.setAlphaF(0.1);
    QBrush bgBrush = QBrush(highlight);
    painter.setBrush(bgBrush);

    QPen pen;
    highlight.setAlphaF(1.0);
    pen.setColor(highlight);
    pen.setWidthF(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    QPointF up   (traceToView(start), 0);
    QPointF down (traceToView(end), viewport()->height());

    QRectF area;
    area.setTopLeft(up);
    area.setBottomRight(down);


    // draw area if length > 1
    if (mCurrentSelection.length >= 1)
        painter.drawRect(area);

    // draw line
    else
        painter.drawLine(up.x(),up.y(), up.x(), viewport()->height());



}
//-------------------------------------------------------------------------------
void TraceView::drawPositions(QPainter &painter)
{
    QPen pen;
    pen.setColor(Qt::gray);
    painter.setPen(pen);

    QFont font;
    font.setPixelSize(12);
    font.setBold(false);
    painter.setFont(font);

    QFontMetrics metrics(font);

    for (int i=0; i<trace()->baseLocations().length(); i+=10)
    {

        int pos = trace()->baseLocations().at(i);

        if (inView(pos))
        {

            int x = traceToView(pos) - metrics.width(QString::number(i))/2;
            painter.drawText(QPoint(x, mHeaderHeight*3), QString::number(i));

        }
    }
}
//-------------------------------------------------------------------------------
void TraceView::drawEmpty(QPainter &painter)
{
    QFont font;
    font.setPixelSize(30);

    painter.setFont(font);
    painter.setPen(QPen(Qt::lightGray));
    painter.drawText(viewport()->rect(), Qt::AlignCenter, "Open trace file ...");


}
//-------------------------------------------------------------------------------
QVector<int> TraceView::adjacentBaseLocation() const
{
    QVector <int> diffBaseLocation;
    std::adjacent_difference(trace()->baseLocations().begin(),
                             trace()->baseLocations().end(),
                             std::back_inserter(diffBaseLocation),
                             [](int a,int b){return b+(a-b)/2;});

    return diffBaseLocation;


}
//-------------------------------------------------------------------------------

void TraceView::setFilename(const QString &filename)
{
    mFilename = filename;
    setTrace(TraceFactory::createTrace(filename));


}
//-------------------------------------------------------------------------------
void TraceView::setTrace(Trace *trace)
{
    mTrace = trace;
    if (!isValid()){
        qCritical()<<Q_FUNC_INFO<<tr("Cannot read the file");
        setDisabled(true);
        return ;
    }

    setDisabled(false);
    viewport()->update();
    updateScrollbar();
}
//-------------------------------------------------------------------------------

const Trace *TraceView::trace() const
{
    return mTrace;
}
//-------------------------------------------------------------------------------
bool TraceView::isValid() const
{
    if (mTrace == nullptr)
        return false;

    return trace()->isValid();
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
    // invert selection if is reverse
    // length < 0
    if (length < 0)
    {
        pos    = pos - qAbs(length)-1;
        length = qAbs(length) + 2 ;
    }

    // check out of range
    int max   = trace()->baseLocations().length();
    pos       = pos < 0 ? 0 : pos;
    pos       = pos >= max ? max-1 : pos;
    length    = pos+length >= max ? max-1-pos : length;

    mCurrentSelection = {pos, length};

    int start = trace()->baseLocations().at(mCurrentSelection.pos);

    //scrollTo(start - horizontalScrollBar()->pageStep()/2);
    viewport()->update();

    emit selectionChanged(pos,length);
}
//-------------------------------------------------------------------------------
bool TraceView::toSvg(const QString &filename)
{
    QSvgGenerator generator;
    generator.setFileName(filename);
    generator.setSize(viewport()->size());
    generator.setViewBox(viewport()->rect());
    generator.setTitle("Sanger trace file");
    generator.setDescription(tr("An SVG rendering from cutepeaks"));

    QPainter painter;
    painter.begin(&generator);
    drawAll(painter);
    painter.end();

    return true;
}
//-------------------------------------------------------------------------------
bool TraceView::toPng(const QString &filename)
{
    QPixmap image(viewport()->rect().size());
    image.fill(Qt::white);
    QPainter painter;
    painter.begin(&image);
    drawAll(painter);
    painter.end();
    return image.save(filename);
}
//-------------------------------------------------------------------------------
int TraceView::traceToView(int x)
{
    return (x - mXStart) * mXFactor;
}
//-------------------------------------------------------------------------------
int TraceView::traceFromView(int x)
{
    return (x + mXFactor*mXStart)/mXFactor;
}
//-------------------------------------------------------------------------------
int TraceView::locationFromView(int x)
{
    QVector<int> adj = adjacentBaseLocation();
    int X = traceFromView(x);
    for (int i=1; i< trace()->baseLocations().length(); ++i)
    {
        if (adj.at(i) >= X)
            return i-1;
    }
    return adj.length() -1;
}
//-------------------------------------------------------------------------------
void TraceView::scrollTo(int pos, bool animate)
{
    if (animate)
    {
        mScrollAnimation->stop();
        mScrollAnimation->setStartValue(horizontalScrollBar()->value());
        mScrollAnimation->setEndValue(pos);
        mScrollAnimation->setEasingCurve(QEasingCurve::OutQuint);
        mScrollAnimation->setDuration(500);
        mScrollAnimation->start();
    }

    else
        horizontalScrollBar()->setValue(pos);
}


