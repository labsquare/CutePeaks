#include "peaksview.h"


PeaksView::PeaksView(QWidget *parent)
    :QScrollArea(parent)
{
    mWidget = new PeaksWidget;
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

PeaksWidget *PeaksView::widget()
{
    return mWidget;
}

void PeaksView::setFilename(const QString &filename)
{
    mWidget->setFilename(filename);
    setWidget(mWidget);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);


}

void PeaksView::setAmplitudeFactor(int factor)
{
    mWidget->setAmplitudeFactor(factor);
}

void PeaksView::setScaleFactor(int factor)
{
    mWidget->setScaleFactor(factor);
    qDebug()<<"widget size " <<mWidget->size();

}
