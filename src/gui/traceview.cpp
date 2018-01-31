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

    setAcceptDrops(true);


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
    QAbstractScrollArea::mouseMoveEvent(event);
}

void TraceView::mousePressEvent(QMouseEvent *event)
{
    if (!isValid())
    {
        QAbstractScrollArea::mousePressEvent(event);
        return;
    }
    // If button left pressed
    if (event->button() == Qt::LeftButton)
    {
        if (event->modifiers() & Qt::ShiftModifier)
        {
            int before = mCurrentSelection.pos;
            int now    = locationFromView(event->pos().x());

            qDebug()<<before<<" "<<now-before+1;
            setSelection(before,now - before + 1);
        }

        else
        {
            int pos = locationFromView(event->pos().x());
            qDebug()<<pos;
            setSelection(pos);
        }

    }

    // If button right pressed
    if (event->button() == Qt::RightButton)
    {
        int pos = locationFromView(event->pos().x());
        if (mCurrentSelection.length > 0 && pos >= mCurrentSelection.pos && pos <= mCurrentSelection.pos + mCurrentSelection.length)
        {

            // TODO : Menu


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
void TraceView::wheelEvent(QWheelEvent * /*event*/)
{
    // TODO
    //    mXFactor += event->delta()/10;
    //    setScaleFactor(mXFactor);


}

void TraceView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        // TODO : read magic number instead
        QFileInfo info(event->mimeData()->urls().first().path());
        QStringList supported = {"ab1","scf"};

        if (supported.contains(info.suffix().toLower()))
            event->acceptProposedAction();

    }
}
//-------------------------------------------------------------------------------
void TraceView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        setFilename(event->mimeData()->urls().first().path());
    }
}
//-------------------------------------------------------------------------------
void TraceView::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_PageUp)
        scrollTo(horizontalScrollBar()->minimum());

    if (event->key() == Qt::Key_PageDown)
        scrollTo(horizontalScrollBar()->maximum());

    return QAbstractScrollArea::keyPressEvent(event);

}
//-------------------------------------------------------------------------------
void TraceView::setupViewportDummy()
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
void TraceView::drawAll(QPainter &painter) const
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
        drawPositions(painter);

        drawSelection(painter);

        if (mShowAminoAcid)
            drawAminoAcid(painter);

        painter.translate(viewport()->rect().bottomLeft());
        painter.scale(1.0, -1.0);

        drawTraces(painter);

        if (mShowQuality)
            drawConfident(painter);

        painter.translate(viewport()->rect().bottomLeft());
        painter.scale(1.0, -1.0);

        // drawAxis(painter); //TODO axis next release


    }
}
//-------------------------------------------------------------------------------
void TraceView::drawConfident(QPainter& painter) const
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

void TraceView::drawBases(QPainter& painter) const
{
    QPen pen;
    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    painter.setFont(font);

    bool alternColor = true;
    // loop over all base position
    for (int i=0; i<trace()->baseLocations().length(); ++i, alternColor = !alternColor)
    {
        // get shift base ( before )
        int pos = trace()->shiftBaseLocations().at(i);

        if (inView(pos, 10))
        {
            // get border rect
            int leftBase  = traceToView(trace()->shiftBaseLocations().at(i));
            int rightBase = traceToView(trace()->shiftBaseLocations().at(i+1));

            QChar base = trace()->sequence().at(i);

            // draw rect background
            QRect rect;
            rect.setLeft(leftBase);
            rect.setRight(rightBase);
            rect.setY(0);
            rect.setHeight(mHeaderHeight);

            pen.setWidthF(0.5);
            pen.setColor(Qt::lightGray);
            painter.setPen(pen);
            painter.setBrush(QBrush(alternColor ? QColor("#F5F5F5"): QColor("#EAEAEA")));

            painter.drawRect(rect);

            // draw Base name
            painter.setPen(QPen(TraceColor::color(base)));
            font.setBold(false);
            painter.setFont(font);
            painter.drawText(rect, Qt::AlignCenter, base);
        }
    }
}
//-------------------------------------------------------------------------------

