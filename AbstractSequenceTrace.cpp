#include "AbstractSequenceTrace.h"

AbstractSequenceTrace::AbstractSequenceTrace(QIODevice *device)
    :mDevice(device)
{

}
QList<QChar> AbstractSequenceTrace::bases() const
{
    return traces().keys();
}

int AbstractSequenceTrace::traceLength()
{
    if (traces().isEmpty())
        return 0;

    QChar key = traces().keys().first();
    return traces()[key].count();
}

QVector<int> AbstractSequenceTrace::trace(const QChar& base) const
{
    return traces()[base];
}

QIODevice *AbstractSequenceTrace::device()
{
    return mDevice;
}

