#include "abstracttracewriter.h"

AbstractTraceWriter::AbstractTraceWriter(QIODevice *device)
    :mDevice(device)
{

}

QIODevice *AbstractTraceWriter::device()
{
    return mDevice;
}
