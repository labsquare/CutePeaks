#include "reversesequenceproxytrace.h"



ReverseSequenceProxyTrace::ReverseSequenceProxyTrace(AbstractTraceReader *source)
    :AbstractTraceReader(nullptr), mSource(source)
{
    mBaseCalls     = source->sequence().reverse();

    mConfScores    = source->baseScores();
    mBaseLocations = source->baseLocations();
    std::reverse(mConfScores.begin(), mConfScores.end());
    std::reverse(mBaseLocations.begin(), mBaseLocations.end());

    mTraces = source->datas();

    for (auto it = mTraces.begin(); it != mTraces.end(); ++it)
    {
        auto list = it.value();
        std::reverse(list.begin(), list.end());
        mTraces[it.key()] = list;
    }

}

const QHash<QChar, QVector<int> > &ReverseSequenceProxyTrace::datas() const
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

const QVector<int> &ReverseSequenceProxyTrace::baseScores() const
{
    return mConfScores;
}
