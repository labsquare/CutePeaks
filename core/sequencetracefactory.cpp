#include "sequencetracefactory.h"


SequenceTraceFactory::FileType SequenceTraceFactory::filetype(QIODevice *device)
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

SequenceTraceFactory::FileType SequenceTraceFactory::filetype(const QString &filename)
{
    QFile file(filename);
    return SequenceTraceFactory::filetype(&file);
}

Trace SequenceTraceFactory::loadTraceFile(const QString &filename)
{

    QFile * file = new QFile(filename);

    AbstractTraceReader * reader;
    Trace trace;

    if (SequenceTraceFactory::filetype(filename) == ABIF)
        reader = new AbifSequenceTrace(file);

    if (SequenceTraceFactory::filetype(filename) == SCF)
        reader = new ScfSequenceTrace(file);

    return reader->trace();


}

SequenceTraceFactory::SequenceTraceFactory()
{

}
