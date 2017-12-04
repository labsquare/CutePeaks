#include "abstractsequencetrace.h"

AbstractSequenceTrace::AbstractSequenceTrace(QIODevice *device)
    :mDevice(device)
{

}
QList<QChar> AbstractSequenceTrace::bases() const
{
    return traces().keys();
}

int AbstractSequenceTrace::traceLength()
{
    if (traces().isEmpty())
        return 0;

    QChar key = traces().keys().first();
    return traces()[key].count();
}

QVector<int> AbstractSequenceTrace::trace(const QChar& base) const
{
    return traces()[base];
}

QIODevice *AbstractSequenceTrace::device()
{
    return mDevice;
}
QStringList AbstractSequenceTrace::keys() const
{
    return mComments.keys();
}
QVariant AbstractSequenceTrace::value(const QString& key)
{
    return mComments.value(key);
}

bool AbstractSequenceTrace::isValid() const
{
    // need to improve

        if (trace('A').isEmpty())
            return false;

        if (baseLocations().length() == 0)
            return false;

        if (baseLocations().length() != sequence().length())
            return false;

    return true;

}

void AbstractSequenceTrace::addComment(const QString& key, const QVariant& value)
{
    mComments[key]= value;
}

void AbstractSequenceTrace::clearComments()
{
    mComments.clear();
}
