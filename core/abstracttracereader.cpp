#include "abstracttracereader.h"

AbstractTraceReader::AbstractTraceReader(QIODevice *device)
    :mDevice(device)
{

}

AbstractTraceReader::~AbstractTraceReader()
{

}

Trace * AbstractTraceReader::createTrace() const
{
    return new Trace(datas(), baseLocations(), baseScores(), sequence(), metadatas());

}

QIODevice *AbstractTraceReader::device()
{
    return mDevice;
}
