#include "abstracttracereader.h"

AbstractTraceReader::AbstractTraceReader(QIODevice *device)
    :mDevice(device)
{

}

Trace AbstractTraceReader::createTrace() const
{
    Trace tt(datas(), baseLocations(), baseScores(), sequence());
    return tt;
}

QIODevice *AbstractTraceReader::device()
{
    return mDevice;
}
QStringList AbstractTraceReader::keys() const
{
    return mComments.keys();
}
QVariant AbstractTraceReader::value(const QString& key)
{
    return mComments.value(key);
}

void AbstractTraceReader::addComment(const QString& key, const QVariant& value)
{
    mComments[key]= value;
}

void AbstractTraceReader::clearComments()
{
    mComments.clear();
}
