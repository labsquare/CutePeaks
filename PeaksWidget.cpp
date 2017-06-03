#include "PeaksWidget.h"

PeaksWidget::PeaksWidget(QWidget *parent) : QWidget(parent)
{
    resize(1000,200);
}
void PeaksWidget::setFilename(const QString &filename)
{
    mFilename = filename;
    load();
    update();
}

void PeaksWidget::setAmplitudeFactor(int factor)
{
    mYFactor = float(factor) / 100;
    update();
}

void PeaksWidget::setScaleFactor(int factor)
{
    mXFactor = factor;
    update();
}


void PeaksWidget::load()
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

}

void PeaksWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    // inverse y axis
    painter.translate(rect().bottomLeft());
    painter.scale(1.0, -1.0);


    QPainterPath path;
    path.moveTo(0,0);
    QVector<QPointF> data = mLineSeries["DATA.11"];

    for ( int x = 0 ; x < qMin(rect().width(),data.size()) ; ++x)
    {
        QPointF p = mLineSeries["DATA.11"][x];
        path.lineTo(p.x() * mXFactor , p.y() * mYFactor);

    }


    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setBrush(Qt::transparent);
    painter.drawPath(path);








}



void PeaksWidget::draw()
{
    // repaint ================================
    int cHeight = height();
    mPix = QPixmap(mXSize * mXFactor ,cHeight );
    mPix.fill(Qt::white);
    resize(mPix.size());


    QPainter painter;
    painter.begin(&mPix);
    //painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
    // Invert axis
    painter.translate(mPix.rect().bottomLeft());
    painter.scale(1.0, -1.0);


    QList <QColor> colors = {Qt::red, Qt::green , Qt::blue, Qt::black};

    auto i = mLineSeries.constBegin();
    int colId = 0;
    mPaths.clear();
    while (i != mLineSeries.constEnd()) {


        for (int ii=0; ii <  mLineSeries[i.key()].size(); ii+=1)
        {
            QPointF p = mLineSeries[i.key()][ii];
            painter.drawPoint(p);
            //            path.lineTo(p.x() * mXFactor, p.y() * cHeight / mYSize * mYFactor);

        }
        //        mPaths.append(path);

        QPen pen(colors[colId]);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(Qt::transparent);
        //        painter.drawPath(path);

        colId++;
        i++;

    }
    painter.end();
    update();
}




