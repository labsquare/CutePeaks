#include "scftracewriter.h"

ScfTraceWriter::ScfTraceWriter(QIODevice *device)
    :AbstractTraceWriter(device)
{

}

void ScfTraceWriter::writeDatas(const QHash<QChar, QVector<int> > &datas)
{


}

void ScfTraceWriter::writeSequence(const Sequence &sequence)
{

}

void ScfTraceWriter::writeBaseLocations(const QVector<int> &locations)
{

}

void ScfTraceWriter::writeBaseScores(const QVector<int> &scores)
{

}

void ScfTraceWriter::writeMetadatas(const QHash<QString, QVariant> &meta)
{

}
