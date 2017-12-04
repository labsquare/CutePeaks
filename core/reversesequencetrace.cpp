#include "reversesequencetrace.h"


ReverseSequenceTrace::ReverseSequenceTrace(QIODevice *device)
    :AbstractSequenceTrace(device)
{

}

const QHash<QChar, QVector<int> > &ReverseSequenceTrace::traces() const
{

}

const Sequence &ReverseSequenceTrace::sequence() const
{

}

const QVector<int> &ReverseSequenceTrace::baseLocations() const
{

}

const QVector<int> &ReverseSequenceTrace::confScores() const
{

}
