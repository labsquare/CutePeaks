#include "abstracttracereader.h"

AbstractTraceReader::AbstractTraceReader(QIODevice *device)
    :mDevice(device)
{

}

AbstractTraceReader::~AbstractTraceReader()
{

}

Trace AbstractTraceReader::createTrace() const
{
    Trace tt(datas(), baseLocations(), baseScores(), sequence(), metadatas());
    return tt;
}

QIODevice *AbstractTraceReader::device()
{
    return mDevice;
}
