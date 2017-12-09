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
    QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);

    setDisabled(true);

    setMouseTracking(true);

}
//-------------------------------------------------------------------------------
void TraceView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(viewport());
    // Draw empty background



    if (!isValid()){
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));
        painter.drawRect(viewport()->rect());
        return;
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
    if (event->localPos().y() > mBaseHeight && event->localPos().y() <= viewport()->rect().height()-4)
        setCursor(Qt::CrossCursor);
    else
        setCursor(Qt::ArrowCursor);

    QAbstractScrollArea::mouseMoveEvent(event);
}

void TraceView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug()<<"click "<<mCurrentSelection.pos<<" "<<mCurrentSelection.length;
        // mTrace->cut(mCurrentSelection.pos, mCurrentSelection.length);
        viewport()->update();
        updateScrollbar();
        toSvg("/tmp/test.svg");


    }


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
            rect.setHeight(mBaseHeight);

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
            rect.setY(mBaseHeight);
            rect.setHeight(mBaseHeight);

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
    QPainterPath stepCurve;

    QPen pen;
    QColor highlight = palette().brush(QPalette::Highlight).color();
    pen.setColor(highlight);
    pen.setWidthF(2);
    painter.setPen(pen);
    highlight.setAlphaF(0.1);
    QBrush bgBrush = QBrush(highlight);
    painter.setBrush(bgBrush);

    if (mCurrentSelection.length >= trace()->baseLocations().length())
        return;


    // TODO : avoid copy
    int start = adjacentBaseLocation().at(mCurrentSelection.pos);
    int end   = adjacentBaseLocation().at(mCurrentSelection.pos + mCurrentSelection.length);

    QPointF up   (traceToView(start), 0);
    QPointF down (traceToView(end), viewport()->height());

    QRectF area;
    area.setTopLeft(up);
    area.setBottomRight(down);

    painter.drawRect(area);


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
            painter.drawText(QPoint(x, mBaseHeight*3), QString::number(i));

        }
    }
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

    mCurrentSelection = {pos, length};
    //viewport()->update();


    int start = trace()->baseLocations().at(mCurrentSelection.pos);
    int end   = trace()->baseLocations().at(mCurrentSelection.pos + mCurrentSelection.length);

    scrollTo(start-50);
    viewport()->update();


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


