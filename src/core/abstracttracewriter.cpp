#include "abstracttracewriter.h"

AbstractTraceWriter::AbstractTraceWriter(QIODevice *device)
    :mDevice(device)
{

}

void AbstractTraceWriter::writeTrace(Trace *trace)
{
    writeDatas(trace->datas());
    writeBaseLocations(trace->baseLocations());
    writeBaseScores(trace->baseScores());
    writeSequence(trace->sequence());
    writeMetadatas(trace->metadatas());

}

QIODevice *AbstractTraceWriter::device()
{
    return mDevice;
}
