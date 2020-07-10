#include "abifsequencetrace.h"
#include <QDebug>

AbifSequenceTrace::AbifSequenceTrace(QIODevice *device)
    :AbstractTraceReader(device)
{
    readData();
}

const QHash<QChar, QVector<int>>& AbifSequenceTrace::datas() const
{
    return mTraces;
}
const Sequence& AbifSequenceTrace::sequence()const
{
    return mBaseCalls;
}
const QVector<int>& AbifSequenceTrace::baseLocations()const
{
    return mBaseLocations;

}
const QVector<int>& AbifSequenceTrace::baseScores()const
{
    return mConfScores;
}

const QHash<QString, QVariant> &AbifSequenceTrace::metadatas() const
{

    return mMetadatas;
}

void AbifSequenceTrace::readData()
{
  tracy::readab("/home/schutz/Dev/CutePeaks/examples/B_forward.ab1", mTrace);

  mTraces.clear();
  mTraces['A'] = QVector<int>::fromStdVector(mTrace.traceACGT[0]);
  mTraces['C'] = QVector<int>::fromStdVector(mTrace.traceACGT[1]);
  mTraces['G'] = QVector<int>::fromStdVector(mTrace.traceACGT[2]);
  mTraces['T'] = QVector<int>::fromStdVector(mTrace.traceACGT[3]);


  mConfScores.clear();
  for (const auto& i: mTrace.qual)
      mConfScores.append(i);

  mBaseLocations = QVector<int>::fromStdVector(mTrace.basecallpos);

  mBaseCalls = Sequence(QByteArray::fromStdString(mTrace.basecalls1));


}




