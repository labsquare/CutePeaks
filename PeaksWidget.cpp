#include "PeaksWidget.h"

PeaksWidget::PeaksWidget(QWidget *parent) : QScrollArea(parent)
{
    mLabel = new QLabel;
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    load();

}

void PeaksWidget::load()
{
    mLineSeries.clear();

    // load data ===================
    int size = 0;
    // parse ab1 file
    AbifReader reader("/home/sacha/Dev/CutePeaks/examples/A_forward.ab1");

    // loop over 4 series A,C,T,G
    for (int i=9; i<=12 ; ++i)
    {
        // create DATA.x key
        QString key = QString("DATA.%1").arg(i);


        // if key exists in ab1 file
        if (reader.directoryKeys().contains(key))
        {
            // create a line serie
            QList<QPointF> serie;
            // get data according key
            QVariantList datas = reader.data(key).toList();
            size = datas.size();

            // fill serie with x,y values
            for (int i=0; i<datas.length(); ++i)
                serie.append(QPointF(i, datas[i].toInt()));

            // add serie in the chart
            mLineSeries[key] = serie;
        }
    }
    // repaint ================================
    pix = QPixmap(10020, height());

    qDebug()<<pix;

    QPainter painter;
    painter.begin(&pix);
    // Invert axis
    painter.translate(pix.rect().bottomLeft());
    painter.scale(1.0, -1.0);

    painter.setBrush(Qt::white);
    painter.drawRect(pix.rect());

    QList <QColor> colors = {Qt::red, Qt::green , Qt::blue, Qt::black};

    auto i = mLineSeries.constBegin();

    int colId = 0;

    while (i != mLineSeries.constEnd()) {

        QPainterPath path;

        for ( QPointF p : mLineSeries[i.key()])
        {
            path.lineTo(p.x(), p.y() * 0.1);


        }

        painter.setPen(colors[colId]);
        painter.drawPath(path);

        colId++;
        i++;

    }

    painter.end();

    mLabel->setPixmap(pix);
    setWidget(mLabel);
    setMinimumHeight(mLabel->height()+20);
    resize(1000,minimumHeight());



}




