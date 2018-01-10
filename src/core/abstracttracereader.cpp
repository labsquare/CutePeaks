#include "abstracttracereader.h"

AbstractTraceReader::AbstractTraceReader(QIODevice *device)
    :mDevice(device)
{

}

AbstractTraceReader::~AbstractTraceReader()
{

}

Trace * AbstractTraceReader::readTrace() const
{
    return new Trace(readDatas(), readBaseLocations(), readBaseScores(), readSequence(), readMetadatas());

}

QIODevice *AbstractTraceReader::device()
{
    return mDevice;
}
