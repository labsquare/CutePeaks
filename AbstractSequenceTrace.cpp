#include "AbstractSequenceTrace.h"


AbstractSequenceTrace::AbstractSequenceTrace(QIODevice *device)
    :mDevice(device)
{

}

const QVector<int> &AbstractSequenceTrace::traces(const QChar &base) const
{
    return mTraces[base];
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


void AbstractSequenceTrace::setTrace(const QChar &base, const QVector<int>& data)
{
    mTraces[base] = data;
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
