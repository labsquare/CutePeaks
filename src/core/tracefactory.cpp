#include "tracefactory.h"


TraceFactory::FileType TraceFactory::filetype(QIODevice *device)
{
    if (device->open(QIODevice::ReadOnly))
    {
        QByteArray magic = device->read(4);

        if (magic.toUpper() == "ABIF")
            return ABIF;

        if (magic.toUpper() == ".SCF")
            return SCF;

        device->close();
    }
    else
        qCritical()<<QObject::tr("Cannot open file");

    return Unknown;

}

TraceFactory::FileType TraceFactory::filetype(const QString &filename)
{
    QFile file(filename);
    return TraceFactory::filetype(&file);
}

Trace * TraceFactory::createTrace(const QString &filename)
{
    QFile file(filename);

    QScopedPointer<AbstractTraceReader> reader;

    if (TraceFactory::filetype(filename) == ABIF)
        reader.reset(new AbifTraceReader(&file));

    if (TraceFactory::filetype(filename) == SCF)
        reader.reset(new ScfTraceReader(&file));

    if (reader == nullptr)
        return nullptr;

    return reader->readTrace();
}

