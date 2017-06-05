#include "AbstractSequenceTrace.h"


AbstractSequenceTrace::AbstractSequenceTrace(QIODevice *device)
    :mDevice(device)
{

}

 QVector<int> AbstractSequenceTrace::traces(const QChar &base) const
{
    return mTraces[base.toUpper()];
}

const QByteArray &AbstractSequenceTrace::baseCalls() const
{
    return mBaseCalls;
}

const QVector<int> &AbstractSequenceTrace::baseLocations() const
{
    return mBaseLocations;
}

const QVector<int> &AbstractSequenceTrace::confScores() const
{
    return mConfScores;
}

int AbstractSequenceTrace::traceLength() const
{
    return mTraceLength;
}

QList<QChar> AbstractSequenceTrace::bases() const
{
    return mTraces.keys();
}


void AbstractSequenceTrace::setTrace(const QChar &base, const QVector<int>& data)
{
    mTraces[base.toUpper()] = data;
    // get max x
    mTraceLength = qMax(mTraceLength, data.length());

    // get max y
    for (int i : data)
    {
        mTraceHeight = qMax(mTraceHeight, i);
    }

}

void AbstractSequenceTrace::setBaseCalls(const QByteArray &data)
{
    mBaseCalls = data;
}

void AbstractSequenceTrace::setBaseLocations(const QVector<int> &locations)
{
    mBaseLocations = locations;
}

void AbstractSequenceTrace::setConfScores(const QVector<int> &scores)
{
    mConfScores = scores;
}

QIODevice *AbstractSequenceTrace::device()
{
    return mDevice;
}
