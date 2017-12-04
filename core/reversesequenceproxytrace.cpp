#include "reversesequenceproxytrace.h"



ReverseSequenceProxyTrace::ReverseSequenceProxyTrace(AbstractSequenceTrace *source)
    :AbstractSequenceTrace(nullptr), mSource(source)
{
    mBaseCalls     = source->sequence().reverse();

    mConfScores    = source->confScores();
    mBaseLocations = source->baseLocations();
    std::reverse(mConfScores.begin(), mConfScores.end());
    std::reverse(mBaseLocations.begin(), mBaseLocations.end());

    mTraces = source->traces();

    for (auto it = mTraces.begin(); it != mTraces.end(); ++it)
    {
        auto list = it.value();
        std::reverse(list.begin(), list.end());
        mTraces[it.key()] = list;
    }

}

const QHash<QChar, QVector<int> > &ReverseSequenceProxyTrace::traces() const
{
    return mTraces;
}

const Sequence &ReverseSequenceProxyTrace::sequence() const
{
    return mSource->sequence().reverse();
}

const QVector<int> &ReverseSequenceProxyTrace::baseLocations() const
{
    return mBaseLocations;
}

const QVector<int> &ReverseSequenceProxyTrace::confScores() const
{
    return mConfScores;
}