void TraceView::drawAminoAcid(QPainter &painter) const
{
    QPen pen;
    pen.setColor(Qt::gray);
    painter.setPen(pen);

    int shift = int(mReadFrame);

    for (int i=0 + shift; i<trace()->baseLocations().length()-3-shift; i+=3)
    {
        int pos = trace()->baseLocations().at(i);

        if (inView(pos,40))
        {

            int leftBase  = traceToView(trace()->shiftBaseLocations().at(i + shift));
            int rightBase = traceToView(trace()->shiftBaseLocations().at(i+3 + shift));

            // draw rect
            QRect rect;
            rect.setLeft(leftBase);
            rect.setRight(rightBase);
            rect.setY(mHeaderHeight);
            rect.setHeight(mHeaderHeight);

            QPen pen;
            pen.setWidthF(0.5);
            pen.setColor(Qt::lightGray);

            QLinearGradient linearGrad(QPointF(rect.x(), rect.top()), QPointF(rect.x(), rect.bottom()));
            linearGrad.setColorAt(0, QColor("#3FA2FC"));
            linearGrad.setColorAt(1, QColor("#115FBE"));

            painter.setPen(pen);
            painter.setBrush(Qt::red);
            painter.setBrush(QBrush(linearGrad));
            painter.drawRect(rect);


            QByteArray codon = trace()->sequence().byteArray().mid(i+shift,3);
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
void TraceView::drawTraces(QPainter& painter) const
{
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
void TraceView::drawSelection(QPainter &painter) const
{

    QVector<int> adjBaseLocation = trace()->shiftBaseLocations();


    if (mCurrentSelection.pos < 0 || mCurrentSelection.pos >= adjBaseLocation.length())
        return;

    if (mCurrentSelection.pos + mCurrentSelection.length > adjBaseLocation.length())
        return;


    // TODO : avoid copy
    int start = adjBaseLocation.at(mCurrentSelection.pos);
    int end   = adjBaseLocation.at(mCurrentSelection.pos + mCurrentSelection.length);

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
void TraceView::drawPositions(QPainter &painter) const
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
void TraceView::drawEmpty(QPainter &painter) const
{
    QFont font;
    font.setPixelSize(30);

    painter.setFont(font);
    painter.setPen(QPen(Qt::lightGray));
    painter.drawText(viewport()->rect(), Qt::AlignCenter, "Open trace file ...");


}
//-------------------------------------------------------------------------------
void TraceView::drawAxis(QPainter &painter) const
{

    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::lightGray);

    painter.setPen(pen);
    painter.drawLine(mMousePos.x(), mHeaderHeight, mMousePos.x(), viewport()->height());
    painter.drawLine(0, viewport()->height()-mMousePos.y(), viewport()->width(), viewport()->height()-mMousePos.y());


}

float TraceView::xFactor() const
{
    return mXFactor;
}

float TraceView::yFactor() const
{
    return mYFactor;
}
//-------------------------------------------------------------------------------
void TraceView::search(const QString &expression)
{
    mMatchList.clear();
    mMatchIndex = 0;
    qDebug()<<expression;
    QRegularExpression exp;
    exp.setPattern(expression);
    exp.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    if (exp.isValid() && !expression.isEmpty())
    {
        QRegularExpressionMatchIterator it = exp.globalMatch(trace()->sequence().byteArray());
        while (it.hasNext())
            mMatchList.append(it.next());

        if (!mMatchList.isEmpty()){
            mMatchIndex = 0;
            setSelection(mMatchList.first().capturedStart(), mMatchList.first().capturedLength());

        }

    }
    else
        clearSelection();


    emit matchCountChanged(mMatchList.count());


}
//-------------------------------------------------------------------------------
void TraceView::selectNextSearch()
{
    if (mMatchList.isEmpty())
        return;

    if (mMatchIndex < mMatchList.size() - 1)
        mMatchIndex++;

    QRegularExpressionMatch match = mMatchList[mMatchIndex];
    setSelection(match.capturedStart(), match.capturedLength());



}
//-------------------------------------------------------------------------------
void TraceView::selectPreviousSearch()
{
    if (mMatchList.isEmpty())
        return;

    if (mMatchIndex > 0)
        mMatchIndex--;

    QRegularExpressionMatch match = mMatchList[mMatchIndex];
    setSelection(match.capturedStart(), match.capturedLength());

}
//-------------------------------------------------------------------------------
void TraceView::showQuality(bool showQuality)
{
    mShowQuality = showQuality;
    viewport()->update();
}

void TraceView::showAminoAcid(bool showAminoAcid)
{
    mShowAminoAcid = showAminoAcid;
    viewport()->update();
}

Sequence::ReadFame TraceView::frameShift() const
{
    return mReadFrame;
}

void TraceView::setFrameShift(Sequence::ReadFame frameShift)
{
    mReadFrame = frameShift;
    viewport()->update();
}

const Selection &TraceView::currentSelection() const
{
    return mCurrentSelection;
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
    if (trace == nullptr)
        return;

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
    length    = pos+length > max ? max-1-pos : length;

    mCurrentSelection = {pos, length};

    int start = trace()->baseLocations().at(mCurrentSelection.pos);

    scrollTo(start - horizontalScrollBar()->pageStep()/2);
    viewport()->update();

    emit selectionChanged(pos,length);
}

void TraceView::selectAll()
{
    if (!isValid())
        return;

    mCurrentSelection.pos = 0;
    mCurrentSelection.length = trace()->sequence().length();
    viewport()->update();

}
//-------------------------------------------------------------------------------
void TraceView::clearSelection()
{
    mCurrentSelection = {0,0};
    viewport()->update();
    emit selectionChanged(0,0);
}
//-------------------------------------------------------------------------------
Trace *TraceView::cutTrace(int pos, int length)
{
    Trace *trace = mTrace->cut(pos, length);
    clearSelection();
    viewport()->update();
    updateScrollbar();
    return trace;

}
//-------------------------------------------------------------------------------
void TraceView::pasteTrace(Trace *trace)
{
    mTrace->paste(trace);
    setSelection(trace->insertIndex(), trace->baseCount());
    viewport()->update();
    updateScrollbar();

}
//-------------------------------------------------------------------------------
void TraceView::revert()
{

    mTrace->revert();
    viewport()->update();

}
//-------------------------------------------------------------------------------

void TraceView::copySequence() const
{
    if (!isValid())
        return;

    Sequence seq = trace()->sequence().mid(mCurrentSelection.pos, mCurrentSelection.length);
    qApp->clipboard()->setText(seq.toString());

}
//-------------------------------------------------------------------------------
bool TraceView::toSvg(const QString &filename) const
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
bool TraceView::toPng(const QString &filename) const
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
bool TraceView::toCsv(const QString &filename) const
{
    QFile file(filename);
    QTextStream stream(&file);

    if (file.open(QIODevice::WriteOnly))
    {
        for (int i=0; i< trace()->datas().begin()->size(); ++i)
        {
            QStringList row;
            if (i==0)
            {
                for (QChar key : trace()->datas().keys())
                    row.append(key);
                stream <<"#"<<row.join('\t')<<'\n';
                row.clear();
            }

            for (QChar key : trace()->datas().keys())
                row.append(QString::number(trace()->datas()[key][i]));

            stream<<row.join('\t')<<'\n';
        }
        return true;
    }
    return false;
}
//-------------------------------------------------------------------------------
bool TraceView::toFasta(const QString &filename, Sequence::Type type) const
{
    QFile file(filename);
    QTextStream stream(&file);
    QFileInfo info(file);

    if (file.open(QIODevice::WriteOnly))
    {
        if (type == Sequence::Dna)
            stream<<trace()->sequence().toFasta(info.baseName());

        if (type == Sequence::Protein)
            stream<<trace()->sequence().translate(mReadFrame).toFasta(info.baseName());

        return true;
    }
    return false;
}
//-------------------------------------------------------------------------------
int TraceView::traceToView(int x) const
{
    return (x - mXStart) * mXFactor;
}
//-------------------------------------------------------------------------------
int TraceView::traceFromView(int x) const
{
    return (x + mXFactor*mXStart)/mXFactor;
}
//-------------------------------------------------------------------------------
int TraceView::locationFromView(int x) const
{
    int X = traceFromView(x);

    for (int i=1; i< trace()->baseLocations().length(); ++i)
    {
        if (trace()->shiftBaseLocations().at(i) >= X)
            return i-1;
    }

    return trace()->baseLocations().length()-1;
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

int TraceView::matchCount() const
{
    return mMatchList.count();
}



