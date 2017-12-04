#include "trace.h"

Trace::Trace()
{

}

const QHash<QChar, QVector<int> > &Trace::traces() const
{
    return mTraces;
}

const QVector<int> &Trace::baseLocations() const
{
    return mBaseLocations;
}

void Trace::setTraces(const QHash<QChar, QVector<int> > data)
{
    mTraces = data;
}

void Trace::setBaseLocations(const QVector<int> &data)
{
    mBaseLocations = data;
}

void Trace::setConfScores(const QVector<int> &data)
{
    mConfScores = data;
}

const QVector<int> &Trace::confScores() const
{
    return mConfScores;
}

const Sequence &Trace::sequence() const
{
    return mBaseCalls;
}

int Trace::traceLengh()
{
    if (traces().isEmpty())
        return 0;

    QChar key = traces().keys().first();
    return traces()[key].count();
}

QList<QChar> Trace::bases() const
{
    return traces().keys();

}

QVector<int> Trace::trace(const QChar &base) const
{
    return traces()[base];

}

QStringList Trace::keys() const
{
    return QStringList();
}

QVariant Trace::value(const QString &key)
{
    return "ee";
}

bool Trace::isValid() const
{
    // need to improve

//    if (trace('A').isEmpty())
//        return false;

//    if (baseLocations().length() == 0)
//        return false;

//    if (baseLocations().length() != sequence().length())
//        return false;

    return true;
}

void Trace::setSequence(const Sequence &seq)
{
    mBaseCalls = seq;
}
