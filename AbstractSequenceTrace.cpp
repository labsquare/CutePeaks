#include "AbstractSequenceTrace.h"


AbstractSequenceTrace::AbstractSequenceTrace(QIODevice *device)
    :mDevice(device)
{

}

AbstractSequenceTrace::AbstractSequenceTrace(const QString &filename)
{

    AbstractSequenceTrace(new QFile(filename));

}


const QVector<int> &AbstractSequenceTrace::traces(const QChar &base)
{
    return mTraces[base];
}
