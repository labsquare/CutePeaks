#include "abstracttracewriter.h"

AbstractTraceWriter::AbstractTraceWriter(QIODevice *device)
{

}

AbstractTraceWriter::~AbstractTraceWriter()
{

}

void AbstractTraceWriter::writeTrace(Trace *trace) const
{
    writeDatas(trace->datas());
    writeBaseLocations(trace->baseLocations());
    writeBaseScores(trace->baseScores());
    writeSequence(trace->sequence());
    writeMetadatas(trace->metadatas());

}
